
/* ************************************************************************** */
/*                                                                            */
/*     ▄▀▀▄ ▄▄   ▄▀▀█▄▄▄▄  ▄▀▀▀▀▄     ▄▀▀▄▀▀▀▄  ▄▀▀█▄▄▄▄  ▄▀▀▄▀▀▀▄  ▄▀▀▀▀▄    */ 
/*    █  █   ▄▀ ▐  ▄▀   ▐ █    █     █   █   █ ▐  ▄▀   ▐ █   █   █ █ █   ▐    */ 
/*    ▐  █▄▄▄█    █▄▄▄▄▄  ▐    █     ▐  █▀▀▀▀    █▄▄▄▄▄  ▐  █▀▀█▀     ▀▄      */ 
/*       █   █    █    ▌      █         █        █    ▌   ▄▀    █  ▀▄   █     */ 
/*      ▄▀  ▄▀   ▄▀▄▄▄▄     ▄▀▄▄▄▄▄▄▀ ▄▀        ▄▀▄▄▄▄   █     █    █▀▀▀      */ 
/*     █   █     █    ▐     █        █          █    ▐   ▐     ▐    ▐         */ 
/*     ▐   ▐     ▐          ▐        ▐          ▐                             */ 
/*																			  */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*																			  */
/* ************************************************************************** */

#ifndef VERY_USEFUL_UTILITY_HPP
# define VERY_USEFUL_UTILITY_HPP

# include <pair.hpp>

namespace ft
{

//////////
// SWAP //
//////////
	template < class T >
		void	value_swap(T &a, T &b)
	{
		T tmp = b;

		b = a;
		a = tmp;
	}

///////////////
// MAKE_PAIR //
///////////////
	template < class T1, class T2 >
		ft::pair<T1, T2> make_pair (T1 x, T2 y)
	{
		return (ft::pair<T1, T2>(x, y));
	}

///////////
// EQUAL //
///////////
	template< class InputIt1, class InputIt2 >
		bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		while (first1 != last1) {
			if (*first1 != *first2)
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

} /* end of namespace */

#endif
