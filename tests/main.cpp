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
		std::cerr << "---------------- std::" << type << " -----------------" << std::endl;
	#else
		std::cerr << "----------------  ft::" << type << " -----------------" << std::endl;
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

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	print_type_header("vector");
	time_function(vector_test, "vector");
	time_function(vector_iterator_test, "vector iterators");

	print_type_header("deque");
	time_function(deque_test, "deque");

	print_type_header("map");
	time_function(map_test, "map");
	// vector_iterator_test();
	system("leaks containers | grep -o 'leaks for 0'");
}
