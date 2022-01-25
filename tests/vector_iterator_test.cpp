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
	namespace ft = std;
#else
	#include <vector.hpp>
#endif

static void vector_iterator_functions()
{
	ft::vector<int>							vec;
	ft::vector<int>::iterator				itr;
	ft::vector<int>::const_iterator			citr;
	ft::vector<int>::reverse_iterator		ritr;
	ft::vector<int>::const_reverse_iterator	critr;

	for (size_t i = 0; i < 15; i++)
		vec.push_back(rand());

	itr = vec.begin();
	citr = vec.begin();
	ritr = vec.rbegin();
	critr = vec.rbegin();
	std::cout << "Begin: " << *itr << std::endl;
	std::cout << "Const begin: " << *citr << std::endl;
	std::cout << "Reverse begin: " << *ritr << std::endl;
	std::cout << "Const reverse begin: " << *critr << std::endl;
	
	itr = vec.end() - 1;
	citr = vec.end() - 1;
	ritr = vec.rend() - 1;
	critr = vec.rend() - 1;
	std::cout << "End: " << *itr << std::endl;
	std::cout << "Const end: " << *citr << std::endl;
	std::cout << "Reverse end: " << *ritr << std::endl;
	std::cout << "Const reverse end: " << *critr << std::endl;
	whats_in_this_container_yo(vec, "iterator functions");
}

static void	loopy_bois()
{
	typedef ft::vector<std::size_t> 	vec_type;
	typedef vec_type::iterator			iterator_type;
	typedef vec_type::reverse_iterator	reverse_iterator_type;
	
	vec_type				vec;
	vec_type				copy;
	iterator_type			itr;
	reverse_iterator_type	ritr;

	for (std::size_t i = 0; i < 42069; ++i)
		vec.push_back(i);
	for (itr = vec.begin(); itr != vec.end(); ++itr)
		std::cout << *itr;
	copy.assign(vec.begin() + 69, vec.end() - 420);
	for (itr = copy.begin(); itr != copy.end(); ++itr)
		std::cout << *itr;

	for (ritr = vec.rbegin(); ritr != vec.rend(); ++ritr)
		std::cout << *ritr;
	for (ritr = copy.rbegin() + 42; ritr != copy.rend() - 69; ++ritr)
		std::cout << *ritr;

}

void	vector_iterator_test()
{
	vector_iterator_functions();
	loopy_bois();
}
