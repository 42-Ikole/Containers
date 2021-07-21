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
	template	<class InputIterator>
	void		vec::assign(InputIterator first, InputIterator last)
	{
		if (ft::distance(first, last) > _capacity)
			realloc(ft::distance(first, last) + _capacity);
		size_type i = 0;
		for (; first != last && i < _capacity; first++ && i++)
			_arr[i] = *first;
		_size = i;
	}

	tpl
	void		vec::assign(size_type n, const value_type& val)
	{
		if (n > _capacity)
			realloc(n + _capacity);
		size_type i = 0;
		for (; i < _capacity; i++)
			_arr[i] = val;
		_size = i;
	}

	tpl
	void		vec::push_back (const value_type& val)
	{
		if (_size + 1 > _capacity)
			realloc(_capacity * 2);
		_arr[_size] = val;
		_size++;
	}

	tpl
	void		vec::pop_back()
	{
		_size--;
	}

	tpl
	typ::iterator	vec::insert(iterator position, const value_type& val)
	{
		if (_size + 1 > _capacity)
			realloc(_capacity * 2);
		_size++;
		for (iterator i = _end(); i > position; i--)
			_arr[i] = i - 1;
		position = val;
	}

	tpl
	void 		vec::insert(iterator position, size_type n, const value_type& val)
	{
		if (_size + n > _capacity)
			realloc(n + _capacity);
		_size += n;
		for (iterator i = _end(); i > position + n; i--) // kan niet met end iterator fix dit
			_arr[i] = i - 1;
		for (size_type i = 0; i < n; i++)
			position + i = val;
	}

	tpl
	template	<class InputIterator>
	void 		vec::insert(iterator position, InputIterator first, InputIterator last)
	{
		size_type	dist = ft::distance(first, last);
		
		if (_size + dist > _capacity)
			realloc(_capacity + dist);
		size_type i = ft::distance(begin(), position);
		for (iterator pos = end(); i < dist; i--)

		
	}

	tpl
	typ::iterator	vec::erase(iterator position)
	{

	}

	tpl
	typ::iterator	vec::erase(iterator first, iterator last)
	{

	}

	tpl
	void		vec::swap(vector& x)
	{

	}

	tpl
	void		vec::clear()
	{

	}

}
