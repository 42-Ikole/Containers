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
	#include <map>
	namespace ft = std;
#else
	#include <map.hpp>
#endif

static void map_iterator_functions()
{
	ft::map<int, std::string>							map;
	ft::map<int, std::string>::iterator					itr;
	ft::map<int, std::string>::const_iterator			citr;
	ft::map<int, std::string>::reverse_iterator			ritr;
	ft::map<int, std::string>::const_reverse_iterator	critr;

	for (size_t i = 0; i < 15; i++)
		map[rand()] = std::to_string(i);

	itr = map.begin();
	citr = map.begin();
	ritr = map.rbegin();
	critr = map.rbegin();
	std::cout << "Begin: " << (*itr).first << (*itr).second << std::endl;
	std::cout << "Const begin: " << (*citr).first << (*citr).second << std::endl;
	std::cout << "Reverse begin: " << (*ritr).first << (*ritr).second << std::endl;
	std::cout << "Const reverse begin: " << (*critr).first << (*critr).second << std::endl;
	
	itr = --map.end();
	citr = --map.end();
	ritr = --map.rend();
	critr = --map.rend();
	std::cout << "End: " << (*itr).first << (*itr).second << std::endl;
	std::cout << "Const end: " << (*citr).first << (*citr).second << std::endl;
	std::cout << "Reverse end: " << (*ritr).first << (*ritr).second << std::endl;
	std::cout << "Const reverse end: " << (*critr).first << (*critr).second << std::endl;
}

static void	loopy_bois()
{
	typedef ft::map<std::size_t, int> 	map_type;
	typedef map_type::iterator			iterator_type;
	typedef map_type::reverse_iterator	reverse_iterator_type;
	
	map_type				map;
	map_type				copy;
	iterator_type			itr;
	reverse_iterator_type	ritr;

/* iterator */
	for (std::size_t i = 0; i < 42069; ++i)
		map[i] = i*i;
	for (itr = map.begin(); itr != map.end(); ++itr)
		std::cout << (*itr).first << (*itr).second;
	copy.insert(++map.begin(), --map.end());
	(*(++map.begin())).second = -42;
	for (itr = copy.begin(); itr != copy.end(); ++itr)
		std::cout << (*itr).first << (*itr).second;

/* reverse iterator */
	for (ritr = map.rbegin(); ritr != map.rend(); ++ritr)
		std::cout << (*ritr).first << (*ritr).second;
	(*(++map.rbegin())).second = -69;
	for (ritr = ++copy.rbegin(); ritr != --copy.rend(); ++ritr)
		std::cout << (*ritr).first << (*ritr).second;

/* begin == end */
	std::cout << ((map.begin() == map.end()) && (map.rbegin() == map.rend())) << "\n";
	map.clear();
	std::cout << ((map.begin() == map.end()) && (map.rbegin() == map.rend())) << "\n";
}

void	map_iterator_test()
{
	print_header("map Iterators");
	map_iterator_functions();
	loopy_bois();
}
