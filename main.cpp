
#include <vector.hpp>
#include <iostream>
#include <string>
#include <iterator.hpp>

void	extremely_cool_vector_tests()
{
	ft::vector<int> vecint(10, 42);
	ft::vector<std::string> vecstr;
	ft::vector<int> cpint(vecint);

	std::cout << "cpint size = " << cpint.size() << std::endl;

	}

int main(void)
{
	extremely_cool_vector_tests();
}
