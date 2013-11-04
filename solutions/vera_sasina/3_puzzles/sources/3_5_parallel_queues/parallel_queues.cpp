#include <reader.h>
#include <map>

typedef std::map<uint32_t, uint32_t> uint32_map;
const static uint32_t max_type = 100000;
const static size_t size_buffer = 2048;

class Result
{
private:
	uint32_map results;
	uint32_t full_time;
public:
	void add( const uint32_t );
	void check_time( const uint32_t );
};

void check_data( std::string &input_file_name, Result &res )
{
	std::ifstream input_file( BINARY_DIR + input_file_name, std::ios::binary );
	if ( !input_file.is_open() )
		return;

	uint32_map buffer;
	size_t read_size = 0;
	uint32_t current_time = 0;

	while(true)
	{
		binary_reader::message net_data( input_file );
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
			res.add( net_data.type() );
		}
		res.check_time( net_data.time() );
	}


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
	input_file.close();
	output_file.close();
}
int main()
{
	char *name;
	boost::thread_group threads;
	int count_files = 1000;
	class Result output;
	for( int i = 1; i < count_files; i++ )
	{
		name = new char [16];
		std::sprintf( name, "/input_%03d.txt", i );
		std::string input_file_name( name );

		threads.create_thread( boost::bind( &check_data, input_file_name, output ) );
		delete [] name;
	}
	threads.join_all();


	return 0;
}