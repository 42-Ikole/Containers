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
	#include <stack>
	namespace ft = std;
#else
	#include <stack.hpp>
#endif

template <class T>
void	whats_in_this_stack_yo(ft::stack<T>& c, const char* msg)
{
	ft::stack<T> t = c;

	std::cout << msg << "\n";
	std::cout << c.empty() << " " << c.size() << "\n";
	while (c.size() > 0) {
		std::cout << c.top() << " ";
		c.pop();
	}
	std::cout << "\n";
	c = t;
}

/////////////////
// CONSTRUCTOR //
/////////////////
static void constructor_test()
{
	print_header("Stack CONSTRUCTOR");

/* default constructor */
	ft::stack<int> default_constructor;
	default_constructor.push(69);
	whats_in_this_stack_yo(default_constructor, "default constructor");

/* copy constructor */
	ft::stack<int> copy_constructor(default_constructor);
	whats_in_this_stack_yo(copy_constructor, "copy constructor");

/* assigantion operator */
	ft::stack<int> assignation = copy_constructor;
	whats_in_this_stack_yo(assignation, "assignation operator");

/* deep copy */
	assignation.push(1337);
	copy_constructor.push(42);
	copy_constructor.push(69);

	assignation = copy_constructor;
	assignation.pop();
	whats_in_this_stack_yo(assignation, "deep copy");
	whats_in_this_stack_yo(copy_constructor, "deep copy");
}

///////////////
// MODIFIERS //
///////////////
static void modifier_test()
{
	print_header("Stack Modifier test");

	ft::stack<std::string>	stonk;

	for(size_t i = 0; i < 1337; ++i)
		stonk.push(std::to_string(i));
	whats_in_this_stack_yo(stonk, "push * 1337");

	while (stonk.size() > 0)
		stonk.pop();
	whats_in_this_stack_yo(stonk, "empty");
}

static void	stack_stress()
{
	print_header("Stack STRESS TEST");

	ft::stack<test> vectest;

	for (size_t i = 0; i < 42069; i++)
		vectest.push(test(i));
	for (; vectest.size() > 1337; vectest.pop());

	ft::stack<int> vec;
	for (size_t i = 0; i < 500000; i++)
		vec.push(i);
	
	ft::stack<int> copy = vec;
	while (vec.size() > 0) {
		vec.pop();
		copy.pop();
	}
}

static void	stack_operators()
{
	ft::stack<int> a;
	ft::stack<int> b;

	a.push(69);
	b.push(420);
	std::cout << std::boolalpha << (a == b) << std::endl;
	std::cout << std::boolalpha << (a < b) << std::endl;
	std::cout << std::boolalpha << (a > b) << std::endl;
	std::cout << std::boolalpha << (a != b) << std::endl;
	std::cout << std::boolalpha << (a >= b) << std::endl;
	std::cout << std::boolalpha << (a <= b) << std::endl;
}

void	stack_test()
{
	constructor_test();
	modifier_test();
	stack_stress();
	stack_operators();
}
