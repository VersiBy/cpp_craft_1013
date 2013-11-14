#ifndef _TASK5_4_TEMPLATE_FUNCTIONS_H_
#define _TASK5_4_TEMPLATE_FUNCTIONS_H_

#include <functional>
#include <algorithm>
#include <iostream>

namespace task5_4
{
	/*
	template < typename T >
	class delete_ptr : public std::unary_function< T, void > 
	{	
	public:
		void operator()( T ptr ) 
		{ 
			delete ptr; 
		}
	};
	*/

	template< bool delete_first, typename Container >
	void clear_container( Container& container)
	{
		if( delete_first )
		{
			//std::for_each( container.begin(), container.end(), delete_ptr< Container::value_type >() );
			for( Container::iterator it = container.begin(); it != container.end(); it++ )
			{
				delete *it;
			}	
		}
		container.clear();
	}

	template< bool delete_first, bool delete_second, typename Container >
	void clear_container( Container& container )
	{
		// TODO
		container.clear();
	}
}

#endif // _TASK5_4_TEMPLATE_FUNCTIONS_H_