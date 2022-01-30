/* ************************************************************************** */
/*                                                                            */
/*              ,---------.     .-''-.      .-'''-.  ,---------.              */
/*              \          \  .'_ _   \    / _     \ \          \             */
/*               `--.  ,---' / ( ` )   '  (`' )/`--'  `--.  ,---'             */
/*                  |   \   . (_ o _)  | (_ o _).        |   \                */
/*                  :_ _:   |  (_,_)___|  (_,_). '.      :_ _:                */
/*                  (_I_)   '  \   .---. .---.  \  :     (_I_)                */
/*                 (_(=)_)   \  `-'    / \    `-'  |    (_(=)_)               */
/*                  (_I_)     \       /   \       /      (_I_)                */
/*                  '---'      `'-..-'     `-...-'       '---'                */
/*																			  */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*																			  */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <iostream>
#include <tests.hpp>

#ifdef STD
	#include <vector>
	#include <algorithm> // lexicographical compare
	#include <iterator> // iterator_traits
	#include <map>
	namespace ft = std;
#else
	#include <utility.hpp>
	#include <type_traits.hpp>
	#include <vector.hpp>
	#include <iterator_traits.hpp>
	#include <map.hpp>
#endif

static void iterator_trait_test()
{
	ft::vector<int>::iterator				vitr;
	ft::map<char, std::string>::iterator	mitr;

	ft::iterator_traits<itr>::value_type		var = 69;
	ft::iterator_traits<itr>::pointer			ptr = &var;
	ft::iterator_traits<itr>::reference			ref = *ptr;
	ft::iterator_traits<itr>::difference_type	dif = 42069;
	ft::iterator_traits<itr>::iterator_category cat;
	ref = 420;
	std::cout << ref << " " << dif;
}

static void is_integral_test()
{
    std::cout << std::boolalpha;
 
	std::cout << ft::is_integral<char>::value;
	std::cout << ft::is_integral<unsigned char>::value;
	std::cout << ft::is_integral<char*>::value;
	std::cout << ft::is_integral<const char>::value;
	std::cout << ft::is_integral<volatile char>::value;
	std::cout << ft::is_integral<const volatile char>::value;
	std::cout << ft::is_integral<int>::value;
	std::cout << ft::is_integral<const int>::value;
	std::cout << ft::is_integral<bool>::value;
	std::cout << ft::is_integral<volatile int>::value;
	std::cout << ft::is_integral<const int*>::value;
	std::cout << ft::is_integral<std::string>::value;
	std::cout << ft::is_integral<unsigned int>::value;
	std::cout << ft::is_integral<long>::value;
}

static void lexicographical_compare_test()
{
	ft::vector<char> v1("abcd");
	ft::vector<char> v2("abcd");
	std::srand(420);

	while (!ft::lexicographical_compare(v1.begin(), v1.end(),
										v2.begin(), v2.end())) {
		std::cout << v1 << " >= " << v2 << '\n';
		std::shuffle(v1.begin(), v1.end());
		std::shuffle(v2.begin(), v2.end());
	}
	std::cout << v1 << " >= " << v2 << '\n';

	v1 = "abcd";
	v2 = "abcd";
	std::srand(420);

	while (!ft::lexicographical_compare(v1.begin(), v1.end(),
										v2.begin(), v2.end()), ft::less) {
		std::cout << v1 << " >= " << v2 << '\n';
		std::shuffle(v1.begin(), v1.end());
		std::shuffle(v2.begin(), v2.end());
	}
	std::cout << v1 << " >= " << v2 << '\n';
}

void utility_test()
{
	iterator_trait_test();
	lexicographical_compare_test();
	#ifndef STD
		// because is_integral is c++11
		is_integral_test();
	#endif

}