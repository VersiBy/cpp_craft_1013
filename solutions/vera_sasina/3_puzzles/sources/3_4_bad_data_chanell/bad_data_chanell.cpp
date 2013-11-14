#include <reader.h>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <string>

const uint32_t max_type = 4ul;

void check_data( std::string &input_file_name, std::string &output_file_name )
{
	std::ifstream input_file( BINARY_DIR + input_file_name, std::ios::binary );
	if ( !input_file.is_open() )
		return;
	std::ofstream output_file( BINARY_DIR + output_file_name, std::ios::binary );
	if ( !output_file.is_open() )
		return;
	uint32_t maxTime = NULL;

	while( true )
	{
		binary_reader::market_message data( input_file );
		if( input_file.eof() )
			break;

		if( data.type() > max_type )
			continue;
		if( ( data.time() + 2ul ) <= maxTime )
			continue;
		if( data.time() > maxTime )
			maxTime = data.time();

		data.write( output_file );
	}
	input_file.close();
	output_file.close();
}

int main()
{
	char *name;
	boost::thread_group threads;
	int count_files = 5;
	name = new char [16];
	for( int i = 1; i <= count_files; i++ )
	{
		std::sprintf( name, "/input_%03d.txt", i );
		std::string input_file_name( name );
		std::sprintf( name, "/output_%03d.txt", i );
		std::string output_file_name( name );
		threads.create_thread( boost::bind( &check_data, input_file_name, output_file_name ) );
	}
	delete [] name;
	threads.join_all();
	return 0;
}
