/* ************************************************************************** */
/*                                                                            */
/*               .-')    .-') _      ('-.               .-. .-')              */ 
/*              ( OO ). (  OO) )    ( OO ).-.           \  ( OO )             */ 
/*             (_)---\_)/     '._   / . --. /   .-----. ,--. ,--.             */ 
/*             /    _ | |'--...__)  | \-.  \   '  .--./ |  .'   /             */ 
/*             \  :` `. '--.  .--'.-'-'  |  |  |  |('-. |      /,             */ 
/*              '..`''.)   |  |    \| |_.'  | /_) |OO  )|     ' _)            */ 
/*             .-._)   \   |  |     |  .-.  | ||  |`-'| |  .   \              */ 
/*             \       /   |  |     |  | |  |(_'  '--'\ |  |\   \             */ 
/*              `-----'    `--'     `--' `--'   `-----' `--' '--'             */ 
/*																			  */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*																			  */
/* ************************************************************************** */

#ifndef VERY_NICE_STACK_CLASS_BRO_HPP
# define VERY_NICE_STACK_CLASS_BRO_HPP

# include <deque.hpp>

namespace ft
{

/////////////////
// Stack class //
/////////////////

	template <class T, class Container = ft::deque<T> >
		class stack
	{

	///////////////
	// type defs //
	///////////////
	public:

		typedef T											value_type;
		typedef Container									container_type;
		typedef typename container_type::allocator_type		allocator_type;
		typedef typename container_type::size_type			size_type;
		typedef typename container_type::difference_type	difference_type;
		typedef typename container_type::reference			reference;
		typedef typename container_type::const_reference	const_reference;
		typedef typename container_type::pointer			pointer;
		typedef typename container_type::const_pointer		const_pointer;

		/* Hippity hopptiy these iterators are now my property */
		typedef typename container_type::iterator				iterator;
		typedef typename container_type::const_iterator			const_iterator;
		typedef typename container_type::reverse_iterator		reverse_iterator;
		typedef typename container_type::const_reverse_iterator	const_reverse_iterator;


	//////////////////////
	// Member variables //
	//////////////////////
	protected:

		container_type	c;

	
	////////////////////////
	// Under Construction //
	////////////////////////
	public:
	
		explicit stack (const container_type& container = container_type())
			: c(container)
		{}

		~stack()
		{}

		stack& operator = (const stack& x)
		{
			this->c = x.c;
		}
	////////////////////
	// Element access //
	////////////////////
	public:

		reference top()
		{
			return (this->c.back());
		}

		const_reference top() const
		{
			return (this->c.back());
		}

	//////////////
	// Capacity // 
	//////////////
	public:

		bool empty() const
		{
			return (c.empty());
		}

		size_type size() const
		{
			return (c.size());
		}

	///////////////
	// Modifiers //
	///////////////
	public:

		void push(const value_type& value)
		{
			c.push_back(value);
		}

		void pop()
		{
			c.pop_back();
		}

	////////////////////////
	// Friendly operators //
	////////////////////////
	public:

		friend bool operator == (const stack& lhs, const stack& rhs);
		friend bool operator != (const stack& lhs, const stack& rhs);
		friend bool operator  < (const stack& lhs, const stack& rhs);
		friend bool operator <= (const stack& lhs, const stack& rhs);
		friend bool operator  > (const stack& lhs, const stack& rhs);
		friend bool operator >= (const stack& lhs, const stack& rhs);

	}; /* end of stack class */

//////////////
// FRENS!!! //
//////////////

	template< class T, class Container >
		bool operator == (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
			return (lhs.c == rhs.c);
	}

	template< class T, class Container >
		bool operator != (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
			return (lhs.c != rhs.c);
	}

	template< class T, class Container >
		bool operator  < (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
			return (lhs.c < rhs.c);
	}

	template< class T, class Container >
		bool operator <= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
			return (lhs.c <= rhs.c);
	}

	template< class T, class Container >
		bool operator  > (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
			return (lhs.c > rhs.c);
	}

	template< class T, class Container >
		bool operator >= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
			return (lhs.c >= rhs.c);
	}

}/* end of namespace */

#endif
