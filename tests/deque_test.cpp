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

	// for(int i = 0; i < 42; i++)
		deq.push_back(42);
	// whats_in_this_container_yo(deq, "42");
	// for (int i = 0; i < 42069; i++)
	// 	deq.push_front(i);
	// whats_in_this_container_yo(deq, "42069");
}

void		deque_test()
{
	constructor_test();
	capacity_test();
	modifier_test();
}
