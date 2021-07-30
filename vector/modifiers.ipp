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

#include <vector.hpp>

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
		size_type distance = ft::distance(begin(), position);
		insert (position, 1, val);
		return (begin() + distance);
	}

	tpl
	void 		vec::insert(iterator position, size_type n, const value_type& val)
	{
		if (_size + n > _capacity)
			realloc(n + _capacity);
		for (iterator i = end() + n; i > position && i > begin(); i--)
			_arr[i] = i - n;
		for (size_type i = 0; i < n; i++)
			position + i = val;
		_size += n;	
	}

	tpl
	template	<class InputIterator>
	void 		vec::insert(iterator position, InputIterator first, InputIterator last)
	{
		size_type	dist = ft::distance(first, last);
		
		if (_size + dist > _capacity)
			realloc(_capacity + dist);
		for (iterator i = end() + dist; i > position && i > begin(); i--)
			_arr[i] = i - dist;
		for (size_type i = 0; i < dist; i++)
			position + i = first + i;
		_size += dist;
	}

	tpl
	typ::iterator	vec::erase(iterator position)
	{
		for (; position != end(); position++)
			position = position + 1;
		_size--;
		reuturn (pos);
	}

	tpl
	typ::iterator	vec::erase(iterator first, iterator last)
	{
		while (first != last)
			first = erase(first);
		return (first);
	}

	tpl
	void		vec::swap(vector& x)
	{
		_size = 0;
		this->insert(this->begin(), x.begin(), x.end());
	}

	tpl
	void		vec::clear()
	{
		_size = 0;
	}

}
