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
#include <string>

namespace ft {

	tpl
	vec::vector (const allocator_type& alloc) :
		_arr(NULL), _length(0), _alloc(alloc)
	{}

	tpl
	vec::vector (size_type n, const value_type& val,
					const allocator_type& alloc) :
		_length(n), _alloc(alloc)
	{
		_arr = _alloc.allocate(sizeof(T) * n);
		for (size_type i = 0; i < n; i++)
			_arr[i] = val;
	}

	tpl
	template <class InputIterator>
	vec::vector (InputIterator first, InputIterator last, 
				const allocator_type& alloc) :
		_alloc(alloc)
	{
		difference_type length;

		length = last - first;
		_length = length;
		_arr = _alloc.allocate(sizeof(T) * _length);
		for (size_type i = 0; i < _length; i++)
			_arr[i] = first + i;
	}

	tpl
	vec::vector (const vector& x) : _arr(NULL)
	{
		*this = x;
	}

	tpl
	vec::~vector()
	{
		this->_alloc.deallocate(this->_arr);
	}

	tpl
	vector<T, Alloc>&	vec::operator = (const vector &x)
	{
		if (this->_arr)
			this->_alloc.deallocate(this->_arr);
		this->_length = x._length;
		this->_alloc = x._alloc;
		this->_arr = this->_alloc.allocate(sizeof(T) * x._length);
		for (size_type i = 0; i < x._length; i++)
			_arr[i] = x._arr[i];
	}

	tpl
	typ::allocator_type	vec::get_allocator() const
	{

	}

	tpl
	vec::conception::conception(std::string msg, std::string type, std::string val)
	{
		_msg = std::string("[") + COLOR_GREEN + type + COLOR_RESET + std::string("] ") + 
			COLOR_RED + std::string("Error: ") + COLOR_RESET + msg + 
			std::string(" <") + COLOR_YELLOW + val + COLOR_RESET + std::string(">"); 
	}

	tpl
	const char* vec::conception::what() const throw()
	{
		return _msg.c_str();
	}

}
