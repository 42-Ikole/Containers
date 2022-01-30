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
	#include <set>
	namespace ft = std;
#else
	#include <set.hpp>
#endif

static void set_iterator_functions()
{
	ft::set<std::string>							set;
	ft::set<std::string>::iterator					itr;
	ft::set<std::string>::const_iterator			citr;
	ft::set<std::string>::reverse_iterator			ritr;
	ft::set<std::string>::const_reverse_iterator	critr;

	for (size_t i = 0; i < 15; i++)
		set.insert(std::to_string(i));

	itr = set.begin();
	citr = set.begin();
	ritr = set.rbegin();
	critr = set.rbegin();
	std::cout << "Begin: " << *itr << std::endl;
	std::cout << "Const begin: " << *citr << std::endl;
	std::cout << "Reverse begin: " << *ritr << std::endl;
	std::cout << "Const reverse begin: " << *critr << std::endl;
	
	itr = --set.end();
	citr = --set.end();
	ritr = --set.rend();
	critr = --set.rend();
	std::cout << "End: " << *itr << std::endl;
	std::cout << "Const end: " << *citr << std::endl;
	std::cout << "Reverse end: " << *ritr << std::endl;
	std::cout << "Const reverse end: " << *critr << std::endl;
}

static void	loopy_bois()
{
	typedef ft::set<std::size_t> 		set_type;
	typedef set_type::iterator			iterator_type;
	typedef set_type::reverse_iterator	reverse_iterator_type;
	
	set_type				set;
	set_type				copy;
	iterator_type			itr;
	reverse_iterator_type	ritr;

/* iterator */
	for (std::size_t i = 0; i < 42069; ++i)
		set.insert(i);
	for (itr = set.begin(); itr != set.end(); ++itr)
		std::cout << *itr;
	copy.insert(++set.begin(), --set.end());
	for (itr = copy.begin(); itr != copy.end(); ++itr)
		std::cout << *itr;

/* reverse iterator */
	for (ritr = set.rbegin(); ritr != set.rend(); ++ritr)
		std::cout << *ritr;
	for (ritr = ++copy.rbegin(); ritr != --copy.rend(); ++ritr)
		std::cout << *ritr;

/* begin == end */
	std::cout << ((set.begin() == set.end()) && (set.rbegin() == set.rend())) << "\n";
	set.clear();
	std::cout << ((set.begin() == set.end()) && (set.rbegin() == set.rend())) << "\n";
}

void	set_iterator_test()
{
	print_header("set Iterators");
	set_iterator_functions();
	loopy_bois();
}
