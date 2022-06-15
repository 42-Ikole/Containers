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

# include <iterator_traits.hpp>
# include <iterator.hpp>
# include <sfinae.hpp>

namespace ft {

/////////////////////////
// node iterator class //
/////////////////////////

	template < class Category, class T, class Base = T,
		class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T& >
			struct node_iterator : ft::iterator<Category, T, Distance, Pointer, Reference>
	{

	//////////////
	// Typedefs //
	//////////////
	public:

		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Base*		base_ptr;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef ft::node_iterator< Category, T, Base, Distance, const T*, const T& >	const_iter;

	//////////////////////
	// Member variables //
	//////////////////////
	protected:
		base_ptr	_ptr;

	/////////////////
	// constructor //
	/////////////////
	private:

		void is_forward_iterator(typename ft::forward_iterator_tag const &) {}

	public:

		node_iterator(base_ptr ptr) : _ptr(ptr) {}

		node_iterator() : _ptr(NULL)
		{
			this->is_forward_iterator(typename ft::iterator_traits<node_iterator>::iterator_category());
		}

		node_iterator(const node_iterator& x) {
			*this = x;
		}

		virtual ~node_iterator() {}

	/////////////////
	// Get pointer //
	/////////////////
	public:

		base_ptr	get_ptr(void)
		{
			return (_ptr);
		}

	//////////////////////
	// Common operators //
	//////////////////////
	public:

		node_iterator&	operator ++ (/* prefix */) {
			_ptr = _ptr->get_successor();
			return (*this);
		}

		node_iterator	operator ++ (int /* postfix */) {
			node_iterator tmp = *this;
			++(*this);
			return (tmp);
		}

		node_iterator&	operator  = (const node_iterator& x) {
			if (this == &x)
				return (*this);

			this->_ptr = x._ptr;
			return (*this);
		}

	//////////////////////////////
	// Input iterator operators //
	//////////////////////////////
	private:

		void is_input_iterator(typename ft::input_iterator_tag const &) {}

	public:

		template< class C, class U, class B >
			friend bool operator == (const node_iterator<C, U, B>& lhs, const node_iterator<C, U, B>& rhs);

		template< class C, class U, class B >
			friend bool operator != (const node_iterator<C, U, B>& lhs, const node_iterator<C, U, B>& rhs);
	
		reference operator * ()
		{
			this->is_input_iterator(typename ft::iterator_traits<node_iterator>::iterator_category());
			return (**_ptr);
		}

		pointer operator -> () 
		{
			this->is_input_iterator(typename ft::iterator_traits<node_iterator>::iterator_category());
			return &(_ptr->value);
		}

	//////////////////////////////////////
	// Bidirectional iterator operators //
	//////////////////////////////////////
	private:

		void is_bidirectional_iterator(ft::bidirectional_iterator_tag const &) {}

	public:

		node_iterator& operator -- (/* prefix */)
		{
			this->is_bidirectional_iterator(typename ft::iterator_traits<node_iterator>::iterator_category());
			_ptr = _ptr->get_predecessor();
			return (*this);
		}

		node_iterator operator -- (int /* postfix */)
		{
			this->is_bidirectional_iterator(typename ft::iterator_traits<node_iterator>::iterator_category());
			node_iterator tmp = *this;
			--(*this);
			return (tmp);
		}

	///////////////////////////////////
	// implicit conversion operators //
	///////////////////////////////////
	public:
	
		operator const_iter () const
		{
			return (const_iter(_ptr));
		}

	}; /* end of node iterator */

///////////////////////
// Comrade operators //
///////////////////////

	template< class C, class U, class B >
		bool operator == (const ft::node_iterator<C, U, B>& lhs, const ft::node_iterator<C, U, B>& rhs)
	{
		return (lhs._ptr == rhs._ptr);
	}

	template< class C, class U, class B >
		bool operator != (const ft::node_iterator<C, U, B>& lhs, const ft::node_iterator<C, U, B>& rhs)
	{
		return !(lhs == rhs);
	}

} /* end of namespace */

#endif
