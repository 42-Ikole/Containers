

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

	std::cerr	<< "==============================\n" \
				<< COLOR_GREEN	<< namespacename \
				<< COLOR_BLUE	<< container \
				<< COLOR_RESET	<< " took: " \
				<< COLOR_YELLOW	<< std::setw(10) << duration.count() \
				<< COLOR_RED	<< "µs" \
				<< COLOR_RESET	<< std::endl;
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	time_function(vector_test, "vector");
	// time_function(vector_iterator_test, "vector iterators");
	// vector_iterator_test();
}
