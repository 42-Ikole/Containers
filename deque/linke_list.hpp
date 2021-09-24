/* ************************************************************************** */
/*                                                                            */
/*                    888                                                     */
/*               e88~\888  e88~~8e   e88~-888 888  888  e88~~8e               */
/*              d888  888 d888  88b d888  888 888  888 d888  88b              */
/*              8888  888 8888__888 8888  888 888  888 8888__888              */
/*              Y888  888 Y888    , Y888  888 888  888 Y888    ,              */
/*               "88_/888  "88___/   "88_-888 "88_-888  "88___/               */
/*                                        888                                 */
/*																			  */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*																			  */
/* ************************************************************************** */

#ifndef LINKE_LIST_HPP
# define LINKE_LIST_HPP

# include <memory>
# include <circular_buffer.hpp>

namespace ft
{

////////////////
// LINKE LIST //
////////////////

	template < class T, class Alloc = std::allocator<T> >
		struct linke_list
	{
	///////////////
	// TYPE DEFS //
	///////////////
	public:

		typedef T												value_type;
		typedef Alloc											allocator_type;
		typedef std::size_t										size_type;
		typedef std::ptrdiff_t									difference_type;
		typedef value_type&										reference;
		typedef const value_type&								const_reference;
		typedef value_type*										pointer;
		typedef const value_type*								const_pointer;
		typedef	std::allocator<linke_list<T> >					node_allocator_type;
		typedef	linke_list<T>*									node_pointer;
		typedef	circular_buffer< value_type, allocator_type >	cbuf;

	//////////////////////
	// Member variables //
	//////////////////////
	public:

		node_allocator_type _node_allocator;
		node_pointer		_next;
		node_pointer		_prev;
		cbuf				_elements;

	/////////////
	// CoPlIeN //
	/////////////
	public:

		linke_list(node_pointer	next = NULL, node_pointer prev = NULL)
			: _next(next), _prev(prev), _elements(cbuf())
		{
		}

		~linke_list()
		{
			this->clear();
		}

		linke_list(const linke_list& x)
			: _elements(cbuf())
		{
			*this = x;
		}

		linke_list& operator = (const linke_list &x)
		{
			this->_next		= x._next;
			this->_prev		= x._prev;
			// this->_elements	= x._elements;
			return (*this);
		}
	//////////////////////////////
	// PRIVATE MEMBER FUNCTIONS //
	//////////////////////////////
	private:

		void	_allocate_node(node_pointer& location, const linke_list& val)
		{
			location = _node_allocator.allocate(1);
			_node_allocator.construct(location, val);
		}

	//////////////
	// CAPACITY //
	//////////////
	public:

		size_type	size()
		{
			return (_elements.size());
		}

	///////////////
	// MODIFIERS //
	///////////////
	public:

		node_pointer	push_front(reference val)
		{
			if (_elements.is_full() == true)
			{
				this->_allocate_node(_prev, linke_list(NULL, this));
				_prev->_elements.emplace_front(val);
				return (_prev);
			}
			_elements.emplace_front(val);
			return (this);
		}

		node_pointer	push_back(reference val)
		{
			if (_elements.is_full() == true)
			{
				this->_allocate_node(_next, linke_list(this, NULL));
				_next->_elements.emplace_back(val);
				return (_next);
			}
			_elements.emplace_back(val);
			return (this);
		}

		/* fill range */
		node_pointer	add_range_front(size_type n, reference val)
		{
			node_pointer ret = this;
		
			for (; n > 0; n--)
				ret = this->push_front(val);
			return (ret);
		}

		/* iterator range */
		template <class InputIterator>
			node_pointer	add_range_front(InputIterator first, InputIterator last)
		{
			node_pointer ret = this;
		
			for (; first != last; last--)
				ret = this->push_front(*last);
			return (ret);
		}

		/* fill range */
		node_pointer	add_range_back(size_type n, reference val)
		{
			node_pointer ret = this;

			for (; n > 0; n--)
				ret = this->push_back(val);
			return (ret);
		}

		/* iterator range */
		template <class InputIterator>
			node_pointer	add_range_back(InputIterator first, InputIterator last)
		{
			node_pointer ret = this;
		
			for (; first != last; first++)
				ret = this->push_back(*first);
			return (ret);
		}

		void			pop_front()
		{
			_elements.dequeue_front();
		}

		void			pop_back()
		{
			_elements.dequeue_back();
		}

		void		clear()
		{
			
		}

	////////////////////
	// ELEMENT ACCESS //
	////////////////////
	public:

		reference		operator[](size_type n)
		{
			return (_elements[n]);
		}

		const_reference	operator[](size_type n) const
		{
			return (_elements[n]);
		}
		
	}; /* end of linke list */


} /* end of namespace */

#endif
