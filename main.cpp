
#include <vector.hpp>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <map>

struct test {
	test() {std::cout << "constructor" << std::endl;}
	~test() {std::cout << "destructor" << std::endl;}
};

static void	extremely_cool_vector_tests()
{
	std::cout << "______Extremely_COOL_Vector_tests______\n" << std::endl;

/* constructor test */
	ft::vector<int> vecint(10, 42);
	ft::vector<int> cpint(vecint);

/* push back stest */
	vecint.push_back(69);
	vecint.push_back(420);
	vecint.push_back(1337);
	vecint.push_back(42069);
	std::cout << "cpint size = " << cpint.size() << std::endl;
	
/* assignation test */
	cpint = vecint;
	std::cout << "cpint size = " << cpint.size() << std::endl;
	cpint.pop_back();
	std::cout << "cpint size = " << cpint.size() << std::endl;

/* different type vector */
	ft::vector<std::string> vecstr;
	vecstr.push_back("Mijn vector");
	vecstr.push_back("is lit yo");
	vecstr.push_back("gekke dingen");
	vecstr.pop_back();
	vecstr.push_back("lijp");
	std::cout << "vecstr size = " << vecstr.size() << std::endl;
	for (size_t i = 0; i < vecstr.size(); i++)
		std::cout << vecstr[i] << std::endl;

/* size clear and empty */
	if (vecstr.empty() == false)
		vecstr.clear();
	ft::vector<std::string> yup(42, "NoRmiNeTtE");
	vecstr = yup;
	std::cout << vecstr.size() << std::endl;

/* range constructor test */
	ft::vector<std::string>::iterator itr_1 = vecstr.begin();
	ft::vector<std::string>::iterator itr_2 = itr_1 + 12;

	ft::vector<std::string> vec(itr_1, itr_2);
	
	for (ft::vector<std::string>::iterator itr = vec.begin(); itr != vec.end(); itr++)
		std::cout << *itr << std::endl;
	std::cout << "vec size = " << vec.size() << std::endl;

/* insert test */
	vecstr.insert(vecstr.begin(), std::string("NUMERO UNO BABYYY!!"));
	vecstr.insert(vecstr.begin() + 1, std::string("NUMBA ZWEI"));
	std::cout << *(vecstr.begin()) << std::endl << *(vecstr.begin() + 1) << std::endl;

/* erase test */
	ft::vector<std::string>::iterator erase_first = vecstr.begin() + 2;
	ft::vector<std::string>::iterator erase_last = vecstr.end() - 1;
	vecstr.erase(erase_first, erase_last);
	// std::cout << vecstr.size() << std::endl;
	
	for(std::size_t i = 0; i < vecstr.size(); i++)
		std::cout << vecstr[i] << std::endl;

	ft::vector<test> vectest;
	struct test hoi;
	vectest.push_back(hoi);
	vectest.push_back(hoi);
	vectest.push_back(hoi);
	vectest.erase(vectest.begin(), vectest.begin() + 1);
}

static void	extremely_cool_vector_iterator_tests()
{
	std::cout << "\n______Extremely_COOL_Vector_iterator_tests______\n" << std::endl;

	ft::vector<int> vint(420, 69);

/* iterator ++ test */
	for (ft::vector<int>::iterator itr = vint.begin(); itr != vint.end(); itr++) {
		if (*itr != 69) {
			std::cout << "THIS AINT ADDING UP YO!" << std::endl;
			std::cout << *itr << std::endl;
		}
	}

/* iterator -- test */
	for (ft::vector<int>::iterator itr = vint.end() - 1; itr != vint.begin(); itr--) {
		if (*itr != 69) {
			std::cout << "subtracting going wrong yo!" << std::endl;
			std::cout << *itr << std::endl;
		}
	}

/* iterator + test */
	{
	ft::vector<int>::iterator itr = vint.begin();
	itr += 42;
	*itr = 1337;
	for (itr = vint.begin(); itr != vint.end(); itr++) {
		if (*itr != 69) {
			std::cout << *itr << std::endl;
			break ;
		}
	}

/* iterator assignation erase and - test */
	itr -= 21;
	*itr = 420;
	vint.erase(itr);
	itr += 20;
	vint.erase(itr);
	for (itr = vint.begin(); itr != vint.end(); itr++)
		if (*itr != 69)
			std::cout << *itr << std::endl;
	}
	std::cout << vint.size() << std::endl;
}

int main(void)
{
	extremely_cool_vector_tests();
	extremely_cool_vector_iterator_tests();
	// std::vector<std::string> brr;
	// brr.push_back("wadup");
	// brr.push_back("skrt");

	// std::vector<std::string>::iterator itrr;
	// std::map<int, std::string>::iterator skrt;

	// std::__wrap_iter<int*> itr;


	// // itr = brr.begin();
	// itr++;
	// itr--;
	// system("leaks containers | grep 'total leaked'");
}
