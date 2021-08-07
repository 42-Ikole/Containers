
#include <vector.hpp>
#include <iostream>
#include <string>
#include <iterator.hpp>
#include <iterator>
#include <vector>
#include <map>

void	extremely_cool_vector_tests()
{
	ft::vector<int> vecint(10, 42);
	ft::vector<std::string> vecstr;
	ft::vector<int> cpint(vecint);

	std::cout << "cpint size = " << cpint.size() << std::endl;
	vecstr.push_back("Mijn vector");
	vecstr.push_back("is lit yo");
	vecstr.push_back("gekke dingen");
	std::cout << "vecstr size = " << vecstr.size() << std::endl;
	vecstr.print_vector();

}

void	extremely_cool_iterator_tests()
{
	ft::vector<int> vint(420, 69);

	ft::iterator<ft::vector<int>, ft::bidirectional_iterator_tag> itr;
	itr--;
}

int main(void)
{
	extremely_cool_vector_tests();
}
