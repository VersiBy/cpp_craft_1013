#include "reader.h"

binary_reader::message::message( std::ifstream &ifile ) : msg_( NULL )
{
	ifile.read( reinterpret_cast< char* >( &type_ ), sizeof( type_ ) );
	ifile.read( reinterpret_cast< char* >( &time_ ), sizeof( time_ ) );
	ifile.read( reinterpret_cast< char* >( &len_ ), sizeof( len_ ) );
	msg_ = new char [len_];
	ifile.read( reinterpret_cast< char* >( msg_ ), len_ );
}

void binary_reader::message::write( std::ofstream &ofile )
{
	ofile.write( reinterpret_cast< char* >( &type_ ), sizeof( type_ ) );;
	ofile.write( reinterpret_cast< char* >( &time_ ), sizeof( time_ ) );
	ofile.write( reinterpret_cast< char* >( &len_ ), sizeof( len_ ) );
	ofile.write( msg_, len_ );
}

binary_reader::message::~message()
{
	delete [] msg_;
}
uint32_t binary_reader::message::type() const
{
	return type_;
}
uint32_t binary_reader::message::time() const
{
	return time_;
}
const char* const binary_reader::message::msg() const
{
	return msg_;
}