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

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include <traits.hpp>
# include <rotareti.hpp>
# include <sfinae.hpp>
# include <iostream>

namespace ft {

/////////////////////////
// Iterator base class //
/////////////////////////

	# define itr	ft::iterator< Category, T, Distance, Pointer, Reference >

	template <class Category, class T, class Distance = std::ptrdiff_t,
          class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};

////////////////////////////
// Pointer iterator class //
////////////////////////////

	template < class T, class Category = ft::random_access_iterator_tag,
		class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	class pointer_iterator : public ft::iterator < Category, T, Distance, Pointer, Reference >
	{
	//////////////
	// Typedefs //
	//////////////
	public:

		typedef typename itr::value_type		value_type;
		typedef typename itr::difference_type	difference_type;
		typedef typename itr::pointer			pointer;
		typedef typename itr::reference			reference;
		typedef typename itr::iterator_category	iterator_category;
	
	//////////////////////
	// Member variables //
	//////////////////////
	protected:
		pointer	_ptr;

	/////////////////
	// constructor //
	/////////////////
	public:

		pointer_iterator(Pointer ptr = NULL) : _ptr(ptr) {}

		pointer_iterator(const pointer_iterator& x) {
			*this = x;
		}

		virtual ~pointer_iterator() {}

	//////////////////////
	// Common operators //
	//////////////////////
	public:

		pointer_iterator&	operator ++ (/* prefix */) {
			_ptr++;
			return (*this);
		}

		pointer_iterator	operator ++ (int /* postfix */) {
			pointer_iterator tmp = *this;
			++(*this);
			return (tmp);
		}

		pointer_iterator&	operator  = (const pointer_iterator& x) {
			this->_ptr = x._ptr;
			return (*this);
		}

	//////////////////////////////
	// Input pointer_iterator operators //
	//////////////////////////////
	public:

		bool		operator == (const pointer_iterator& x) {
			return (this->_ptr == x._ptr);			
		}

		bool		operator != (const pointer_iterator& x) {
			return (this->_ptr != x._ptr);
		}
	
		reference	operator * () {
			return *(this->_ptr);
		}

		pointer		operator -> () {
			return (this->_ptr);
		}
	
	//////////////////////////////////////
	// Bidirectional pointer_iterator operators //
	//////////////////////////////////////
	public:
	
		pointer_iterator&	operator -- (/* prefix */) {
			this->_ptr--;
			return (*this);
		}

		pointer_iterator	operator -- (int /* postfix */) {
			pointer_iterator tmp = *this;
			--(*this);
			return (tmp);
		}

	//////////////////////////////////////
	// Random access pointer_iterator operators //
	//////////////////////////////////////
	public:

		pointer_iterator		operator  + (difference_type val) {
			return (pointer_iterator(this->_ptr + val));
		}

		pointer_iterator		operator  + (const pointer_iterator& x) {
			return (pointer_iterator(*this + x));
		}

		pointer_iterator		operator  - (difference_type val) {
			return (pointer_iterator(this->_ptr - val));
		}

		difference_type	operator  - (const pointer_iterator& x) {
			return (pointer_iterator(this->_ptr - x._ptr));
		}

		bool			operator  < (const pointer_iterator& x) {
			return (this->_ptr < x._ptr);
		}

		bool			operator  > (const pointer_iterator& x) {
			return (this->_ptr > x._ptr);
		}

		bool			operator <= (const pointer_iterator& x) {
			return (this->_ptr <= x._ptr);
		}

		bool			operator >= (const pointer_iterator& x) {
			return (this->_ptr >= x._ptr);
		}

		pointer_iterator&		operator += (difference_type val) {
			this->_ptr += val;
			return (*this);
		}

		pointer_iterator&		operator -= (difference_type val) {
			this->_ptr -= val;
			return (*this);
		}

		reference		operator [] (std::size_t n) {
			return (*(this->_ptr + n));
		}

	}; /* end of iterator class */

///////////////////////////////////
// Non member iterator functions //
///////////////////////////////////

	template<class Iter>
		typename iterator_traits<Iter>::difference_type
			distance (Iter first, Iter last)
	{
		typename iterator_traits<Iter>::difference_type dist = 0;

		while (first != last) {
			first++;
			dist++;
		}
		return (dist);
	}

	template <class Iter, class Distance>
		void advance (Iter& it, Distance n)
	{
		it += n;
	}

 
	# undef itr

} /* end of namespace */

#endif
