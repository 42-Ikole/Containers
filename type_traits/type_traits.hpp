/* ************************************************************************** */
/*                                                                            */
/*           _____    ____        _                  _____   ____             */
/*          |_ " _|U |  _"\ u U  /"\  u     ___     |_ " _| / __"| u          */
/*            | |   \| |_) |/  \/ _ \/     |_"_|      | |  <\___ \/           */
/*           /| |\   |  _ <    / ___ \      | |      /| |\  u___) |           */
/*          u |_|U   |_| \_\  /_/   \_\   U/| |\u   u |_|U  |____/>>          */
/*          _// \\_  //   \\_  \\    >>.-,_|___|_,-._// \\_  )(  (__)         */
/*         (__) (__)(__)  (__)(__)  (__)\_)-' '-(_/(__) (__)(__)              */
/*                                                                            */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft
{

//////////////////
// Remove Const //
//////////////////

	template <class T>
		struct remove_const {
			typedef T type;
	};

	template <class T>
		struct remove_const<const T> {
			typedef T type;
	};

/////////////////////
// Remove Volatile //
/////////////////////

	template <class T>
		struct remove_volatile {
			typedef T type;
	};

	template <class T>
		struct remove_volatile<volatile T>{
			typedef T type;
	};

///////////////////////////
// Remove Const Volatile //
///////////////////////////
	
	template <class T>
		struct remove_cv {
			typedef typename ft::remove_volatile<typename ft::remove_const<T>::type>::type type;
	};

////////////////////////
// ANTI SFINAE SFINAE //
////////////////////////

	template < class T >
		struct make_type {
			typedef void type;
	};

////////////////////////////
// true type / false type //
////////////////////////////

	template <class T, T v>
		struct integral_constant {
			static const T value = v;
		};

	template <bool B>
		struct bool_constant : ft::integral_constant<bool, B>{};

		struct true_type	: ft::bool_constant<true>{};
		struct false_type	: ft::bool_constant<false>{};

} /* end of namespace */

#endif
