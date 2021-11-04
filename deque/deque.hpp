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

#ifndef SUPER_EPIC_DEQUE_HPP
# define SUPER_EPIC_DEQUE_HPP

# include <memory>
# include <array_iterator.hpp> //
# include <utility.hpp>
# include <circular_buffer.hpp>

namespace ft
{

/////////////////
// DEQUE CLASS //
/////////////////

	# define CAPACITY	128

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
		typedef circular_buffer<T>																			cbuf;
		typedef	std::allocator<cbuf>																		cbuf_allocator_type;
		typedef std::allocator<cbuf*>																		ptr_alloc;

		/* GA EEN NODE ITERATOR SCHRIJVEN */
		typedef ft::array_iterator<T, ft::random_access_iterator_tag>										iterator;
		typedef ft::array_iterator<T, ft::random_access_iterator_tag, std::ptrdiff_t, const T*, const T&>	const_iterator;
		typedef ft::reverse_iterator< iterator >															reverse_iterator;
		typedef ft::reverse_iterator< const_iterator >														const_reverse_iterator;

	//////////////////////
	// Member variables //
	//////////////////////
	private:

		cbuf_allocator_type	_alloc;
		ptr_alloc			_palloc;
		cbuf				**_arr;
		size_type			_head;
		size_type			_tail;
		size_type			_capacity;
		size_type			_size;
		size_type			_cb_cap;

	/////////////////////
	// BOB THE BUILDER //
	/////////////////////
	public:

