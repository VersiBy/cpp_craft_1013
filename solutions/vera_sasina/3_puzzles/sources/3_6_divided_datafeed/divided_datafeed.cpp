#include <reader.h>

int main()
{
	std::ifstream input_file( BINARY_DIR "/input.txt", std::ios::binary );
	if ( !input_file.is_open() )
		return -1;

	while( true )
	{
		binary_reader::data_message data( input_file );
		if( input_file.eof() )
			break;
		const std::string stock_name = data.stock_name();
		std::ofstream output_file( BINARY_DIR "/output_" + stock_name + ".txt", std::ios::binary | std::ios::app );
		if ( !output_file.is_open() )
			return -1;
		data.write( output_file );
		output_file.close();
	}

	input_file.close();
	return 1;
}
