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
#include <chrono>
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
	std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
	func();
	std::chrono::high_resolution_clock::time_point finish = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);

	#ifdef STD
		std::string namespacename = "std::"; 
	#else
		std::string namespacename = " ft::";
	#endif

	std::cerr	<< COLOR_GREEN	<< namespacename \
				<< COLOR_BLUE	<< std::setw(20) << std::left << container \
				<< COLOR_RESET  << " took: " \
				<< COLOR_YELLOW	<< std::setw(10) << std::right << duration.count() \
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
	// vector_iterator_test();
}
