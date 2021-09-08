/* ************************************************************************** */
/*	      __   __   ______     ______     ______   ______     ______		  */
/*	     /\ \ / /  /\  ___\   /\  ___\   /\__  _\ /\  __ \   /\  == \		  */
/*	     \ \ \'/   \ \  __\   \ \ \____  \/_/\ \/ \ \ \/\ \  \ \  __<		  */
/*	      \ \__|    \ \_____\  \ \_____\    \ \_\  \ \_____\  \ \_\ \_\ 	  */
/*	       \/_/      \/_____/   \/_____/     \/_/   \/_____/   \/_/ /_/ 	  */
/*																			  */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*																			  */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <string>
# include <pointer_iterator.hpp>
# include <iostream>
# include <stdexcept>

namespace ft {

//////////////////
// vector class //
//////////////////

	template < class T, class Alloc = std::allocator<T> >
		class vector {
		
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
			typedef ft::pointer_iterator<T, ft::random_access_iterator_tag>										iterator;
			typedef ft::pointer_iterator<T, ft::random_access_iterator_tag, std::ptrdiff_t, const T*, const T&>	const_iterator;
			typedef ft::reverse_iterator< iterator >															reverse_iterator;
			typedef ft::reverse_iterator< const_iterator >														const_reverse_iterator;

	//////////////////////
	// Member variables //
	//////////////////////
		private:

			pointer			_arr;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;

	/////////////
	// CoPlIeN //
	/////////////
		public:

			/* default constructor */
			explicit vector(const allocator_type& alloc = allocator_type()) 
				: _arr(NULL), _size(0), _capacity(0), _alloc(alloc)  {}

			/* fill constructor */
			explicit vector(size_type n, const value_type& val = value_type(), 
				const allocator_type& alloc = allocator_type())
				: _arr(NULL), _size(0), _capacity(0), _alloc(alloc)  
			{
				this->assign(n, val);
			}

			/* range constructor */
			template <class InputIterator>
				vector(InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type())
					: _arr(NULL), _size(0), _capacity(0), _alloc(alloc)
			{
				this->assign(first, last);
			}

			/* copy constructor */
			vector(const vector& x) : _arr(NULL)
			{
				*this = x;
			}

			virtual ~vector()
			{
				this->clear();
			}

			vector&	operator = (const vector &x)
			{
				if (this->_arr)
					this->clear();
				this->_size = x._size;
				this->_capacity = x._capacity;
				this->_alloc = x._alloc;
				this->_arr = this->_alloc.allocate(sizeof(T) * x._capacity);
				for (size_type i = 0; i < x._size; i++)
					this->_alloc.construct(&this->_arr[i], x._arr[i]);
				return (*this);
			}
		
	//////////////////////////////
	// Private member functions //
	//////////////////////////////
		private:
	
			void		_destruction(void)
			{
				for (; _size > 0;)
					this->pop_back();
				_alloc.deallocate(_arr, _capacity);
			}

			void		_resize(size_type n)
			{
				if (n <= 0)
					n = 1;
				else if (n < _capacity)
					for (size_type i = _capacity; i > n; i--)
						this->pop_back();
				else if (n < (_capacity + (_capacity >> 1)))
					n = (_capacity + (_capacity >> 1));
				this->_realloc(n);
			}

			void		_realloc(size_type n)
			{
				pointer	tmp;

				if (n > this->max_size())
					throw std::length_error(std::to_string(n));
				tmp = _alloc.allocate(sizeof(T) * n);
				size_type i = 0;
				for (; i < _size && i < n; i++)
					_alloc.construct(&tmp[i], _arr[i]);
				if (_arr != NULL)
					this->_destruction();
				_arr = tmp;
				_size = i;
				_capacity = n;
			}

			void		_erase_elem(size_type idx)
			{
				_alloc.destroy(&_arr[idx]);
				_move_back_elem(this->begin() + idx);
				_size--;
			}

			void		_move_back_elem(iterator pos)
			{
				for (; pos != end(); pos++)
					*pos = *(pos + 1);
			}

			iterator	_move_range(iterator pos, size_type &range)
			{
				if (_size + range > _capacity)
				{
					size_type pos_idx = ft::distance(begin(), pos);
					this->_resize(_size + range);
					pos = this->begin() + pos_idx;
				}
				iterator tmp = this->end();
				_size += range;
				iterator itr = this->end();
				while (tmp != pos)
				{
					*itr = *tmp;
					itr--;
					tmp--;
				}
				return (pos);
			}

			void		_move_back_range(iterator pos, size_type &range)
			{
				size_type i = 0;
				while (i < range)
				{
					*pos = *(pos + range);
					i++;
					pos++;
				}
				for (size_type i = 0; i < range; i++) {
					*pos = *(pos + range);
					pos++;
				}
			}
	
