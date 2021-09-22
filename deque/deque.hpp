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
# include <deque> //

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


		////////////////
		// LINKE LIST //
		////////////////
		protected:

			struct linke_list
			{
			///////////////
			// TYPE DEFS //
			///////////////
			public:

				typedef	std::allocator<linke_list>						node_allocator_type;
				typedef	linke_list*										node_pointer;
				typedef	circular_buffer< value_type, allocator_type >	cbuf;

			//////////////////////
			// Member variables //
			//////////////////////
			protected:

				node_allocator_type _node_allocator;
				node_pointer		_next;
				node_pointer		_prev;
				cbuf				_elements;  // moet ik dit allocaten im confused

			/////////////
			// CoPlIeN //
			/////////////
			public:

				linke_list(node_pointer	next = NULL, node_pointer prev = NULL)
					: _next(next), _prev(prev)
				{
				}

				~linke_list()
				{
					this->clear();
				}

			///////////////
			// MODIFIERS //
			///////////////
			public:

				node_pointer	push_front(const value_type& val)
				{
					if (_elements->is_full() == true)
					{
						_prev = _node_allocator.allocate(1);
						_node_allocator.construct(_prev, cbuf(NULL, this));
						_prev->_elements.emplace_front(val);
						return (_prev);
					}
					_elements.emplace_front(val);
					return (this);
				}

				node_pointer	push_back(const value_type& val)
				{
					if (_elements->is_full() == true)
					{
						_next = _node_allocator.allocate(1);
						_node_allocator.construct(_next, cbuf(this, NULL));
						_next->_elements.emplace_back(val);
						return (_next);
					}
					_elements.emplace_back(val);
					return (this);
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



	/////////////
	// CoPliEn //
	/////////////
	public:

		deque()
		{

		}

		explicit deque( const allocator_type& alloc )
		{

		}

		explicit deque( size_type n, const T& value = T(), const allocator_type& alloc = allocator_type())
		{

		}

		template< class InputIt >
			deque( InputIt first, InputIt last,	const allocator_type& alloc = allocator_type())
		{

		}
		
		deque( const deque& other )
		{
			
		}

	}; /* end of deque */

} /* end of namespace */

#endif
