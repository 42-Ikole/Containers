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

# include <vector.hpp>

namespace ft
{

/////////////////
// Stack class //
/////////////////

	template <class T, class Container = ft::vector<T> >
		class stack
	{

	///////////////
	// type defs //
	///////////////
	public:

		typedef T											value_type;
		typedef Container									container_type;
		typedef typename container_type::size_type			size_type;
		typedef typename container_type::reference			reference;
		typedef typename container_type::const_reference	const_reference;
		typedef typename container_type::pointer			pointer;
		typedef typename container_type::const_pointer		const_pointer;

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
			return *(this);
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
