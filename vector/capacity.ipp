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

#include "vector.hpp"

namespace ft {

	tpl
	typ::size_type	vec::size() const
	{
		return _size;
	}

	tpl
	typ::size_type	vec::max_size() const
	{
		return _alloc.max_size();
	}

	tpl
	void		vec::resize(size_type n, value_type val)
	{
		realloc(n);
		for (size_type i = _size; i < _capacity; i++)
			_arr[i] = val;
	}

	tpl
	typ::size_type	vec::capacity() const
	{
		return _capacity;
	}

	tpl
	bool		vec::empty() const
	{
		return (_size == 0);
	}

	tpl
	void		vec::reserve(size_type n)
	{
		if (_capacity < n)
			realloc(n);
	}

}
