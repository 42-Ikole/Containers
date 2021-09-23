
/* ************************************************************************** */
/*                                                                            */
/*     ▄▀▀▄ ▄▄   ▄▀▀█▄▄▄▄  ▄▀▀▀▀▄     ▄▀▀▄▀▀▀▄  ▄▀▀█▄▄▄▄  ▄▀▀▄▀▀▀▄  ▄▀▀▀▀▄    */ 
/*    █  █   ▄▀ ▐  ▄▀   ▐ █    █     █   █   █ ▐  ▄▀   ▐ █   █   █ █ █   ▐    */ 
/*    ▐  █▄▄▄█    █▄▄▄▄▄  ▐    █     ▐  █▀▀▀▀    █▄▄▄▄▄  ▐  █▀▀█▀     ▀▄      */ 
/*       █   █    █    ▌      █         █        █    ▌   ▄▀    █  ▀▄   █     */ 
/*      ▄▀  ▄▀   ▄▀▄▄▄▄     ▄▀▄▄▄▄▄▄▀ ▄▀        ▄▀▄▄▄▄   █     █    █▀▀▀      */ 
/*     █   █     █    ▐     █        █          █    ▐   ▐     ▐    ▐         */ 
/*     ▐   ▐     ▐          ▐        ▐          ▐                             */ 
/*																			  */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*																			  */
/* ************************************************************************** */

#ifndef CIRCULAR_BUFFER_HPP
# define CIRCULAR_BUFFER_HPP

# include <memory>

namespace ft {

	/////////////////////
	// CIRCULAR BUFFER //
	/////////////////////

			template < class T, class Alloc = std::allocator<T> >
				class circular_buffer
			{

		///////////////
		// type defs //
		///////////////
			public:

				typedef T					value_type;
				typedef	Alloc				allocator_type;
				typedef std::size_t			size_type;
				typedef std::ptrdiff_t		difference_type;
				typedef value_type&			reference;
				typedef const value_type&	const_reference;
				typedef value_type*			pointer;
				typedef const value_type*	const_pointer;


		//////////////////////
		// member variables //
		//////////////////////
			private:

				pointer			_arr;
				size_type		_head;
				size_type		_tail;
				size_type		_capacity;
				allocator_type	_alloc;

		/////////////
		// CoPlIeN //
		/////////////
			public:

				circular_buffer(allocator_type alloc = allocator_type())
					: _capacity(4096), _alloc(alloc)
				{
					if (16 * (sizeof(value_type)) > _capacity >> 1)
						_capacity = 16;
					_arr = _alloc.allocate(_capacity);
					_head = _capacity >> 1;
					_tail = _head + 1;
				}

				~circular_buffer()
				{
					this->_clear();
				}

				circular_buffer(circular_buffer &x)
				{
					*this = x;
				}

				circular_buffer&	operator = (circular_buffer &x)
				{
					this->_destroy_elements();
					this->_head		= x._head;
					this->_tail		= x._tail;
					this->_capacity = x._capacity;
					return (*this);
				}

		//////////////////////////////
		// private member functions //
		//////////////////////////////
			private:

				void	_construct_element(size_type& idx, reference val)
				{
					_alloc.construct(&_arr[idx], val);
				}

				void	_destroy_elements()
				{
					for (; _head % _capacity != _tail; _head++)
						_alloc.destroy(&_arr[_head]);
				}

				void	_clear()
				{
					this->_destroy_elements();
					_alloc.deallocate(_arr, _capacity);
					_head		= 0;
					_tail		= 0;
					_capacity	= 0;
					_arr		= NULL;
				}

		///////////////
		// MODIFIERS //
		///////////////
			public:

				void	emplace_back(reference	val)
				{
					if (this->is_full())
						return ;
					this->_construct_element(_tail, val);
					_tail++;
				}

				void	emplace_front(reference	val)
				{
					if (this->is_full())
						return ;
					this->_construct_element(_head, val);
					_head--;
				}

				void	dequeue_back()
				{
					_tail--;
					this->_alloc.destroy(&_arr[_tail]);
				}

				void	dequeue_front()
				{
					_head++;
					this->_alloc.destroy(&_arr[_head]);
				}

		//////////////
		// CAPACITY //
		//////////////
			public:
			
				bool		is_full()
				{
					return (_head == _tail);
				}

				size_type	size()
				{
					return (_capacity - std::abs(_head - _tail));
				}

		////////////////////
		// ELEMENT ACCESS //
		////////////////////
			public:

				reference operator[](const size_type& n)
				{
					return (_arr[(_head + n) % _capacity]);
				}

				reference operator[](const size_type& n) const
				{
					return (_arr[(_head + n) % _capacity]);
				}

			}; /* end of circular buffer */

}

#endif
