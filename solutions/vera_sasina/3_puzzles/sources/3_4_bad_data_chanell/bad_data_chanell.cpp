#include <reader.h>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <string>

void check_data( std::string &input_file_name, std::string &output_file_name )
{
	std::ifstream input_file( BINARY_DIR + input_file_name, std::ios::binary );
	if ( !input_file.is_open() )
		return;
	std::ofstream output_file( BINARY_DIR + output_file_name, std::ios::binary );
	if ( !output_file.is_open() )
		return;
	uint32_t maxTime = 0;

	while( true )
	{
		binary_reader::message data( input_file );
		if( input_file.eof() )
			break;

		if(data.type() > 4)
			continue;
		if((data.time()+2) <= maxTime)
			continue;
		if(data.time() > maxTime)
			maxTime = data.time();

		data.write( output_file );
	}
	input_file.close();
	output_file.close();
}

int main()
{
	char *name;
	name = new char [16];
	boost::thread_group threads;
	int count_files = 3;

	for( int i = 0; i < count_files; i++ )
	{
		std::sprintf( name, "/input_%03d.txt", i+1 );
		std::string input_file_name( name );

		std::sprintf( name, "/output_%03d.txt", i+1 );
		std::string output_file_name( name );

		threads.create_thread( boost::bind( &check_data, input_file_name, output_file_name ) );
	}
	delete [] name;
	threads.join_all();
	return 0;
}