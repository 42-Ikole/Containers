
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

struct test {
	static const char* foek;
	test() {}
	~test() {}
	test(const test& x) {*this = x;}
	test operator = (const test& x) {(void)x; return *this;}
};

int main(void)
{
	
	// system("leaks containers | grep -o 'leaks for'");
}
