#include "result.h"

int main()
{
	char *name;
	boost::thread_group threads;
	int count_files = 999;
	class Result output;
	name = new char [16];
	for( int i = 1; i <= count_files; i++ )
	{
		std::sprintf( name, "/input_%03d.txt", i );
		std::string input_file_name( name );
		threads.create_thread( boost::bind( &check_data, input_file_name, &output ) );
	}
	threads.join_all();
	output.get();
	delete [] name;
	return 0;
}