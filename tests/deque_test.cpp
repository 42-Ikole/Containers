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

	// ft::deque<int> nice;
}

static void	capacity_test()
{

}

static void	modifier_test()
{
	print_header("DEQUE MODIFIER");
	ft::deque<int> deq;

	for(int i = 0; i < 4242; i++)
		deq.push_back(i);
	whats_in_this_container_yo(deq, "4242");
	for (int i = 0; i < 42069; i++)
		deq.push_front(i);
	whats_in_this_container_yo(deq, "42069");
	// deq.push_back(4);
	// deq.push_back(5);
	// deq.push_front(3);
	// deq.push_front(2);
	// deq.push_front(1);
	// whats_in_this_container_yo(deq, "fadj");
}

void		deque_test()
{
	constructor_test();
	capacity_test();
	modifier_test();
}
