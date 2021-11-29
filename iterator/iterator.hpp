/* ************************************************************************** */
/*                                                                            */
/*  @@@  @@@@@@@  @@@@@@@@  @@@@@@@    @@@@@@   @@@@@@@   @@@@@@   @@@@@@@    */
/*  @@@  @@@@@@@  @@@@@@@@  @@@@@@@@  @@@@@@@@  @@@@@@@  @@@@@@@@  @@@@@@@@   */
/*  @@!    @@!    @@!       @@!  @@@  @@!  @@@    @@!    @@!  @@@  @@!  @@@   */
/*  !@!    !@!    !@!       !@!  @!@  !@!  @!@    !@!    !@!  @!@  !@!  @!@   */
/*  !!@    @!!    @!!!:!    @!@!!@!   @!@!@!@!    @!!    @!@  !@!  @!@!!@!    */
/*  !!!    !!!    !!!!!:    !!@!@!    !!!@!!!!    !!!    !@!  !!!  !!@!@!     */
/*  !!:    !!:    !!:       !!: :!!   !!:  !!!    !!:    !!:  !!!  !!: :!!    */
/*  :!:    :!:    :!:       :!:  !:!  :!:  !:!    :!:    :!:  !:!  :!:  !:!   */
/*   ::     ::     :: ::::  ::   :::  ::   :::     ::    ::::: ::  ::   :::   */
/*  :       :     : :: ::    :   : :   :   : :     :      : :  :    :   : :   */
/*																			  */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_DONT_LIKE_ITERATOR_HPP
# define I_DONT_LIKE_ITERATOR_HPP

# include <traits.hpp>

namespace ft {

/////////////////////////
// Iterator base class //
/////////////////////////

	template <class Category, class T, class Distance = std::ptrdiff_t,
        class Pointer = T*, class Reference = T&>
	struct iterator
	{

	//////////////
	// Typedefs //
	//////////////
	public:

		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};

///////////////////////////////////
// Non member iterator functions //
///////////////////////////////////

	template<class Iter>
		typename ft::iterator_traits<Iter>::difference_type
			distance(Iter first, Iter last)
	{
		return (distance(first, last, typename ft::iterator_traits<Iter>::iterator_category()));
	}

	template<class Iter>
		typename ft::iterator_traits<Iter>::difference_type
			distance (Iter& first, Iter& last, ft::forward_iterator_tag)
	{
		typename iterator_traits<Iter>::difference_type dist = 0;

		while (first != last) {
			first++;
			dist++;
		}
		return (dist);
	}

	template<class Iter>
		typename ft::iterator_traits<Iter>::difference_type
			distance (Iter& first, Iter& last, ft::random_access_iterator_tag)
	{
		return (last - first);
	}

	template <class Iter, class Distance>
		void advance (Iter& it, Distance n)
	{
		it += n;
	}

} /* end of namespace */

#endif
