#ifndef _BINARY_READER_READER_H_
#define _BINARY_READER_READER_H_

#include <stdint.h>
#include <fstream>
#include <limits>
#include <string>
#include <boost/thread.hpp>

namespace binary_reader
{
	class market_message 
	{
	protected:
		uint32_t type_;
		uint32_t time_;
		uint32_t len_;
		char *msg_;
	public:
		market_message() {}
		market_message( std::ifstream& );
		~market_message();
		void write( std::ofstream& );
		uint32_t type() const;
		uint32_t time() const;
		uint32_t len() const;
		const char* const msg() const;
	};

	class data_message
	{
	protected:
		char stock_name_[8];
		char date_time_[8];
		double price_;
		double vwap_;
		uint32_t volume_;
		double f1_;
		double t1_;
		double f2_;
		double f3_;
		double f4_;
		uint32_t days_count_(const char* );
	public:
		data_message() {}
		data_message( std::ifstream& );
		~data_message();
		void write( std::ofstream& );
		const std::string stock_name() const;

	};
}

#endif // _BINARY_READER_READER_H_
