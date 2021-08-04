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

#include <type_traits>

namespace ft {

///////////////
// Enable if //
///////////////

	template <bool B, class T = void>
		struct enable_if {
			typedef T type;
		};

	template <class T>
		struct enable_if<false, T> {};

	template <bool B, class T = void>
		using enable_if_t = typename enable_if<B, T>::type;

}
