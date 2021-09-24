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
# include <linke_list.hpp>

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
			typedef linke_list<T>																				node;
			typedef node*																						node_pointer;
			typedef std::allocator<node>																		node_allocator_type;

			/* GA EEN NODE ITERATOR SCHRIJVEN */
			typedef ft::array_iterator<T, ft::random_access_iterator_tag>										iterator;
			typedef ft::array_iterator<T, ft::random_access_iterator_tag, std::ptrdiff_t, const T*, const T&>	const_iterator;
			typedef ft::reverse_iterator< iterator >															reverse_iterator;
			typedef ft::reverse_iterator< const_iterator >														const_reverse_iterator;

	//////////////////////
	// Member variables //
	//////////////////////
		private:

			allocator_type		_alloc;
			node_pointer		_head;
			node_pointer		_tail;
			size_type			_size;
			node_allocator_type	_node_alloc;

	/////////////////////
	// BOB THE BUILDER //
	/////////////////////
	public:

		explicit deque(const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _head(_allocate_node()), _tail(_head), _size(0), _node_alloc(node_allocator_type())
		{
		}

		explicit deque(size_type n, const T& val = T(), const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _head(_allocate_node()), _tail(_head), _size(0), _node_alloc(node_allocator_type())
		{
			_tail = _tail->add_range_back(n, val);
		}

		template< class InputIt >
			deque(InputIt first, InputIt last,	const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _head(_allocate_node()), _tail(_head), _size(0), _node_alloc(node_allocator_type())
		{
			_tail = _head->add_range_back(first, last);
		}
		
		deque(const deque& x)
		{
			*this = x;
		}

		deque&	operator = (const deque &x)
		{
			this->clear();
			this->_head = x._head;
			this->_tail = x._tail;
			this->_size = x._size;
			return (*this);
		}

	//////////////////////////////
	// Private member functions //
	//////////////////////////////
		private:

			void			_destruction()
			{
				while(_size > 0)
					this->pop_back();
			}

			node_pointer	_allocate_node(const node& new_node = node())
			{
				node_pointer ret;

				ret = _node_alloc.allocate(1);
				_node_alloc.construct(ret, new_node);
				return (ret);
			}

			reference		_get_element(size_type n)
			{
				node_pointer tmp = _head;

				while (n > tmp->size())
				{
					n -= tmp->size();
					tmp = tmp->_next;
				}
				return ((*tmp)[n]);
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
						this->pop_back();
				}
				else {
					for (size_type i = _size; i < n; i++)
						this->push_back(val);
				}
			}

			bool		empty() const
			{
				return (_size == 0);
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
				this->clear();
				while (first != last)
				{
					this->push_back(*first);
					first++;
				}
			}

			/* fill assign */
			void		assign(size_type n, const value_type& val)
			{
				this->clear();
				for (; n > 0; n--)
					this->push_back(val);
			}

			void		push_back(value_type& val)
			{
				_tail = _tail->push_back(val);
				_size++;
			}

			void		pop_back()
			{
				if (_size <= 0)
					return ;
				_tail = _tail->pop_back();
				_size--;
			}

			void		push_front(value_type& val)
			{
				_head = _head->push_front(val);
				_size++;
			}

			void		pop_front()
			{
				if (_size <= 0)
					return ;
				_size--;
				_head = _head->pop_front();
			}

			/*
			** INSERT MAKES NO SENSE IN DEQUE!
			*/

			/*
			** ERASE ALSO MAKES NO SENSE AT ALL :/
			*/


		////////////////////
		// ELEMENT ACCESS //
		////////////////////
		public:

			reference		operator[](size_type n)
			{
				return (this->_get_element(n));
			}

			const_reference	operator[](size_type n) const
			{
				return (this->_get_element(n));
			}



			void		swap(deque& x)
			{
				ft::value_swap(this->_head, x._head);
				ft::value_swap(this->_tail, x._tail);
				ft::value_swap(this->_size, x._size);
			}

			void		clear()
			{
				_destruction();
				_head = NULL;
				_tail = NULL;
				_size = 0;
			}

	}; /* end of deque */

} /* end of namespace */

#endif
