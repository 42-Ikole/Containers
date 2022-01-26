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

#ifndef SO_TO_VICTOR_HPP
# define SO_TO_VICTOR_HPP

# include <memory>
# include <string>
# include <iostream>
# include <stdexcept>
# include <iterator.hpp>
# include <utility.hpp>
# include <type_traits.hpp>
# include <lexicographical_compare.hpp>

# define LENGTH_ERROR "allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size"

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

			typedef T										value_type;
			typedef Alloc									allocator_type;
			typedef std::size_t								size_type;
			typedef std::ptrdiff_t							difference_type;
			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef value_type*								pointer;
			typedef const value_type*						const_pointer;
			typedef T*										iterator;
			typedef const T*								const_iterator;
			typedef ft::reverse_iterator< iterator >		reverse_iterator;
			typedef ft::reverse_iterator< const_iterator >	const_reverse_iterator;

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
				if (*this == x)
					return (*this);

				if (this->_arr)
					this->clear();
				this->_size = x._size;
				this->_capacity = x._capacity;
				this->_arr = this->_alloc.allocate(x._capacity);
				for (size_type i = 0; i < x._size; i++)
					this->_alloc.construct(&this->_arr[i], x._arr[i]);
				return (*this);
			}
		
	//////////////////////////////
	// Private member functions //
	//////////////////////////////
		private:
	
			void	_destruction(void)
			{
				while (_size > 0)
					this->pop_back();
				_alloc.deallocate(_arr, _capacity);
			}

			void	_resize(size_type n)
			{
				if (n <= 0)
					n = 1;
				else if (n < _capacity * 2)
					n = _capacity * 2;
				this->_realloc(n);
			}

			void	_realloc(size_type n)
			{
				pointer	tmp;

				if (n > this->max_size())
					throw std::length_error(LENGTH_ERROR);
				tmp = _alloc.allocate(n);
				size_type i = 0;
				for (; i < _size && i < n; i++)
					_alloc.construct(&tmp[i], _arr[i]);
				if (_arr != NULL)
					this->_destruction();
				_arr = tmp;
				_size = i;
				_capacity = n;
			}

			void	_move_range(iterator &pos, size_type &range)
			{
				if (_size + range > _capacity)
				{
					size_type pos_idx = ft::distance(begin(), pos);
					this->_resize(_size + range);
					pos = this->begin() + pos_idx;
				}
				iterator tmp = this->end();
				_size += range;
				while (tmp != pos)
				{
					--tmp;
					_alloc.construct(&(*(tmp + range)), *tmp);
					_alloc.destroy(&(*tmp));
				}
			}

			void	_move_back_range(iterator pos, size_type range)
			{
				size_type i = static_cast<size_type>(ft::distance(this->begin(), pos));

				for (; i < i + range && i + range < _size; i++) {
					_alloc.construct(&_arr[i], _arr[i + range]);
					_alloc.destroy(&_arr[i + range]);
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
				return (reverse_iterator(&this->_arr[this->_size - 1]));
			}

			const_reverse_iterator	rbegin() const {
				return (const_reverse_iterator(&this->_arr[this->_size - 1]));
			}

			reverse_iterator		rend() {
				return (reverse_iterator(this->_arr - 1));
			}

			const_reverse_iterator	rend() const {
				return (const_reverse_iterator(this->_arr - 1));
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
					this->_realloc(n);
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
					this->_resize(n);
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
					this->_resize(_capacity + ft::distance(first, last));
				size_type i = 0;
				while (first != last)
				{
					if (i < _size)
						_alloc.destroy(&_arr[i]);
					_alloc.construct(&_arr[i], *first);
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
				for (; i < n; i++) {
					if (i < _size)
						_alloc.destroy(&_arr[i]);
					_alloc.construct(&_arr[i], val);
				}
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
				this->_move_range(position, n);
				for (size_type i = 0; i < n; i++)
					_alloc.construct(&(*(position + i)), val);
			}

			/* range insert */
			template	<class InputIterator>
				void 		insert(iterator position, InputIterator first, InputIterator last, 
					typename ft::iterator_traits<InputIterator>::iterator_category* = 0)
			{
				size_type	dist = ft::distance(first, last);
		
				_move_range(position, dist);
				for (size_type i = 0; i < dist; i++)
					_alloc.construct(&(*(position + i)), *(first + i));
			}

			/* element erase */
			iterator	erase(iterator position)
			{
				return (this->erase(position, position + 1));
			}

			/* ranged erase */
			iterator	erase(iterator first, iterator last)
			{
				difference_type range  = ft::distance(first, last);
				for (iterator i = first; i != last; i++)
					_alloc.destroy(&(*i));
				this->_move_back_range(first, range);
				_size -= range;
				return (first);
			}

			void		swap(vector& x)
			{
				ft::value_swap(this->_arr, x._arr);
				ft::value_swap(this->_size, x._size);
				ft::value_swap(this->_capacity, x._capacity);
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

	}; /* end of vector class */

///////////////
// Swapfiets //
///////////////

	template< class T, class Alloc >
		void swap(ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs)
	{
		lhs.swap(rhs);
	}

//////////////////////////
// CoMpArIsOn oPeRaToRs //
//////////////////////////

	template< class T, class Alloc >
		bool operator == (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template< class T, class Alloc >
		bool operator != (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template< class T, class Alloc >
		bool operator  < (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template< class T, class Alloc >
		bool operator <= ( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
			return !(rhs < lhs);
	}

	template< class T, class Alloc >
		bool operator  > (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
			return (rhs < lhs);
	}

	template< class T, class Alloc >
		bool operator >= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
			return !(lhs < rhs);
	}

} /* end of namespace */

#endif
