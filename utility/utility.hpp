
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
		return ( ft::pair<T1, T2>(x, y) );
	}

} /* end of namespace */

#endif
