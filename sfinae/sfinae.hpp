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

#ifndef I_HATE_ENABLE_IF_HPP
# define I_HATE_ENABLE_IF_HPP

namespace ft
{

///////////////
// Enable if //
///////////////

	template <bool B, class T = void>
		struct enable_if {
			typedef T type;
		};

	template <class T>
		struct enable_if<false, T> {};

/* alias declaration is cpp11 ffs */
/*
	template <bool B, class T = void>
		using enable_if_t = typename enable_if<B, T>::type;

	template<bool B>
		using bool_if_t = std::enable_if_t<B, bool>;
*/
	
}

#endif
