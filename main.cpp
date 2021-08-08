
#include <vector.hpp>
#include <iostream>
#include <string>
#include <iterator.hpp>
#include <iterator>
#include <vector>
#include <map>

static void	extremely_cool_vector_tests()
{
	ft::vector<int> vecint(10, 42);
	ft::vector<std::string> vecstr;
	ft::vector<int> cpint(vecint);
	vecint.push_back(69);
	vecint.push_back(420);
	vecint.push_back(1337);
	vecint.push_back(42069);
	std::cout << "cpint size = " << cpint.size() << std::endl;

	for (ft::vector<int>::iterator itr = vecint.begin(); itr != vecint.end(); itr++)
		std::cout << *itr << std::endl;

	vecstr.push_back("Mijn vector");
	vecstr.push_back("is lit yo");
	vecstr.push_back("gekke dingen");
	std::cout << "vecstr size = " << vecstr.size() << std::endl;
	for (ft::vector<std::string>::iterator itr = vecstr.begin(); itr != vecstr.end(); itr++)
		std::cout << *itr << std::endl;

}

// static void	extremely_cool_iterator_tests()
// {
// 	ft::vector<int> vint(420, 69);

// 	ft::vector<int>::iterator itr;
// 	itr--;
// }

int main(void)
{
	extremely_cool_vector_tests();
	// std::vector<std::string> brr;
	// brr.push_back("wadup");
	// brr.push_back("skrt");

	// std::vector<std::string>::iterator itrr;
	// std::map<int, std::string>::iterator skrt;

	// std::__wrap_iter<int*> itr;


	// // itr = brr.begin();
	// itr++;
	// itr--;
}
