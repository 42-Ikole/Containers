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

/////////////////
// DEQUE CLASS //
/////////////////

	template < class T, class Alloc = std::allocator<T> >
		class deque {

	#define NODE_CAPACITY	16

	//////////
	// node //
	//////////
	private:

		struct node
		{
		
	///////////////
	// type defs //
	///////////////
		private:

			typedef	T				value_type;
			typedef T*				pointer;
			typedef const T*		const_pointer;
			typedef	T&				reference;
			typedef const T&		const_reference;
			typedef std::size_t		size_type;
			typedef node*			node_pointer;
			typedef Alloc			allocator_type;
			
	//////////////////////
	// member variables //
	//////////////////////
		private:

			node_pointer	_next;
			node_pointer	_prev;
			pointer			_arr;
			size_type		_size;
			allocator_type	_alloc;

	/////////////////////
	// BOB THE BUILDER //
	/////////////////////
		public:

			node(node_pointer next = NULL, node_pointer prev = NULL)
				: _next(next), _prev(prev), _arr(NULL), _size(0)
			{
				_arr = _alloc.allocate(sizeof(value_type) * NODE_CAPACITY);
			}

			~node()
			{
				this->_clear();
			}

			node operator = (const node &x)
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
					_alloc.destroy(&_arr[_size - 1]);
			}

			void	_clear()
			{
				this->_destroy_elements();
				if (_arr)
				{
					_alloc.deallocate(_arr, NODE_CAPACITY);
					_arr = NULL;
				}
			}

			void	_move_elements_forward()
			{
				for (size_t i = _size; i > 0; i--)
				{
					_alloc.construct(&_arr[i], _arr[i - 1]);
					_alloc.destroy(&_arr[i - 1]);
				}
			}

			void	_move_elements_back()
			{
				for (size_t i = 0; i < _size; i++)
				{
					_alloc.construct(&_arr[i], _arr[i + 1]);
					_alloc.destroy(&_arr[i + 1]);
				}
			}

	/////////////////////////////
	// PUBLIC MEMBER FUNCTIONS //
	/////////////////////////////
		public:

			node_pointer	add_front(value_type val)
			{
				if (_size == NODE_CAPACITY)
				{
					_prev = _alloc.allocate(sizeof(node));
					_alloc.construct(_prev, node(this, NULL));
					_prev->add_front(val);
					return (_prev);
				}
				else 
				{
					this->_move_elements_forward();
					_alloc.construct(&_arr[_size], val);
					_size++;
					return (this);
				}
			}

			node_pointer	add_back(value_type val)
			{
				if (_size == NODE_CAPACITY)
				{
					_next = _alloc.allocate(sizeof(node));
					_alloc.construct(_next, node(NULL, this));
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
					ret = this->add_front(val);
				return (ret);
			}

			/* iterator range */
			template <class InputIterator>
				node_pointer	add_range_front(InputIterator first, InputIterator last)
			{
				node_pointer ret = this;
			
				for (; first != last; last--)
					ret = this->add_front(*last);
				return (ret);
			}

			/* fill range */
			node_pointer	add_range_back(size_type n, value_type val)
			{
				node_pointer ret = this;

				for (; n > 0; n--)
					ret = this->add_back(val);
				return (ret);
			}

			/* iterator range */
			template <class InputIterator>
				node_pointer	add_range_back(InputIterator first, InputIterator last)
			{
				node_pointer ret = this;
			
				for (; first != last; first++)
					ret = this->add_back(*first);
				return (ret);
			}


			void	pop_back()
			{
				if (_size <= 0)
					return ;
				_size--;
				_alloc.destroy(&_arr[_size]);
			}

			void	pop_front()
			{
				if (_size <= 0)
					return ;
				_size--;
				_alloc.destroy(&_arr[0]);
				this->_move_elements_back();
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

		}; /* end of node */

///////////
// DEQUE //
///////////

	///////////////
	// type defs //
	///////////////
		public:

			typedef T																							value_type;
			typedef std::allocator<node>																		allocator_type;
			typedef std::size_t																					size_type;
			typedef std::ptrdiff_t																				difference_type;
			typedef value_type&																					reference;
			typedef const value_type&																			const_reference;
			typedef value_type*																					pointer;
			typedef const value_type*																			const_pointer;
			typedef node*																						node_pointer;

			/* GA EEN NODE ITERATOR SCHRIJVEN */
			typedef ft::array_iterator<T, ft::random_access_iterator_tag>										iterator;
			typedef ft::array_iterator<T, ft::random_access_iterator_tag, std::ptrdiff_t, const T*, const T&>	const_iterator;
			typedef ft::reverse_iterator< iterator >															reverse_iterator;
			typedef ft::reverse_iterator< const_iterator >														const_reverse_iterator;

	//////////////////////
	// Member variables //
	//////////////////////
		private:

			allocator_type	_alloc;
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
				_head = this->_allocate_node();
				_tail = _head;
			}

			explicit deque (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _head(NULL), _tail(NULL)
			{
				_head = this->_allocate_node();
				_tail = _head->add_range_back(n, val);
			}

			template <class InputIterator>
				deque (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
					: _alloc(alloc), _head(NULL), _tail(NULL)
			{
				_head = this->_allocate_node();
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
				for (node i = x._head; i != x._tail; i = i->next)
					this->_add_node_back(*i);
			}

	//////////////////////////////
	// Private member functions //
	//////////////////////////////
		private:

			node_pointer	_allocate_node(const node& new_node = node())
			{
				node_pointer ret;

				ret = _alloc.allocate(sizeof(node));
				_alloc.construct(ret, new_node);
				return (ret);
			}

			void			_add_node_front(node& new_node)
			{
				_head = _head->add_front(new_node);
			}

			void			_add_node_back(node& new_node)
			{
				_tail = _tail->add_back(new_node);
			}

	///////////////
	// ITERATORS //
	///////////////
		public:

			iterator				begin() {
				return (iterator(_head));
			}

			const_iterator			begin() const {
				return (const_iterator(_head));
			}
	
			iterator				end() {
				return (iterator(_tail));
			}

			const_iterator			end() const {
				return (const_iterator(_tail));
			}

			reverse_iterator		rbegin() {
				return (reverse_iterator(_tail));
			}

			const_reverse_iterator	rbegin() const {
				return (const_reverse_iterator(_tail));
			}

			reverse_iterator		rend() {
				return (reverse_iterator(_head));
			}

			const_reverse_iterator	rend() const {
				return (const_reverse_iterator(_head));
			}

	//////////////
	// CAPACITY //
	//////////////
		public:

			size_type	size() const
			{
				return (_size);
			}

			size_type	max_size() const
			{
				return (_alloc.max_size());
			}

			void		resize(size_type n, value_type val = value_type())
			{
				if (n <= _size) {
					for (size_type i = _size; i > n; i--)
						_tail->pop_back();
				}
				else {
					this->_resize(n);
					for (size_type i = _size; i < n; i++)
						this->push_back(val);
				}
			}

			bool		empty() const
			{
				return (_size == 0);
			}

		#undef NODE_CAPACITY	

	}; /* end of deque */

} /* end of namespace */

#endif
