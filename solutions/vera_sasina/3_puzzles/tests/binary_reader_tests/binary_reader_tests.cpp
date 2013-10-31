#include "binary_reader_tests.h"
#include <boost/filesystem.hpp>

binary_reader::bin_read_tests::test_message::test_message( const uint32_t type, const uint32_t time, const char* const msg )
{
	type_ = type;
	time_ = time;
	len_ = static_cast< boost::uint32_t >( strlen( msg ) );
	msg_ = new char[ len_ ];
	memcpy( msg_, msg, len_ );
}

void binary_reader::bin_read_tests::generation_messages( std::ofstream &file )
{
	std::string str;
	char c = '1';
	for( uint32_t i = 1; i < 10; i++, c++)
	{
		str = "test_string" + c;
		test_message msg( i, i, str.c_str() );
		msg.write( file );
	}
	test_message( 10ul, 10ul, NULL ).write( file );
}

void binary_reader::bin_read_tests::check_messages( std::ifstream &file )
{
	std::string str;
	char c = '1';
	for( uint32_t i = 1; i < 10; i++, c++)
	{
		str = "test_string" + c;
		message msg( file );
		BOOST_CHECK_EQUAL( msg.type(), i );
		BOOST_CHECK_EQUAL( msg.time(), i );
		BOOST_CHECK_EQUAL( std::string( msg.msg() ), str );
	}
	message msg( file );
	BOOST_CHECK_EQUAL( msg.type(), 10ul );
	BOOST_CHECK_EQUAL( msg.time(), 10ul );
	BOOST_CHECK_EQUAL( msg.msg(), NULL );
}

void binary_reader::bin_read_tests::start_test()
{
	char *name;
	name = new char [16];
	boost::thread_group threads;
	int count_files = 5;
	for( int i = 0; i < count_files; i++ )
	{
		std::sprintf( name, "/test_%03d.txt", i+1 );
		std::string test_file_name( name );
		std::ofstream test_file( BINARY_DIR + test_file_name, std::ios::binary );
		BOOST_CHECK ( test_file.is_open() );
		threads.create_thread( boost::bind( &binary_reader::bin_read_tests::generation_messages, test_file ) );
	}
	threads.join_all();
	for( int i = 0; i < count_files; i++ )
	{
		std::sprintf( name, "/test_%03d.txt", i+1 );
		std::string test_file_name( name );
		std::ifstream test_file( BINARY_DIR + test_file_name, std::ios::binary );
		BOOST_CHECK ( test_file.is_open() );
		threads.create_thread( boost::bind( &binary_reader::bin_read_tests::check_messages, test_file ) );
	}
	threads.join_all();
	for( int i = 0; i < count_files; i++ )
	{
		std::sprintf( name, "/test_%03d.txt", i+1 );
		std::string test_file_name( name );
		boost::filesystem::remove( BINARY_DIR + test_file_name );
	}
	delete [] name;
}