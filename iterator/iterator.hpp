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
/*																			  */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

namespace ft {

	# define tpl template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	
	tpl
	struct iterator {
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
		
		iterator();
		iterator(const iterator& x);
		iterator&	operator  = (const iterator& x);
		bool		operator == (const iterator& x);
		bool		operator != (const iterator& x);
		iterator*	operator -> ();
		iterator	operator -> ();
		iterator&	operator ++ ();		//prefix
		iterator	operator ++ (int);	//postfix
		iterator&	operator -- ();		//prefix
		iterator	operator -- (int);	//postfix
		iterator	operator  + (int);
		iterator	operator  + (const iterator& x);
		iterator	operator += (int);
		iterator	operator += (const iterator& x);
		iterator	operator  - (int);
		iterator	operator  - (const iterator& x);
		iterator	operator -= (int);
		iterator	operator -= (const iterator& x);
		iterator	operator [] (std::size_t n);
		bool		operator  < (const iterator& x);
		bool		operator <= (const iterator& x);
		bool		operator  > (const iterator& x);
		bool		operator >= (const iterator& x);
	};

	tpl
	class RandomAccessIterator : public iterator {

	};

	#undef tpl
}

#endif