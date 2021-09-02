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
# include <iterator.hpp>

namespace ft {

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
 
	# undef itr

} /* end of namespace */

#endif
