#include "result.h"

Result::Result()
{
	results.empty();
	full_time = 0;
}

void Result::add(  const uint32_t type )
{
	boost::mutex::scoped_lock lock( mtx );
	results[type]++;
}

void Result::check_time( const uint32_t time )
{
	boost::mutex::scoped_lock lock( mtx );
	if( full_time < time )
		full_time = time;
}

void Result::get()
{
	std::ofstream output_file( BINARY_DIR "/output.txt", std::ios::binary );

	double average;
	for(uint32_map::iterator it = results.begin(); it != results.end(); ++it)
	{
		if(it->second > 0)
		{
			average = static_cast<double>(it->second) / static_cast<double>(full_time);
			output_file.write((char*) &it->first, sizeof(it->first));
			output_file.write((char*) &average, sizeof(average));
		}
	}
	output_file.close();
}

void check_data( std::string &input_file_name, Result *res )
{
	std::ifstream input_file( BINARY_DIR + input_file_name, std::ios::binary );
	if ( !input_file.is_open() )
		return;

	uint32_map buffer;
	uint32_t current_time = 0;

	while(true)
	{
		binary_reader::market_message net_data( input_file );
		if( input_file.eof() )
			break;

		if( net_data.time()+1 != current_time )	//time+1 for time == 0
		{
			buffer.clear();
			current_time = net_data.time()+1;
		}
		if( ( buffer[net_data.type()] + net_data.len() + sizeof( uint32_t )*3 ) <= size_buffer )
		{
			buffer[net_data.type()] += net_data.len() + sizeof( uint32_t )*3;
			res->add( net_data.type() );
		}
		res->check_time( net_data.time() );
	}
	input_file.close();
}