		explicit deque (const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _palloc(ptr_alloc()), _arr(NULL), _head(0), _tail(0), _capacity(CAPACITY), _size(0)
		{
			this->_initial_alloc();
		}

		explicit deque (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _palloc(ptr_alloc()), _arr(NULL), _head(0), _tail(0), _capacity(CAPACITY), _size(0)
		{
			this->_initial_alloc();
			this->assign(n, val);
		}

		template <class InputIterator>
			deque (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _palloc(ptr_alloc()), _arr(NULL), _head(0), _tail(0), _capacity(CAPACITY), _size(0)
		{
			this->_initial_alloc();
			this->assign(first, last);
		}

		~deque()
		{
			this->clear();
			this->_destroy_element(_head);
			_palloc.deallocate(_arr, _capacity);
		}

		deque (const deque& x)
		{
			*this = x;
		}

		deque&	operator = (const deque &x)
		{
			this->_destroy_elements();
			_palloc.deallocate(_arr, _capacity);
			this->_head		= x._head;
			this->_tail		= x._tail;
			this->_capacity	= x._capacity;
			this->_alloc 	= x._alloc;
			this->_palloc	= x._palloc;
			this->_initial_alloc();
			for (size_t i = 0; i < x._size; i++)
				this->push_back(x[i]);
			return (*this);
		}

	//////////////////////////////
	// private member functions //
	//////////////////////////////
	private:

		void	_initial_alloc()
		{
			_arr = _palloc.allocate(_capacity);
			this->_construct_element(_head);
			_cb_cap = _arr[_head]->_capacity;
		}

		void	_construct_element(size_type& idx, const cbuf& val = cbuf())
		{
			_arr[idx] = _alloc.allocate(1);
			_alloc.construct(_arr[idx], val);
		}

		void	_destroy_element(size_type& idx)
		{
			_alloc.destroy(&_arr[idx][0]);
			_alloc.deallocate(_arr[idx], 1);
			_arr[idx] = NULL;
		}

		void	_destroy_elements()
		{
			while (_head != _tail) {
				this->_destroy_element(_head);
				_head++;
				if (_head == _capacity)
					_head = 0;
			}
			if (_arr[_head] != NULL)
				this->_destroy_element(_head);
		}

		void	_realloc()
		{
			cbuf	**tmp;

			tmp = _palloc.allocate(_capacity * 2);
			size_type i = 0;
			for (; i < _capacity; ++i) {
				tmp[i] = _arr[_head];
				_head++;
				if (_head == _capacity)
					_head = 0;
			}
			_tail = i - 1;
			_head = 0;
			_palloc.deallocate(_arr, _capacity);
			_capacity *= 2;
			_arr = tmp;
		}

		reference	get_val(size_type idx)
		{
			if (idx < _arr[_head]->_size)
				return (_arr[_head][0][idx]);
			else
				idx -= _arr[_head]->_size;
			size_type i = 1 + (idx / _cb_cap);
			return (_arr[(_head + i) % _capacity][0][idx]);
		}

		bool	_is_full()
		{
			return (_size == (this->_capacity * _cb_cap));
		}

	///////////////
	// ITERATORS //
	///////////////
	public:

	// iterator				begin() {
	// 	return (iterator(this->_arr));
	// }

	// const_iterator			begin() const {
	// 	return (const_iterator(this->_arr));
	// }

	// iterator				end() {
	// 	return (iterator(&this->_arr[this->_size]));
	// }

	// const_iterator			end() const {
	// 	return (const_iterator(&this->_arr[this->_size]));
	// }

	// reverse_iterator		rbegin() {
	// 	return (reverse_iterator(&this->_arr[this->_size]));
	// }

	// const_reverse_iterator	rbegin() const {
	// 	return (const_reverse_iterator(&this->_arr[this->_size]));
	// }

	// reverse_iterator		rend() {
	// 	return (reverse_iterator(this->_arr));
	// }

	// const_reverse_iterator	rend() const {
	// 	return (const_reverse_iterator(this->_arr));
	// }

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
			return (_arr[_head]->_alloc.max_size());
		}

		void		resize(size_type n, value_type val = value_type())
		{
			if (n <= _capacity) {
				for (size_type i = _size; i > n; i--)
					this->pop_back();
			}
			else {
				this->_resize(n);
				for (size_type i = _size; i < _capacity; i++)
					this->push_back(val);
			}
		}

		bool		empty() const
		{
			return (_size == 0);
		}

	////////////////////
	// ELEMENT ACCESS //
	////////////////////
	public:

		reference		operator[](size_type n)
		{
			return (get_val(n));
		}

		const_reference	operator[](size_type n) const
		{
			return (get_val(n));
		}

		reference		at(size_type n)
		{
			if (n < 0 || n >= _size)
				throw std::out_of_range("deque"); /* check deze shit neef */
			return (get_val(n));
		}

		const_reference	at(size_type n) const
		{
			if (n < 0 || n > _size)
				throw std::out_of_range("deque"); /* check deze shit neef */
			return (get_val(n));
		}

		reference		front()
		{
			return (_arr[_head][0]);
		}

		const_reference	front() const
		{
			return (_arr[_head][0]);
		}

		reference		back()
		{
			return (get_val(_size - 1));
		}

		const_reference	back() const
		{
			return (get_val(_size - 1));
		}

	///////////////
	// MODIFIERS //
	///////////////
	public:

		void assign(size_type n, const value_type& val)
		{
			this->clear();
			for (size_type i = 0; i < n; i++)
				this->push_back(val);
		}

		template <class InputIterator>
 			void assign(InputIterator first, InputIterator last,
				typename ft::iterator_traits<InputIterator>::iterator_category* = 0) /* pls fix */
		{
			this->clear();
			for (; first != last; first++)
				this->push_back(*first);
		}

		void push_back(const value_type& val)
		{
			if (_arr[_tail]->is_full()) {
				_tail++;
				if (_tail == _capacity)
					_tail = 0;
				if (_head == _tail) {
					if (_tail == 0)
						_tail = _capacity;
					_tail--;
					this->_realloc();
					return (this->push_back(val));
				}
				this->_construct_element(_tail);
			}
			_arr[_tail]->emplace_back(val);
			_size++;
		}

		void push_front(const value_type& val)
		{
			if (_arr[_head]->is_full()) {
				if (_head == 0)
					_head = _capacity; 
				_head--;
				if (_head == _tail) {
					_head++;
					if (_head == _capacity)
						_head = 0;
					this->_realloc();
					return (this->push_front(val));
				}
				this->_construct_element(_head);
			}
			_arr[_head]->emplace_front(val);
			_size++;
		}

		void pop_back()
		{
			if (this->empty())
				return ;
			_arr[_tail]->dequeue_back();
			if (_arr[_tail]->empty())
			{
				if (_tail != _head) {
					this->_destroy_element(_tail);
					_tail--;
				}
			}
			_size--;
		}

		void pop_front()
		{
			if (this->empty())
				return ;
			_arr[_head]->dequeue_front();
			if (_arr[_head]->empty())
			{
				if (_head != _tail) {
					this->_destroy_element(_head);
					_head++;
				}
			}
			_size--;
		}

		/* WHY DOES THIS HAVE INSERT AND ERASE? */

		void		swap(deque& x)
		{
			ft::value_swap(this->_alloc,	x._alloc);
			ft::value_swap(this->_arr,		x._arr);
			ft::value_swap(this->_head,		x._head);
			ft::value_swap(this->_tail,		x._tail);
			ft::value_swap(this->_capacity,	x._capacity);
			ft::value_swap(this->_size,		x._size);
			ft::value_swap(this->_cb_cap,	x._cb_cap);
		}

		void		clear()
		{
			this->_destroy_elements();
			_head = 0;
			_tail = 0;
			_size = 0;
			this->_construct_element(_head);
		}

	}; /* end of deque */

	# undef CAPACITY

} /* end of namespace */

#endif
