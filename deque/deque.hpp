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

#ifndef DEQUE_HPP
# define DEQUE_HPP

#include <memory>
#include <array_iterator.hpp>

namespace ft
{

////////////////
// NODE CLASS //
////////////////

	# define NODE_CAPACITY 16

	template < class T, class Alloc = std::allocator<T> >
		class deque_node {
			
	///////////////
	// type defs //
	///////////////
		public:

			typedef T				value_type;
			typedef Alloc			allocator_type;
			typedef T*				pointer;
			typedef T&				reference;
			typedef std::size_t		size_type;
			typedef deque_node*		node_pointer;
		
	//////////////////////
	// member variables //
	//////////////////////
		private: 
		
			allocator_type	_alloc;
			node_pointer	_next;
			node_pointer	_prev;
			pointer			_arr;
			size_type		_size;
			size_type		_capacity;
	
	/////////////
	// CoPlIeN //
	/////////////
		public:

			deque_node(node_pointer next = NULL, node_pointer prev = NULL)
				: _next(next), _prev(prev), _size(0), _capacity(NODE_CAPACITY)
			{
				_arr = _alloc.allocate(sizeof(T) * _capacity);
			}

			~deque_node ()
			{
				this->_clear();
			}

			deque_node(const deque_node &x)
			{
				_arr = _alloc.allocate(sizeof(T) * _capacity);
				*this = x;
			}

			deque_node operator = (const deque_node &x)
			{
				this->_destroy_elements();
				for (size_t i = 0; i < x._size; i++)
					this->_alloc.construct(&_arr[i], x._arr[i]);
				this->_size		= x._size;
				this->_capacity	= x._capacity;
				this->_next		= x._next;
				this->_prev		= x._prev;
			}

	//////////////////////////////
	// PRIVATE MEMBER FUNCTIONS //
	//////////////////////////////
		private:
			
			void	_destroy_elements()
			{
				for (; _size > 0; _size--)
					_arr.destroy(&_arr[_size - 1]);
			}

			void	_clear()
			{
				this->_destroy_elements();
				if (_arr)
				{
					_arr.deallocate(_arr, _capacity);
					_arr = NULL;
				}
			}

			void	_move_elements()
			{
				for (size_t i = _size; i > 0; i--)
				{
					_alloc.construct(&_arr[i], _arr[i - 1]);
					_alloc.destroy(&_arr[i - 1]);
				}
			}

	/////////////////////////////
	// PUBLIC MEMBER FUNCTIONS //
	/////////////////////////////
		public:

			node_pointer	add_front(value_type val)
			{
				if (_size == _capacity)
				{
					_prev = _alloc.allocate(sizeof(deque_node));
					_alloc.construct(_prev, deque_node(this, NULL));
					_prev->add_front(val);
					return (_prev);
				}
				else 
				{
					this->_move_elements();
					_alloc.construct(&_arr[_size], val);
					_size++;
					return (this);
				}
			}

			node_pointer	add_back(value_type val)
			{
				if (_size == _capacity)
				{
					_next = _alloc.allocate(sizeof(deque_node));
					_alloc.construct(_next, deque_node(NULL, this));
					_next->add_back(val);
					return (_next);
				}
				else 
				{
					_alloc.construct(&_arr[_size], val);
					_size++;
					return (this);
				}
			}

			/* fill range */
			node_pointer	add_range_front(size_type n, value_type val)
			{
				node_pointer ret = this;
			
				for (; n > 0; n--)
					node_pointer = add_front(val);
				return (ret);
			}

			/* iterator range */
			template <class InputIterator>
				node_pointer	add_range_front(InputIterator first, InputIterator last)
			{
				node_pointer ret = this;
			
				for (; first != last; last--)
					node_pointer = add_front(*last);
				return (ret);
			}

			/* fill range */
			node_pointer	add_range_back(size_type n, value_type val)
			{
				node_pointer ret = this;

				for (; n > 0; n--)
					ret = add_back(val);
				return (ret);
			}

			/* iterator range */
			template <class InputIterator>
				node_pointer	add_range_back(InputIterator first, InputIterator last)
			{
				node_pointer ret = this;
			
				for (; first != last; first++)
					node_pointer = add_back(*first);
				return (ret);
			}
		
		////////////////////
		// ELEMENT ACCESS //
		////////////////////
		public:

			reference		operator[](size_type n)
			{
				return (_arr[n]);
			}

			const_reference	operator[](size_type n) const
			{
				return (_arr[n]);
			}

	}; /* end of node class */

/////////////////
// DEQUE CLASS //
/////////////////

	template < class T, class Alloc = std::allocator<T> >
		class deque {

	///////////////
	// type defs //
	///////////////
		public:

			typedef T																							value_type;
			typedef Alloc																						allocator_type;
			typedef std::size_t																					size_type;
			typedef std::ptrdiff_t																				difference_type;
			typedef value_type&																					reference;
			typedef const value_type&																			const_reference;
			typedef value_type*																					pointer;
			typedef const value_type*																			const_pointer;
			typedef deque_node*																					node_pointer;

			/* GA EEN NODE ITERATOR SCHRIJVEN */
			typedef ft::array_iterator<T, ft::random_access_iterator_tag>										iterator;
			typedef ft::array_iterator<T, ft::random_access_iterator_tag, std::ptrdiff_t, const T*, const T&>	const_iterator;
			typedef ft::reverse_iterator< iterator >															reverse_iterator;
			typedef ft::reverse_iterator< const_iterator >														const_reverse_iterator;

	//////////////////////
	// Member variables //
	//////////////////////
		private:

			node_pointer	_head;
			node_pointer	_tail;
			size_type		_size;

	/////////////
	// CoPliEn //
	/////////////
		public:

			/* default constructor */
			explicit deque (const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _head(NULL), _tail(NULL)
			{
				this->_allocate_head();
			}

			explicit deque (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _head(NULL), _tail(NULL)
			{
				this->_allocate_head();
				_tail = _head->add_range_back(val);
			}

			template <class InputIterator>
				deque (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
					: _alloc(alloc), _head(NULL), _tail(NULL)
			{
				this->_allocate_head();
				_tail = _head->add_range_back(first, last);
			}

			deque (const deque& x)
			{
				*this = x;
			}

			deque& operator = (const deque& x)
			{
				this->_clear();
				this->_alloc = x._alloc;
				this->_size	= x._size;
			}

	//////////////////////////////
	// Private member functions //
	//////////////////////////////
		private:

			void	_allocate_head()
			{
				_head = _alloc.allocate(sizeof(deque_node));
				_alloc.construct(&_head, deque_node());
			}

	}; /* end of deque */

} /* end of namespace */

#endif
