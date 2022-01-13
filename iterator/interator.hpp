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

#ifndef INTERATOR_HPP
# define INTERATOR_HPP

# include <iterator_traits.hpp>
# include <iterator.hpp>
# include <sfinae.hpp>

namespace ft {

//////////////////////
// interator  class //
//////////////////////

	/* wont get invalidated on reallocation! */
	template < class T, class Container, class Category = ft::random_access_iterator_tag, 
		class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T& >
			struct interator : ft::iterator<Category, T, Distance, Pointer, Reference>
	{

	//////////////
	// Typedefs //
	//////////////
	private:

		typedef ft::interator< Category, T, Distance, const T*, const T& >	const_iter;

	public:

		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Container	container_type;
		typedef Pointer		pointer;
		typedef Reference	reference;

	//////////////////////
	// Member variables //
	//////////////////////
	protected:

		difference_type	_idx;
		container_type*	_con;	

	/////////////////
	// constructor //
	/////////////////
	private:

		void is_forward_iterator(typename ft::forward_iterator_tag const &) {}

	public:

		interator(difference_type idx, container_type* con)
			: _idx(idx), _con(con) {}

		interator() : _idx(0), _con(NULL)
		{
			this->is_forward_iterator(typename ft::iterator_traits<interator>::iterator_category());
		}

		interator(const interator& x) {
			*this = x;
		}

		virtual ~interator() {}

	/////////////////
	// Get pointer //
	/////////////////
	public:

		pointer	get_ptr(void)
		{
			return (&((*_con)[_idx]));
		}

	//////////////////////
	// Common operators //
	//////////////////////
	public:

		interator&	operator ++ (/* prefix */) {
			_idx++;
			return (*this);
		}

		interator	operator ++ (int /* postfix */) {
			interator tmp = *this;
			++(*this);
			return (tmp);
		}

		interator&	operator  = (const interator& x) {
			this->_idx = x._idx;
			this->_con = x._con;
			return (*this);
		}

	//////////////////////////////
	// Input iterator operators //
	//////////////////////////////

	public:

		bool 		operator == (const interator& x) {
			return (this->_idx == x._idx && this->_con == x._con);			
		}

		bool		operator != (const interator& x) {
			return (!(*this == x));
		}
	
		reference	operator * () {
			return ((*_con)[_idx]);
		}

		pointer		operator -> () {
			return (this->get_ptr());
		}

	//////////////////////////////////////
	// Bidirectional iterator operators //
	//////////////////////////////////////
	public:

		interator& operator -- (/* prefix */)  {
			_idx--;
			return (*this);
		}

		interator operator -- (int /* postfix */) {
			interator tmp = *this;
			--(*this);
			return (tmp);
		}

	//////////////////////////////////////
	// Random access iterator operators //
	//////////////////////////////////////
	public:

		interator			operator  + (difference_type val) {
			return (interator(_idx + val, _con));
		}

		interator			operator  + (const interator& x) {
			return (interator(this->_idx + x->_idx, _con));
		}

		interator			operator  - (difference_type val) {
			return (interator(_idx - val, _con));
		}

		difference_type		operator  - (const interator& x) {
			return (this->_idx - x._idx);
		}

		bool				operator  < (const interator& x) {
			return (this->_idx < x._idx);
		}

		bool				operator  > (const interator& x) {
			return (this->_idx > x->_idx);
		}

		bool				operator <= (const interator& x) {
			return (this->_idx <= x._idx);
		}

		bool				operator >= (const interator& x) {
			return (this->_idx >= x._idx);
		}

		interator&			operator += (difference_type val) {
			_idx += val;
			return (*this);
		}

		interator&			operator -= (difference_type val) {
			_idx -= val;
			return (*this);
		}

		reference			operator [] (difference_type n) {
			return ((*_con)[_idx + n]);
		}

	///////////////////////////////////
	// implicit conversion operators //
	///////////////////////////////////
	public:
	
		operator const_iter () const
		{
			return (const_iter(_idx, _con));
		}

	}; /* end of interator */

} /* end of namespace */

#endif
