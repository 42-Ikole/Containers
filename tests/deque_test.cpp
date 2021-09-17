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
	#include <deque>
	namespace ft = std;
#else
	#include <deque.hpp>
#endif

static void	constructor_test()
{
	print_header("DEQUE CONSTRUCTOR");

	ft::deque<int> nice;
}

static void	capacity_test()
{

}

static void	modifier_test()
{
	print_header("DEQUE MODIFIER");
	ft::deque<int> deq;

	for(int i = 0; i < 42; i++)
		deq.push_back(i);
	whats_in_this_deque_yo(deq, "42");
}

void		deque_test()
{
	constructor_test();
	capacity_test();
	modifier_test();
}