	///////////////
	// ITERATORS //
	///////////////
		public:

			iterator				begin() {
				return (iterator(this->_arr));
			}

			const_iterator			begin() const {
				return (const_iterator(this->_arr));
			}
	
			iterator				end() {
				return (iterator(&this->_arr[this->_size]));
			}

			const_iterator			end() const {
				return (const_iterator(&this->_arr[this->_size]));
			}

			reverse_iterator		rbegin() {
				return (reverse_iterator(&this->_arr[this->_size]));
			}

			const_reverse_iterator	rbegin() const {
				return (const_reverse_iterator(&this->_arr[this->_size]));
			}

			reverse_iterator		rend() {
				return (reverse_iterator(this->_arr));
			}

			const_reverse_iterator	rend() const {
				return (const_reverse_iterator(this->_arr));
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
				this->_resize(n);
				for (size_type i = _size; i < _capacity; i++)
					this->push_back(val);
			}

			size_type	capacity() const
			{
				return (_capacity);
			}

			bool		empty() const
			{
				return (_size == 0);
			}

			void		reserve(size_type n)
			{
				if (_capacity < n)
					this->_realloc(n);
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

			reference		at(size_type n)
			{
				if (n < 0 || n >= _size)
					throw std::out_of_range("vector");
				return (_arr[n]);
			}

			const_reference	at(size_type n) const
			{
				if (n < 0 || n > _size)
					throw std::out_of_range("vector");
				return (_arr[n]);
			}

			reference		front()
			{
				return (_arr[0]);
			}

			const_reference	front() const
			{
				return (_arr[0]);
			}

			reference		back()
			{
				return (_arr[_size - 1]);
			}

			const_reference	back() const
			{
				return (_arr[_size - 1]);
			}

	///////////////
	// MODIFIERS //
	///////////////
		public:

		/* iterator range assign */
		template	<class InputIterator>
			void		assign(InputIterator first, InputIterator last,
				typename ft::iterator_traits<InputIterator>::iterator_category* = 0)
			{
				if (static_cast<size_type>(ft::distance(first, last)) > _capacity)
					this->_resize(ft::distance(first, last) + _capacity);
				size_type i = 0;
				while (first != last && i < _capacity)
				{
					_arr[i] = *first;
					first++;
					i++;
				}
				_size = i;
			}

			/* fill assign */
			void		assign(size_type n, const value_type& val)
			{
				if (n > _capacity)
					this->_resize(n);
				size_type i = 0;
				for (; i < n; i++)
					_alloc.construct(&_arr[i], val);
				_size = i;
			}

			void		push_back(const value_type& val)
			{
				if (_size + 1 > _capacity)
					this->_resize(_size + 1);
				_alloc.construct(&_arr[_size], val);
				_size++;
			}

			void		pop_back()
			{
				if (_size <= 0)
					return ;
				_size--;
				_alloc.destroy(&_arr[_size]);
			}

			/* fill insert */
			iterator	insert(iterator position, const value_type& val)
			{
				size_type distance = ft::distance(this->begin(), position);
				this->insert(position, 1, val);
				return (this->begin() + distance);
			}	

			/* fill insert */
			void 		insert(iterator position, size_type n, const value_type& val)
			{
				position = this->_move_range(position, n);
				for (size_type i = 0; i < n; i++)
					*(position + i) = val;
			}

			/* ranged iterator insert */
			template	<class InputIterator>
				void 		insert(iterator position, InputIterator first, InputIterator last, 
					typename ft::iterator_traits<InputIterator>::iterator_category* = 0)
			{
				size_type	dist = ft::distance(first, last);
		
				position = this->_move_range(position, dist);
				for (size_type i = 0; i < dist; i++)
					*(position + i) = *(first + i);
			}

			iterator	erase(iterator position)
			{
				difference_type	idx = ft::distance(this->begin(), position);

				this->_erase_elem(idx);
				this->_move_back_elem(position);
				return (position);
			}

			iterator	erase(iterator first, iterator last)
			{
				difference_type	idx		= ft::distance(this->begin(), first);
				difference_type	lidx	= ft::distance(this->begin(), last);
				size_type dist			= lidx - idx;

				while (idx != lidx) {
					this->_erase_elem(idx);
					idx++;
				}
				this->_move_back_range(first, dist);
				return (first);
			}

			void		swap(vector& x)
			{
				_size = 0;
				this->insert(this->begin(), x.begin(), x.end());
			}

			void		clear()
			{
				_destruction();
				_arr = NULL;
				_size = 0;
				_capacity = 0;
			}

	///////////////
	// ALLOCATOR //
	///////////////
		public:

			allocator_type	get_allocator() const
			{
				return (_alloc);
			}

	};
}

#endif
