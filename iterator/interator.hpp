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
			if (this == &x)
				return (*this);

			this->_idx = x._idx;
			this->_con = x._con;
			return (*this);
		}

	//////////////////////////////
	// Input iterator operators //
	//////////////////////////////
	private:

		void is_input_iterator(typename ft::input_iterator_tag const &) {}

	public:

		template< class U, class Con >
			friend bool operator == (const interator<U, Con>& lhs, const interator<U, Con>& rhs);

		template< class U, class Con >
			friend bool operator != (const interator<U, Con>& lhs, const interator<U, Con>& rhs);
	
		reference	operator * () {
			this->is_input_iterator(typename ft::iterator_traits<interator>::iterator_category());
			return ((*_con)[_idx]);
		}

		pointer		operator -> () {
			this->is_input_iterator(typename ft::iterator_traits<interator>::iterator_category());
			return (this->get_ptr());
		}

	//////////////////////////////////////
	// Bidirectional iterator operators //
	//////////////////////////////////////
	private:

		void is_bidirectional_iterator(ft::bidirectional_iterator_tag const &) {}

	public:

		interator& operator -- (/* prefix */)  {
			this->is_bidirectional_iterator(typename ft::iterator_traits<interator>::iterator_category());
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
	private:

		void is_random_access_iterator(ft::random_access_iterator_tag const &) {}

	public:

		interator			operator  + (difference_type val) {
			this->is_random_access_iterator(typename ft::iterator_traits<interator>::iterator_category());
			return (interator(_idx + val, _con));
		}

		interator			operator  + (const interator& x) {
			this->is_random_access_iterator(typename ft::iterator_traits<interator>::iterator_category());
			return (interator(this->_idx + x->_idx, _con));
		}

		interator			operator  - (difference_type val) {
			this->is_random_access_iterator(typename ft::iterator_traits<interator>::iterator_category());
			return (interator(_idx - val, _con));
		}

		difference_type		operator  - (const interator& x) {
			this->is_random_access_iterator(typename ft::iterator_traits<interator>::iterator_category());
			return (this->_idx - x._idx);
		}

		interator&			operator += (difference_type val) {
			this->is_random_access_iterator(typename ft::iterator_traits<interator>::iterator_category());
			_idx += val;
			return (*this);
		}

		interator&			operator -= (difference_type val) {
			this->is_random_access_iterator(typename ft::iterator_traits<interator>::iterator_category());
			_idx -= val;
			return (*this);
		}

		reference			operator [] (difference_type n) {
			this->is_random_access_iterator(typename ft::iterator_traits<interator>::iterator_category());
			return ((*_con)[_idx + n]);
		}
		
		template< class U, class Con >
			friend bool operator  < (const interator<U, Con>& lhs, const interator<U, Con>& rhs);

		template< class U, class Con >
			friend bool operator <= (const interator<U, Con>& lhs, const interator<U, Con>& rhs);

		template< class U, class Con >
			friend bool operator  > (const interator<U, Con>& lhs, const interator<U, Con>& rhs);

		template< class U, class Con >
			friend bool operator >= (const interator<U, Con>& lhs, const interator<U, Con>& rhs);

	///////////////////////////////////
	// implicit conversion operators //
	///////////////////////////////////
	public:
	
		operator const_iter () const
		{
			return (const_iter(_idx, _con));
		}

	}; /* end of interator */

///////////////////////
// Allied opperators //
///////////////////////

	template< class U, class Con >
		bool operator == (const ft::interator<U, Con>& lhs, const ft::interator<U, Con>& rhs)
	{
		return (lhs._idx == rhs._idx && lhs._con == rhs._con);			
	}

	template< class U, class Con >
		bool operator != (const ft::interator<U, Con>& lhs, const ft::interator<U, Con>& rhs) 
	{
		return (!(lhs == rhs));
	}

	template< class U, class Con >
		bool operator  < (const ft::interator<U, Con>& lhs, const ft::interator<U, Con>& rhs)
	{
		return (lhs._idx < rhs._idx && lhs._con == rhs._con);			
	}

	template< class U, class Con >
		bool operator <= (const ft::interator<U, Con>& lhs, const ft::interator<U, Con>& rhs)
	{
		return (lhs._idx <= rhs._idx && lhs._con == rhs._con);			
	}

	template< class U, class Con >
		bool operator  > (const ft::interator<U, Con>& lhs, const ft::interator<U, Con>& rhs)
	{
		return !(lhs <= rhs);
	}

	template< class U, class Con >
		bool operator >= (const ft::interator<U, Con>& lhs, const ft::interator<U, Con>& rhs)
	{
		return !(lhs < rhs);
	}

} /* end of namespace */

#endif
