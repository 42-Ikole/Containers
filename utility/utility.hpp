/* ************************************************************************** */
/*                                                                            */
/*    ▄▀▀▄ ▄▀▀▄  ▄▀▀▀█▀▀▄  ▄▀▀█▀▄   ▄▀▀▀▀▄     ▄▀▀█▀▄    ▄▀▀▀█▀▀▄  ▄▀▀▄ ▀▀▄   */
/*   █   █    █ █    █  ▐ █   █  █ █    █     █   █  █  █    █  ▐ █   ▀▄ ▄▀   */
/*   ▐  █    █  ▐   █     ▐   █  ▐ ▐    █     ▐   █  ▐  ▐   █     ▐     █     */
/*     █    █      █          █        █          █        █            █     */
/*      ▀▄▄▄▄▀   ▄▀        ▄▀▀▀▀▀▄   ▄▀▄▄▄▄▄▄▀ ▄▀▀▀▀▀▄   ▄▀           ▄▀      */
/*              █         █       █  █        █       █ █             █       */
/*              ▐         ▐       ▐  ▐        ▐       ▐ ▐             ▐       */
/*                                                                            */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERY_USEFUL_UTILITY_HPP
# define VERY_USEFUL_UTILITY_HPP

# include <pair.hpp>
# include <is_integral.hpp>
# include <sfinae.hpp>

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

////////////////
// Equal to?? //
////////////////

	template< class T >
		struct equal_to
	{
		bool operator () (const T &lhs, const T &rhs) const {
			return (lhs == rhs);
		}

	}; /* end of equal to */

//////////////////
// log2 power 2 //
//////////////////

	/*
	** - for integral types only
	** - no negatives
	** - only works for powers of 2 ohterwise it will behave like floor(log2())
	*/
	template < class T >
		typename ft::enable_if<ft::is_integral<T>::value,
			std::size_t>::type	log2pow2(T n)
	{
		std::size_t pow = 1;

		while (n > 2)
		{
			n >>= 1;
			++pow;
		}
		return (pow);
	}

} /* end of namespace */

#endif
