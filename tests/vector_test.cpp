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

template < class Vec >
	static void whats_in_this_vector_yo(Vec &vec, std::string test)
{
	std::cout << "--[ " << test << " ]--" << std::endl;
	for (size_t i = 0; i < vec.size(); i++)
		std::cout << vec[i] << std::endl;
	std::cout << "size = " << vec.size() << std::endl;
}

/////////////////
// CONSTRUCTOR //
/////////////////
static void constructor_test()
{
	print_header("VECTOR CONSTRUCTOR");

	ft::vector<int> default_constructor;
	whats_in_this_vector_yo(default_constructor, "default constructor");

	ft::vector<std::string, std::allocator<std::string>> set_allocator;
	whats_in_this_vector_yo(set_allocator, "set allocater");

	ft::vector<unsigned char> fill_constructor(42, 'a');
	whats_in_this_vector_yo(fill_constructor, "fill constructor");

	ft::vector<unsigned char> range_constructor(fill_constructor.begin(), fill_constructor.end() - 21);
	whats_in_this_vector_yo(range_constructor, "range constructor");

	ft::vector<unsigned char> copy_constructor(range_constructor);
	whats_in_this_vector_yo(copy_constructor, "copy constructor");

	ft::vector<unsigned char> assignation = copy_constructor;
	whats_in_this_vector_yo(assignation, "assignation operator");
}

//////////////
// ITERATOR //
//////////////
static void iterator_test()
{
	print_header("VECTOR ITERATOR");
	ft::vector<int>	int_vector(42, 69);
	for (ft::vector<int>::iterator itr = int_vector.begin(); itr != int_vector.end(); itr++)
		std::cout << *itr << std::endl;

	const ft::vector<std::string> string_vector(16, "lmfao");
	for(ft::vector<std::string>::const_iterator itr = string_vector.begin(); itr != string_vector.end(); itr++)
		std::cout << *itr << std::endl;

	/* 
	**	ga die reverse dingen testen dan als je die rotareti hebt geschreven
	*/
}

//////////////
// CAPACITY //
//////////////
static void capacity_test()
{
	print_header("VECTOR CAPACITY");
	ft::vector<int>	vec;
	whats_in_this_vector_yo(vec, "empty vector");
	std::cout << "max_size = " << vec.max_size() << std::endl;
	std::cout << "is empty = " << vec.empty() << std::endl;
	vec.reserve(42);
	whats_in_this_vector_yo(vec, "after reserve for 42");
	std::cout << "capacity = " << vec.capacity() << std::endl;
	std::cout << "is empty = " << vec.empty() << std::endl;
	vec.resize(69, 420);
	whats_in_this_vector_yo(vec, "after resize tot 69 with 420");
	std::cout << "capacity = " << vec.capacity() << std::endl;
	std::cout << "is empty = " << vec.empty() << std::endl;
	vec.resize(21, 69);
	whats_in_this_vector_yo(vec, "after resize tot 21 with 69");
	std::cout << "capacity = " << vec.capacity() << std::endl;
	std::cout << "is empty = " << vec.empty() << std::endl;

}

void	vector_test() {
	constructor_test();
	iterator_test();
	capacity_test();
}
