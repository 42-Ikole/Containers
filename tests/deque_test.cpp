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

/* push back */
	for(int i = 0; i < 4242; i++)
		deq.push_back(i);
	whats_in_this_container_yo(deq, "push_back");

/* push front */
	for (int i = 0; i < 42069; i++)
		deq.push_front(i);
	whats_in_this_container_yo(deq, "push_front");

/* assign */
	deq.assign(1337, 69);
	whats_in_this_container_yo(deq, "assign");

/* pop_back */
	while (deq.size())
		deq.pop_back();
	whats_in_this_container_yo(deq, "pop_back");

/* iterator assign */
	deq.assign(69, 420);
	whats_in_this_container_yo(deq, "iterator assign");

/* pop_back */
	while (deq.size())
		deq.pop_front();
	whats_in_this_container_yo(deq, "pop_front");

/* swap */
	ft::deque<int> swappert(420, 69);
	deq.push_back(42);
	swappert.swap(deq);
	whats_in_this_container_yo(swappert, "swap1");
	whats_in_this_container_yo(deq, "swap2");

/* clear */
	swappert.clear();
	deq.clear();
	whats_in_this_container_yo(swappert, "clear1");
	whats_in_this_container_yo(deq, "clear2");

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
