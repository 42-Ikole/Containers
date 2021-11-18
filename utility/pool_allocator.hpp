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

#ifndef MY_VERY_OWN_REALLY_POG_POOL_ALLOCATOR
# define MY_VERY_OWN_REALLY_POG_POOL_ALLOCATOR

#include <memory>

namespace ft
{

	template < typename T >
		class pool_allocator
	{

	//////////////
	// Typedefs //
	//////////////
	public:

		typedef T							value_type;
		typedef value_type&					reference;
		typedef value_type*					pointer;
		typedef std::ptrdiff_t				difference_type;
		typedef std::allocator<value_type>	allocator_type;

	//////////////////////
	// Member variables //
	//////////////////////
	private:

		const size_t	capacity = 25;

		value_type*		_elements;
		size_t			_size;
		allocator_type	_alloc;


	/////////////////
	// Construcors //
	/////////////////
	public:

		pool_allocator() throw()
			: _elements(NULL), _size(0), _alloc(allocator_type())
		{

		}

		template< class U >
			pool_allocator( const pool_allocator<U>& other ) throw()
		{

		}

		~pool_allocator()
		{

		}

	//////////////////////
	// Member functions //
	//////////////////////
	public:

		pointer address(reference x) const
		{
			return (&x);
		}

		pointer allocate(size_type n, const void * hint = 0)
		{
			if (_size == 0)
				_elements = _alloc.allocate(_capacity);
			if (n > _size)
				return (_alloc.allocate(n));
			else {
				pointer ret = _elements + _capacity - _size;
				_size -= n;
				return (ret);
			}
		}

	}; /* end of class pool allocator */

} /* end of namespace ft */

#endif
