/* ************************************************************************** */
/*                                                                            */
/*              ____________________________   __________________             */
/*              __  ___/__  ____/___  _/__  | / /__    |__  ____/             */
/*              _____ \__  /_    __  / __   |/ /__  /| |_  __/                */
/*              ____/ /_  __/   __/ /  _  /|  / _  ___ |  /___                */
/*              /____/ /_/      /___/  /_/ |_/  /_/  |_/_____/                */
/*                                                                            */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*																			  */
/* ************************************************************************** */

#ifndef UGH_INTEGRAL_HPP
# define UGH_INTEGRAL_HPP

# include <type_traits.hpp>

namespace ft
{

////////////////////////////////
// is integral implementation //
////////////////////////////////

	/* BASE CASE */
	template <class T>
		struct is_integral_impl 
			: public ft::false_type {};

	/* bool */
	template <>
		struct is_integral_impl<bool> 
			: public ft::true_type {};

	/* char */
	template <>
		struct is_integral_impl<char> 
			: public ft::true_type {};

	/* signed char */	
	template <>
		struct is_integral_impl<signed char> 
			: public ft::true_type {};

	/* unsigned char */
	template <>
		struct is_integral_impl<unsigned char> 
			: public ft::true_type {};

	/* wide char */
	template <>
		struct is_integral_impl<wchar_t> 
			: public ft::true_type {};

	/* short */
	template <>
		struct is_integral_impl<short> 
			: public ft::true_type {};

	/* unsigned short */
	template <>
		struct is_integral_impl<unsigned short> 
			: public ft::true_type {};

	/* int */
	template <>
		struct is_integral_impl<int> 
			: public ft::true_type {};

	/* unsigned int */
	template <>
		struct is_integral_impl<unsigned int> 
			: public ft::true_type {};

	/* long */
	template <>
		struct is_integral_impl<long> 
			: public ft::true_type {};

	/* unsigned long */
	template <>
		struct is_integral_impl<unsigned long> 
			: public ft::true_type {};
	
///////////////////////////
// Actual implementation //
///////////////////////////

template <class T>
	struct is_integral
    	: public is_integral_impl<typename ft::remove_cv<T>::type> {};

} /* end of namespace */

#endif
