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

/////////////////
// CONSTRUCTOR //
/////////////////
static void constructor_test()
{
	print_header("VECTOR CONSTRUCTOR");

/* default constructor */
	ft::vector<int> default_constructor;
	whats_in_this_container_yo(default_constructor, "default constructor");

/* set allocator */
	ft::vector<std::string, std::allocator<std::string> > set_allocator;
	whats_in_this_container_yo(set_allocator, "set allocater");

/* fill constructor */
	ft::vector<int> fill_constructor(42, 'a');
	whats_in_this_container_yo(fill_constructor, "fill constructor");

/* range constructor */
	ft::vector<int> range_constructor(fill_constructor.begin(), fill_constructor.end() - 21);
	whats_in_this_container_yo(range_constructor, "range constructor");

/* copy constructor */
	ft::vector<int> copy_constructor(range_constructor);
	whats_in_this_container_yo(copy_constructor, "copy constructor");

/* assigantion operator */
	ft::vector<int> assignation = copy_constructor;
	whats_in_this_container_yo(assignation, "assignation operator");
	std::cout << "capacity = " << assignation.capacity() << std::endl;

/* deep copy */
	assignation.push_back(1337);
	copy_constructor.push_back(42);
	copy_constructor.push_back(69);

	assignation = copy_constructor;
	assignation.pop_back();
	whats_in_this_container_yo(assignation, "deep copy");
	whats_in_this_container_yo(copy_constructor, "deep copy");

}

//////////////
// CAPACITY //
//////////////
static void capacity_test()
{
	print_header("VECTOR CAPACITY");

	ft::vector<int>	vec;
	whats_in_this_container_yo(vec, "empty vector");
	std::cout << "max_size = " << vec.max_size() << std::endl;
	std::cout << "is empty = " << vec.empty() << std::endl;

	vec.reserve(42);
	whats_in_this_container_yo(vec, "after reserve for 42");
	std::cout << "capacity = " << vec.capacity() << std::endl;
	std::cout << "is empty = " << vec.empty() << std::endl;\

	vec.resize(69, 420);
	whats_in_this_container_yo(vec, "after resize tot 69 with 420");
	std::cout << "is empty = " << vec.empty() << std::endl;

	vec.resize(21, 69);
	whats_in_this_container_yo(vec, "after resize tot 21 with 69");
	std::cout << "is empty = " << vec.empty() << std::endl;

	vec.reserve(420);
	whats_in_this_container_yo(vec, "reserve 420");
	std::cout << "is empty = " << vec.empty() << std::endl;

	try {
		vec.reserve(-1);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}

////////////////////
// ELEMENT ACCESS //
////////////////////
static void element_access_test()
{
	print_header("VECTOR ELEMENT ACCESS");

	ft::vector<int> vec;
	vec.reserve(1337);

	for (int i = 0; i < 1337; i++)
		vec.push_back(i);
	whats_in_this_container_yo(vec, "1 till 1337");

/* subscript operator */
	int j = vec.size() - 1;
	for (int i = 0; i != j; i++)
		vec[j] = vec[i];
	whats_in_this_container_yo(vec, "reversed the vector");

/* at */
	try {
		for (size_t i = 0; i < vec.size() + 1; i++)
			vec.at(i);
	} catch (std::out_of_range &e) {
		std::cout << e.what() << std::endl;
	}
	try {
		std::cout << vec.at(-1) << std::endl;
	} catch (std::out_of_range &e) {
		std::cout << e.what() << std::endl;
	}

/* front && back */
	std::cout << vec.front() << std::endl;
	std::cout << vec.back() << std::endl;

/* front == back */
	vec.clear();
	vec.push_back(80085);
	std::cout << vec.front() << std::endl;
	std::cout << vec.back() << std::endl;
}

///////////////
// MODIFIERS //
///////////////
static void modifier_test()
{

	print_header("VECTOR Modifier test");

	ft::vector<std::string>				vec(2000, "MANY STRINGS YO");
	ft::vector<std::string>				empty;

/* iterator range assign */
	ft::vector<std::string>::iterator	first = vec.begin() + 42;
	ft::vector<std::string>::iterator	last = vec.begin() + 1337;
	empty.assign(first, last);
	whats_in_this_container_yo(empty, "iterator range assign");

/* fill assign */
	std::string assigned("we just got assigned yo");
	empty.assign(420, assigned);
	std::cout << "size = " << empty.size() << std::endl;
	for (size_t i = 0; i < empty.size(); i++)
			std::cout << "[" << i << "] " << assigned << std::endl;
	
/* push back */
	for (size_t i = 0; i < 6969; i++)
		empty.push_back(std::to_string(i));
	whats_in_this_container_yo(empty, "had to do a lot of pushing for this");

/* pop back */
	for (size_t i = 0; i < 6969; i++)
		empty.pop_back();
	whats_in_this_container_yo(empty, "POP");

/* insert */
	empty.insert(empty.begin() + 42, "LEGENDARY");
	std::cout << empty.at(42) << std::endl;
	std::cout << empty.size() << std::endl;

/* range erase */
	empty.erase(empty.begin(), empty.end() - 1);

/* fill insert */
	empty.insert(empty.end() - 1, 1337, "living on the edge");
	whats_in_this_container_yo(empty, "fill insert");

/* element erase */
	for (size_t i = 0; i < empty.size(); i++)
		empty.erase(empty.begin() + i);
	whats_in_this_container_yo(empty, "elemental erase");

/* Range insert */
	empty.insert(empty.begin(), vec.begin(), vec.end());
	whats_in_this_container_yo(empty, "Ranged insert");

/* clear test */
	empty.clear();
	whats_in_this_container_yo(empty, "clear");

/* swaperoo */
	empty.insert(empty.begin(), 42, "About to get swapped");
	empty.swap(vec);
	whats_in_this_container_yo(empty, "swap 1");
	whats_in_this_container_yo(vec, "swap 2");
}

static void	vector_stress()
{
	print_header("VECTOR STRESS TEST");

	ft::vector<test> vectest;

	for (size_t i = 0; i < 42069; i++)
		vectest.push_back(test(i));
	for (; vectest.size() > 1337; vectest.pop_back());
	vectest.insert(vectest.begin(), 250000, test(1, "insert"));
	
	ft::vector<test> vecswap;
	vecswap.swap(vectest);
	vecswap.erase(vecswap.begin(), vecswap.end() - 2500);
	vecswap.clear();

	ft::vector<int> vec;
	vec.reserve(500000);
	for (size_t i = 0; i < vec.capacity(); i++)
		vec.push_back(i);
	
	vec.resize(25000);
	vec.resize(13370);
	vec.insert(vec.begin(), 1337, 420);

	vec.resize(25000);
	for (size_t i = 0; i < vec.size(); i++)
		vec[i] = i;

	vec.assign(1337, 69);
	whats_in_this_container_yo(vec, "assign");
}

void	vector_test()
{
	constructor_test();
	capacity_test();
	element_access_test();
	modifier_test();
	vector_stress();
}
