#include "reader.h"

// market_message
binary_reader::market_message::market_message( std::ifstream &ifile ) : msg_( NULL )
{
	ifile.read( reinterpret_cast< char* >( &type_ ), sizeof( type_ ) );
	ifile.read( reinterpret_cast< char* >( &time_ ), sizeof( time_ ) );
	ifile.read( reinterpret_cast< char* >( &len_ ), sizeof( len_ ) );
	if ( len_ > 0 )
	{
		msg_ = new char [len_];
		ifile.read( reinterpret_cast< char* >( msg_ ), len_ );
	}
}

void binary_reader::market_message::write( std::ofstream &ofile )
{
	ofile.write( reinterpret_cast< char* >( &type_ ), sizeof( type_ ) );
	ofile.write( reinterpret_cast< char* >( &time_ ), sizeof( time_ ) );
	ofile.write( reinterpret_cast< char* >( &len_ ), sizeof( len_ ) );
	ofile.write( msg_, len_ );
}

binary_reader::market_message::~market_message()
{
	if( msg_ )
		delete [] msg_;
}
uint32_t binary_reader::market_message::type() const
{
	return type_;
}
uint32_t binary_reader::market_message::time() const
{
	return time_;
}
uint32_t binary_reader::market_message::len() const
{
	return len_;
}
const char* const binary_reader::market_message::msg() const
{
	return msg_;
}

// data_message

binary_reader::data_message::data_message(  std::ifstream &ifile )
{
	ifile.read( stock_name_, sizeof( stock_name_ ) );
	ifile.read( date_time_, sizeof( date_time_ ) );
	ifile.read( reinterpret_cast< char* >( &price_ ), sizeof( price_ ) );
	ifile.read( reinterpret_cast< char* >( &vwap_ ), sizeof( vwap_ ) );
	ifile.read( reinterpret_cast< char* >( &volume_ ), sizeof( volume_ ) );
	ifile.read( reinterpret_cast< char* >( &f1_ ), sizeof( f1_ ) );
	ifile.read( reinterpret_cast< char* >( &t1_ ), sizeof( t1_ ) );
	ifile.read( reinterpret_cast< char* >( &f2_ ), sizeof( f2_ ) );
	ifile.read( reinterpret_cast< char* >( &f3_ ), sizeof( f3_ ) );
	ifile.read( reinterpret_cast< char* >( &f4_ ), sizeof( f4_ ) );
}

binary_reader::data_message::~data_message() { }

void binary_reader::data_message::write( std::ofstream& ofile )
{
	ofile.write( stock_name_, 9 );
	uint32_t days = days_count_( date_time_ );
	ofile.write( reinterpret_cast< char* >( &days ), sizeof( days ) );
	price_ = vwap_;
	ofile.write( reinterpret_cast< char* >( &price_ ), sizeof( price_ ) );
	ofile.write( reinterpret_cast< char* >( &volume_ ), sizeof( volume_ ) );
	ofile.write( reinterpret_cast< char* >( &f2_ ), sizeof( f2_ ) );
}

const std::string binary_reader::data_message::stock_name() const
{
	std::string str(stock_name_);
	return str;
}

uint32_t binary_reader::data_message::days_count_( const char* date )
{
	int month;
    int day;
    int year;
	std::sscanf( date, "%4d%2d%2d", &year, &month, &day );
	return ( ( year - 1 ) * 372 +  ( month  - 1 )* 31 + day );
}