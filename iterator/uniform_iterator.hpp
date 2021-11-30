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

#ifndef I_HOPE_THIS_IS_GOING_TO_WORK_HPP
# define I_HOPE_THIS_IS_GOING_TO_WORK_HPP

# include <traits.hpp>
# include <rotareti.hpp>

namespace ft {

/////////////////////////
// Iterator base class //
/////////////////////////

	template < class Category, class T, class Base = T*,
		class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T& >
			struct uniform_iterator
	{

	//////////////
	// Typedefs //
	//////////////
	private:

		/* yuck */
		typedef	ft::uniform_iterator< Category, T, Base, Distance, Pointer, Reference >				iter;
		typedef ft::uniform_iterator< Category, T, Base, Distance, const Pointer, const Reference >	const_iter;

	public:

		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Base		base_ptr;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;

	//////////////////////
	// Member variables //
	//////////////////////
	protected:
		base_ptr	_ptr;

	/////////////////
	// constructor //
	/////////////////
	public:

		uniform_iterator(base_ptr ptr = NULL) : _ptr(ptr) {}

		uniform_iterator(const uniform_iterator& x) {
			*this = x;
		}

		virtual ~uniform_iterator() {}

	//////////////////////
	// Common operators //
	//////////////////////
	public:

		uniform_iterator&	operator ++ (/* prefix */) {
			++_ptr;
			return (*this);
		}

		uniform_iterator	operator ++ (int /* postfix */) {
			uniform_iterator tmp = *this;
			++(*this);
			return (tmp);
		}

		uniform_iterator&	operator  = (const uniform_iterator& x) {
			this->_ptr = x._ptr;
			return (*this);
		}

	//////////////////////////////
	// Input iterator operators //
	//////////////////////////////
	public:

		bool		operator == (const uniform_iterator& x) {
			return (this->_ptr == x._ptr);			
		}

		bool		operator != (const uniform_iterator& x) {
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
	public:
	
		uniform_iterator&	operator -- (/* prefix */) {
			--_ptr;
			return (*this);
		}

		uniform_iterator	operator -- (int /* postfix */) {
			uniform_iterator tmp = *this;
			--(*this);
			return (tmp);
		}

	//////////////////////////////////////
	// Random access iterator operators //
	//////////////////////////////////////
	public:

		uniform_iterator	operator  + (difference_type val) {
			return (uniform_iterator(this->_ptr + val));
		}

		uniform_iterator	operator  + (const uniform_iterator& x) {
			return (uniform_iterator(*this + x));
		}

		uniform_iterator	operator  - (difference_type val) {
			return (uniform_iterator(this->_ptr - val));
		}

		difference_type		operator  - (const uniform_iterator& x) {
			return (this->_ptr - x._ptr);
		}

		bool				operator  < (const uniform_iterator& x) {
			return (this->_ptr < x._ptr);
		}

		bool				operator  > (const uniform_iterator& x) {
			return (this->_ptr > x._ptr);
		}

		bool				operator <= (const uniform_iterator& x) {
			return (this->_ptr <= x._ptr);
		}

		bool				operator >= (const uniform_iterator& x) {
			return (this->_ptr >= x._ptr);
		}

		uniform_iterator&	operator += (difference_type val) {
			_ptr += val;
			return (*this);
		}

		uniform_iterator&	operator -= (difference_type val) {
			_ptr -= val;
			return (*this);
		}

		reference			operator [] (std::size_t n) {
			return (*(_ptr + n));
		}

	///////////////////////////////////
	// implicit conversion operators //
	///////////////////////////////////
	public:
	
		operator const_iter() const
		{
			return (const_iter(_ptr));
		}

	}; /* end of uniform iterator */

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
