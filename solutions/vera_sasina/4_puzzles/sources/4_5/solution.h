#ifndef _TASK4_5_SOLUTION_H_
#define _TASK4_5_SOLUTION_H_

#include <vector>

namespace task4_5
{
	typedef std::vector< std::vector< int > > data_type;
	typedef std::vector< int > vector_type;

	class solution
	{
		int min;
		int max;
		void find( const vector_type& );
	public:
		explicit solution( const data_type& );
		explicit solution();
		int get_min() const;
		int get_max() const;
	};
}

#endif // _TASK4_5_SOLUTION_H_

