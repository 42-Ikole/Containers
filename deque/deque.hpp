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

# include <memory>
# include <array_iterator.hpp> //
# include <general_helpers.hpp>
# include <circular_buffer.hpp>

namespace ft
{

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
		typedef circular_buffer<T>																			cbuf;
		typedef	std::allocator<cbuf>																		cbuf_allocator_type;

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
		cbuf				**_arr;
		size_type			_head;
		size_type			_tail;
		size_type			_capacity;
		size_type			_size;

	/////////////////////
	// BOB THE BUILDER //
	/////////////////////
	public:

		explicit deque (const allocator_type& alloc = allocator_type())
			: _alloc(cbuf_allocator_type()), _arr(NULL), _head(0), _tail(0), _capacity(128), _size(0)
		{
			this->_initial_alloc();
		}

		explicit deque (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _arr(NULL), _head(0), _tail(0), _capacity(128), _size(0)
		{
			_this->_initial_alloc();
			this->assign(n, val);
		}

		template <class InputIterator>
			deque (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _arr(NULL), _head(0), _tail(0), _capacity(128), _size(0)
		{
			this->_initial_alloc();
			this->assign(first, last);
		}

		deque (const deque& x)
		{
			*this = x;
		}

	//////////////////////////////
	// private member functions //
	//////////////////////////////
	private:

		void	_realloc()
		{
			cbuf	*tmp;

			_capacity <<= 1;
			tmp = _alloc.allocate(_capacity);
			size_type i = 0;
			for (; _head != _tail; i++) {
				if (_head == _capacity >> 1)
					_head = 0;
				tmp[i] = _arr[_head];
				_head++;
			}
			_tail = i;
			_head = 0;
			_alloc.deallocate(_arr);
			_arr = tmp;
		}

		void	_initial_alloc()
		{
			_arr = _alloc.allocate(_capacity);
			this->_construct_element(_head);
		}

		void	_construct_element(size_type& idx, cbuf& = cbuf())
		{
			_arr[idx] = _alloc.allocate(1);
			_alloc.construct(_arr[idx][0], val);
		}

		void	_destroy_element(size_type& idx)
		{
			_alloc.destroy(_arr[idx]);
		}

		void	_destroy_elements()
		{
			for (; _head != _tail; _head++) {
				if (_head == _capacity)
					_head = 0;
				this->_destroy_element(_head);
			}
		}

		bool	_empty()
		{
			return (_size == 0);
		}

	///////////////
	// MODIFIERS //
	///////////////
	public:

		void assign (size_type n, const value_type& val)
		{
			this->_destroy_elements();
			for (size_type i = 0; i < n; i++)
				this->push_back(val);
		}

		template <class InputIterator>
 			void assign (InputIterator first, InputIterator last)
		{
			this->_destroy_elements();
			for (; first != last; first++)
				this->push_back(*first);
		}

		void push_back(const value_type& val)
		{
			if (_arr[_tail]->is_full()) {
				_tail++;
				if (_tail == _capacity)
					_tail = 0;
				// if (this->is_full())
				// 	realloc ofzo
				this->_construct_element(_tail);
			}
			_arr[_tail]->emplace_back(val);
			_size++;
		}

		void push_front(const value_type& val)
		{
			if (_arr[_head]->is_full()) {
				_head--;
				if (_head == -1)
					_head = _capacity - 1;
				// if (this->is_full())
				// 	realloc ofzo
				this->_construct_element(_head);
			}
			_arr[_head]->emplace_front(val);
			_size++;
		}

		void pop_back()
		{
			if (this->_empty())
				return ;
			_arr[_tail]->dequeue_back();
			if (_arr[_tail]->empty())
			{
				if (_tail != _head) {
					this->_destroy_element(_tail);
					_tail--;
				}
			}
		}

		void pop_front()
		{
			if (this->_empty())
				return ;
			_arr[_head]->dequeue_front();
			if (_arr[_head]->empty())
			{
				if (_head != _tail) {
					this->_destroy_element(_head);
					_head++;
				}
			}
		}

	}; /* end of deque */

} /* end of namespace */

#endif
