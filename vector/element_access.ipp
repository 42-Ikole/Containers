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
	typ::reference			vec::operator [](size_type n)
	{
		return _arr[n];
	}

	tpl
	typ::const_reference	vec::operator [](size_type n) const
	{
		return _arr[n];
	}

	tpl
	typ::reference			vec::at(size_type n)
	{
		if (n < 0 || n > _size)
			throw conception(OUT_OF_RANGE, "at()", std::to_string(n));
		return _arr[n];
	}

	tpl
	typ::const_reference	vec::at(size_type n) const
	{
		if (n < 0 || n > _size)
			throw conception(OUT_OF_RANGE, "at()", std::to_string(n));
		return _arr[n];
	}

	tpl
	typ::reference			vec::front()
	{
		return _arr[0];
	}

	tpl
	typ::const_reference	vec::front() const
	{
		return _arr[0];
	}

	tpl
	typ::reference			vec::back()
	{
		return _arr[_size - 1];
	}

	tpl
	typ::const_reference	vec::back() const
	{
		return _arr[_size - 1];
	}

}
