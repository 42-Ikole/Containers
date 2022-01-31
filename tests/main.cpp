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
#include <iomanip>
#include <string>
#include <sys/time.h>
#include <tests.hpp>

#ifdef STD
	namespace ft = std;
#endif

void	print_header(std::string header)
{
	std::cout << "-----------------" << std::setw(15) << header << "-----------------" << std::endl;
}

void	print_type_header(std::string type)
{
	#ifdef STD
		std::cerr << "\n---------------- std::" << type << " -----------------" << std::endl;
	#else
		std::cerr << "\n----------------  ft::" << type << " -----------------" << std::endl;
	#endif
}

void	time_function(void(*func)(), std::string container)
{
	struct timeval	time;
	size_t			duration;

	gettimeofday(&time, NULL);
	duration = (time.tv_sec * 1000 * 1000) + time.tv_usec;
	func();
	gettimeofday(&time, NULL);
	duration = ((time.tv_sec * 1000 * 1000) + time.tv_usec) - duration;

	#ifdef STD
		std::string namespacename = "std::"; 
	#else
		std::string namespacename = " ft::";
	#endif

	std::cerr	<< COLOR_GREEN	<< namespacename \
				<< COLOR_BLUE	<< std::setw(20) << std::left << container \
				<< COLOR_RESET  << " took: " \
				<< COLOR_YELLOW	<< std::setw(10) << std::right << duration \
				<< COLOR_RED	<< "µs" \
				<< COLOR_RESET	<< std::endl;
}

static void exec_container(void (*con)(void), void (*itr)(void), std::string name)
{
	print_type_header(name);
	time_function(con, name);
	time_function(itr, name + " iterators");
}

static void exec_container(void (*con)(void), std::string name)
{
	print_type_header(name);
	time_function(con, name);
}

int	main(int argc, char **argv)
{
	(void)argc;

	srand(420);

	exec_container(vector_test, vector_iterator_test, "vector");
	exec_container(map_test, map_iterator_test, "map");
	exec_container(set_test, set_iterator_test, "set");
	exec_container(stack_test, "stack");
	exec_container(utility_test, "utility");

	#ifndef DEBUG
		std::cout << std::endl;
		std::string name(argv[0]);
		name.erase(0, name.rfind("/") + 1);
		std::string leaks(std::string("leaks ") + name + " | grep -o 'leaks for 0'");
		system(leaks.c_str());
	#endif
}
