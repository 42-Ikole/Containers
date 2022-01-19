
#include <vector.hpp>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <map>
#include <deque.hpp>
#include <deque>
#include <map.hpp>
#include <functional>
#include <hash.hpp>
#include <type_traits.hpp>
#include <is_integral.hpp>
#include <type_traits>
#include <linear_hash_map.hpp>
#include <unordered_set>

struct test {
	static const char* foek;
	test() {}
	~test() {}
	test(const test& x) {*this = x;}
	test operator = (const test& x) {(void)x; return *this;}
};

int main(void)
{

	typedef ft::linear_hash_map<int, ft::hash<int>, ft::equal_to<int> > hm_type;
	// typedef std::unordered_set<int> hm_type;

	hm_type				lhm;
	hm_type::iterator	itr;


	lhm.insert(42);
	// itr = lhm.insert(42).first;
	lhm.insert(69);
	lhm.insert(420);
	lhm.insert(1337);

	// lhm.erase(itr);
	for (hm_type::iterator i = lhm.begin(); i != lhm.end(); ++i)
		std::cout << *i << std::endl;


	for (int i = 0; i < 4206911; ++i) {
		lhm.insert(i);
		// std::cout << i << std::endl;
	}
	

	
	// system("leaks containers | grep -o 'leaks for'");
}
