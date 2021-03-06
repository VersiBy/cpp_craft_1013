#include "binary_reader_tests.h"
#include <boost/filesystem.hpp>

binary_reader::bin_read_tests::test_message::test_message( const uint32_t type, const uint32_t time, const char* const msg )
{
	type_ = type;
	time_ = time;
	if( msg )
	{
		len_ = static_cast< uint32_t >( strlen( msg ) ) + 1; // +1 for null-symbol of string
		msg_ = new char[ len_ ];
		memcpy( msg_, msg, len_ );
	}
	else
	{
		len_ = NULL;
		msg_ = NULL;
	}
}

void binary_reader::bin_read_tests::generation_messages( std::string test_file_name )
{
	std::ofstream test_file( BINARY_DIR + test_file_name, std::ios::binary );
	BOOST_CHECK ( test_file.is_open() );
	std::string str;
	char c = '1';
	for( uint32_t i = 1; i < 10; i++, c++)
	{
		str = "test_string";
		str += c;
		test_message msg( i, i, str.c_str() );
 		msg.write( test_file );
	}
	test_message( 10ul, 10ul, NULL ).write( test_file );
	test_file.close();
}

void binary_reader::bin_read_tests::check_messages( std::string test_file_name )
{
	std::ifstream test_file( BINARY_DIR + test_file_name, std::ios::binary );
	BOOST_CHECK ( test_file.is_open() );
	std::string str;
	char c = '1';
	for( uint32_t i = 1; i < 10; i++, c++)
	{
		str = "test_string";
		str += c;
		market_message msg( test_file );
		BOOST_CHECK_EQUAL( msg.type(), i );
		BOOST_CHECK_EQUAL( msg.time(), i );
		BOOST_CHECK_EQUAL( msg.msg(), str.c_str() );
	}
	market_message msg( test_file );
	BOOST_CHECK_EQUAL( msg.type(), 10ul );
	BOOST_CHECK_EQUAL( msg.time(), 10ul );
	BOOST_CHECK_EQUAL( msg.msg(), reinterpret_cast< char* >( NULL ) );
	test_file.close();
}

void binary_reader::bin_read_tests::start_test()
{
	boost::thread_group threads;
	const int count_files = 5;
	char *name;
	name = new char [16];

	for( int i = 0; i < count_files; i++ )
	{ 
		std::sprintf( name, "/test_%03d.txt", i+1 );
		std::string test_file_name( name );
		threads.create_thread( boost::bind( &generation_messages, test_file_name ) ); 
 	}
	threads.join_all();
	
	for( int i = 0; i < count_files; i++ )
	{ 
		std::sprintf( name, "/test_%03d.txt", i+1 );
		std::string test_file_name( name );
		threads.create_thread( boost::bind( &check_messages, test_file_name ) ); 
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