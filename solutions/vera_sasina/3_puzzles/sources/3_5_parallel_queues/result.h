#include <reader.h>
#include <map>

typedef std::map<uint32_t, uint32_t> uint32_map;
const static uint32_t max_type = 100000;
const static size_t size_buffer = 2048;
static boost::mutex mtx;

class Result
{
private:
	uint32_map results;
	uint32_t full_time;
public:
	Result();
	void add( const uint32_t );
	void check_time( const uint32_t );
	void get();
};

void check_data( std::string &, Result * );