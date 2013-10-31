#ifndef _BINARY_READER_READER_H_
#define _BINARY_READER_READER_H_

#include <stdint.h>
#include <fstream>
#include <limits>
#include <boost/thread.hpp>

namespace binary_reader
{
	class message 
	{
	protected:
		uint32_t type_;
		uint32_t time_;
		uint32_t len_;
		char *msg_;
	public:
		message() {}
		message( std::ifstream& );
		~message();
		void write( std::ofstream& );
		uint32_t type() const;
		uint32_t time() const;
		const char* const msg() const;
	};

}

#endif // _BINARY_READER_READER_H_
