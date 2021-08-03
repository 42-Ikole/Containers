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
# include <traits.hpp>
# include <rotareti.hpp>

namespace ft {

/////////////////////////
// Iterator base class //
/////////////////////////

	template < class T, class Category = random_access_iterator_tag, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	class iterator
	{
	//////////////
	// Typedefs //
	//////////////
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	
	//////////////////////
	// Member variables //
	//////////////////////
	protected:
		pointer	_ptr;

	/////////////////
	// constructor //
	/////////////////
	public:
		/* ForwardIterator */
		iterator(Pointer ptr = NULL) : _ptr(ptr) {}

		iterator(const iterator& x) {
			*this = x;
		}

		virtual ~iterator() {}

	//////////////////////
	// Common operators //
	//////////////////////
	protected:

		iterator&	operator ++ (/* prefix */) {
			_ptr++;
			return (*this);
		}

		iterator&	operator ++ (int /* postfix */) {
			iterator tmp = *this;
			++(*this);
			return (*tmp);
		}

		iterator	operator  = (const iterator& x) {
			this->_ptr = x._ptr;
			return (*this);
		}

	//////////////////////////////
	// Input iterator operators //
	//////////////////////////////
	protected:

		bool		operator == (const iterator& x) {
			return (this->_ptr == x._ptr);			
		}

		bool		operator != (const iterator& x) {
			return (this->_ptr != x._ptr);
		}
	
		reference	operator * () {
			return *(this->_ptr);
		}

		pointer		operator -> () {
			return (this->_ptr);
		}
	
	//////////////////////////////////////
	// Bidirectional iterator operators //
	//////////////////////////////////////
	protected:
		
		iterator&	operator -- (/* prefix */) {
			this->_ptr--;
			return (*this);
		}

		iterator&	operator -- (int /* postfix */) {
			iterator tmp = *this;
			--(*this);
			return (tmp);
		}

	//////////////////////////////////////
	// Random access iterator operators //
	//////////////////////////////////////
	protected:

		iterator	operator  + (difference_type val) {
			return (iterator(this->_ptr + val));
		}

		iterator	operator  + (const iterator& x) {
			return (iterator(*this + x));
		}

		iterator	operator  - (difference_type val) {
			return (iterator(this->_ptr - val));
		}

		difference_type			operator  - (const iterator& x) {
			return (iterator(this->_ptr - x._ptr));
		}

		bool					operator  < (const iterator& x) {
			return (this->_ptr < x._ptr);
		}

		bool					operator  > (const iterator& x) {
			return (this->_ptr > x._ptr);
		}

		bool					operator <= (const iterator& x) {
			return (this->_ptr <= x._ptr);
		}

		bool					operator >= (const iterator& x) {
			return (this->_ptr >= x._ptr);
		}

		iterator&	operator += (difference_type val) {
			this->_ptr += val;
			return (*this);
		}

		iterator&	operator -= (difference_type val) {
			this->_ptr -= val;
			return (*this);
		}

		reference				operator [] (std::size_t n) {
			return (*(this->_ptr + n));
		}

	};

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

}

#endif
