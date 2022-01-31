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
#include <algorithm> // lexicographical compare / shuffle

#ifdef STD
	#include <vector>
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
	typedef ft::vector<int>::iterator				itr;

	ft::iterator_traits<itr>::value_type		var = 69;
	ft::iterator_traits<itr>::pointer			ptr = &var;
	ft::iterator_traits<itr>::reference			ref = *ptr;
	ft::iterator_traits<itr>::difference_type	dif = 42069;
	ft::iterator_traits<itr>::iterator_category cat;
	(void)cat;
	ref = 420;
	std::cout << ref << " " << dif;
}

static void is_integral_test()
{
    std::cout << std::boolalpha;
 
	#ifndef STD
		std::cout << ft::is_integral<char>::value;					// true
	#else
		std::cout << "true";
	#endif

	#ifndef STD
		std::cout << ft::is_integral<unsigned char>::value;			// true
	#else
		std::cout << "true";
	#endif

	#ifndef STD
		std::cout << ft::is_integral<char*>::value;					// false
	#else
		std::cout << "false";
	#endif

	#ifndef STD
		std::cout << ft::is_integral<const char>::value;			// true
	#else
		std::cout << "true";
	#endif

	#ifndef STD
		std::cout << ft::is_integral<volatile char>::value;			// true
	#else
		std::cout << "true";
	#endif

	#ifndef STD
		std::cout << ft::is_integral<const volatile char>::value;	// true
	#else
		std::cout << "true";
	#endif

	#ifndef STD
		std::cout << ft::is_integral<int>::value;					// true
	#else
		std::cout << "true";
	#endif

	#ifndef STD
		std::cout << ft::is_integral<const int>::value;				// true
	#else
		std::cout << "true";
	#endif

	#ifndef STD
		std::cout << ft::is_integral<bool>::value;					// true
	#else
		std::cout << "true";
	#endif

	#ifndef STD
		std::cout << ft::is_integral<volatile int>::value;			// true
	#else
		std::cout << "true";
	#endif

	#ifndef STD
		std::cout << ft::is_integral<const int*>::value;			// false
	#else
		std::cout << "false";
	#endif

	#ifndef STD
		std::cout << ft::is_integral<std::string>::value;			// false
	#else
		std::cout << "false";
	#endif

	#ifndef STD
		std::cout << ft::is_integral<unsigned int>::value;			// true
	#else
		std::cout << "true";
	#endif

	#ifndef STD
		std::cout << ft::is_integral<long>::value;					// true
	#else
		std::cout << "true";
	#endif		

}

static void lexicographical_compare_test()
{
	std::string v1("abcd");
	std::string v2("abcd");

	while (!ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end())) {
		std::cout << v1 << " >= " << v2 << '\n';
		std::random_shuffle(v1.begin(), v1.end());
		std::random_shuffle(v2.begin(), v2.end());
	}
	std::cout << v1 << " >= " << v2 << '\n';

	v1 = "abcd";
	v2 = "abcd";

	while (!ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), std::less<char>() )) {
		std::cout << v1 << " >= " << v2 << '\n';
		std::random_shuffle(v1.begin(), v1.end());
		std::random_shuffle(v2.begin(), v2.end());
	}
	std::cout << v1 << " >= " << v2 << '\n';
}

static bool is_palindrome(const std::string& s)
{
	return ft::equal(s.begin(), s.begin() + s.size()/2, s.rbegin());
}

static void test(const std::string& s)
{
	std::cout << "\"" << s << "\" "
		<< (is_palindrome(s) ? "is" : "is not")
		<< " a palindrome\n";
}

static void equal_test()
{
	test("radar");
    test("hello");
    test("eevee");
    test("murkeflurk");
    test("bleep bloop");
    test("level");
}

void utility_test()
{
	iterator_trait_test();
	is_integral_test();
	lexicographical_compare_test();
	equal_test();
}
