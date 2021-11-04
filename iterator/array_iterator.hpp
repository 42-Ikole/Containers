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

#ifndef ARRAY_ITERATOR_HPP
# define ARRAY_ITERATOR_HPP

# include <cstddef>
# include <traits.hpp>
# include <rotareti.hpp>
# include <iterator.hpp>

namespace ft {

////////////////////////////
// Pointer iterator class //
////////////////////////////
	# define itr	ft::iterator< Category, T, Distance, Pointer, Reference >

	template < class T, class Category = ft::random_access_iterator_tag,
		class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	class array_iterator : public ft::iterator < Category, T, Distance, Pointer, Reference >
	{
	//////////////
	// Typedefs //
	//////////////
	private:

		typedef ft::array_iterator < T, Category, Distance, T*, T& >				iter;
		typedef ft::array_iterator < T, Category, Distance, const T*, const T& >	const_iter;
	
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

		array_iterator(Pointer ptr = NULL) : _ptr(ptr) {}

		array_iterator(const array_iterator& x) {
			*this = x;
		}

		virtual ~array_iterator() {}

	//////////////////////
	// Common operators //
	//////////////////////
	public:

		array_iterator&	operator ++ (/* prefix */) {
			_ptr++;
			return (*this);
		}

		array_iterator	operator ++ (int /* postfix */) {
			array_iterator tmp = *this;
			++(*this);
			return (tmp);
		}

		array_iterator&	operator  = (const array_iterator& x) {
			this->_ptr = x._ptr;
			return (*this);
		}

	////////////////////////////////////
	// Input array_iterator operators //
	////////////////////////////////////
	public:

		bool		operator == (const array_iterator& x) {
			return (this->_ptr == x._ptr);			
		}

		bool		operator != (const array_iterator& x) {
			return (this->_ptr != x._ptr);
		}
	
		reference	operator * () {
			return *(this->_ptr);
		}

		pointer		operator -> () {
			return (this->_ptr);
		}
	
	////////////////////////////////////////////
	// Bidirectional array_iterator operators //
	////////////////////////////////////////////
	public:
	
		array_iterator&	operator -- (/* prefix */) {
			this->_ptr--;
			return (*this);
		}

		array_iterator	operator -- (int /* postfix */) {
			array_iterator tmp = *this;
			--(*this);
			return (tmp);
		}

	////////////////////////////////////////////
	// Random access array_iterator operators //
	////////////////////////////////////////////
	public:

		array_iterator	operator  + (difference_type val) {
			return (array_iterator(this->_ptr + val));
		}

		array_iterator	operator  + (const array_iterator& x) {
			return (array_iterator(*this + x));
		}

		array_iterator	operator  - (difference_type val) {
			return (array_iterator(this->_ptr - val));
		}

		difference_type	operator  - (const array_iterator& x) {
			return (this->_ptr - x._ptr);
		}

		bool			operator  < (const array_iterator& x) {
			return (this->_ptr < x._ptr);
		}

		bool			operator  > (const array_iterator& x) {
			return (this->_ptr > x._ptr);
		}

		bool			operator <= (const array_iterator& x) {
			return (this->_ptr <= x._ptr);
		}

		bool			operator >= (const array_iterator& x) {
			return (this->_ptr >= x._ptr);
		}

		array_iterator&	operator += (difference_type val) {
			this->_ptr += val;
			return (*this);
		}

		array_iterator&	operator -= (difference_type val) {
			this->_ptr -= val;
			return (*this);
		}

		reference		operator [] (std::size_t n) {
			return (*(this->_ptr + n));
		}

///////////////////////////////////
// implicit conversion operators //
///////////////////////////////////
	public:
	
		operator const_iter() const
		{
			return (const_iter(this->_ptr));
		}

		operator iter() const
		{
			return (iter(this->_ptr));
		}

	}; /* end of iterator class */
 
	# undef itr

} /* end of namespace */

#endif
