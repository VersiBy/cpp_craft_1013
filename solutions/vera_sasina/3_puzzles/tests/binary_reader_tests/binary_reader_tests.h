#include <reader.h>
#include <fstream>
#include <boost/test/test_tools.hpp>

namespace binary_reader
{
	namespace bin_read_tests
	{
		class test_message : public binary_reader::message
		{
		public:
			test_message( const uint32_t, const uint32_t, const char* const );
		};

		void generation_messages( std::ofstream& );
		void check_messages( std::ifstream& );
		void start_test();
	}
}