#include "solution.h"
#include <boost/thread.hpp>
static boost::mutex mtxMin;
static boost::mutex mtxMax;

task4_5::solution::solution( const data_type &data )
{
	if( data.empty() )
	{
		min = 0;
		max = 0;
	}
	else
	{
		min = data[0][0];
		max = data[0][0];
		size_t szi = data.size();
		boost::thread_group threads;

		for( size_t i = 0; i < szi; i++ )
			threads.create_thread( boost::bind( &solution::find, this, boost::ref( data[i] ) ) );
		threads.join_all();
	}
}

void task4_5::solution::find( const vector_type &data )
{
	size_t szj = data.size();
	for( size_t j = 0; j < szj; j++ )
	{
		{
			boost::mutex::scoped_lock lock( mtxMin );
			min = std::min( min, data[j] );
		}
		{
			boost::mutex::scoped_lock lock( mtxMax );
			max = std::max( max, data[j] );
		}
	}
}

task4_5::solution::solution( ) : min( 0 ) , max( 0 ) {}

int task4_5::solution::get_min() const
{
	return min;
}
int task4_5::solution::get_max() const
{
	return max;
}
