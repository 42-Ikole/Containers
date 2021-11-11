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
#include <string>
#include <iostream>
#include <tests.hpp>

#ifdef STD
	#include <map>
	namespace ft = std;
#else
	#include <map.hpp>
#endif



/////////////////
// CONSTRUCTOR //
/////////////////
static void constructor_test()
{
	print_header("MAP CONSTRUCTOR");


/* default constructor */
	ft::map<int, int> default_constructor;
	whats_in_this_map_yo(default_constructor, default_constructor.begin(), "default constructor");

/* range constructor */
	for (int i = 0; i < 420; i++)
		default_constructor.insert(ft::make_pair(i, i));
	ft::map<int, int> range_constructor(default_constructor.begin(), default_constructor.end());
	whats_in_this_map_yo(range_constructor, range_constructor.begin(), "default constructor");

}

//////////////
// ITERATOR //
//////////////
static void iterator_test()
{
	print_header("MAP ITERATOR");

	/* 
	**	ga die reverse dingen testen dan als je die rotareti hebt geschreven
	*/
}

//////////////
// CAPACITY //
//////////////
static void capacity_test()
{
	print_header("MAP CAPACITY");

}

////////////////////
// ELEMENT ACCESS //
////////////////////
static void element_access_test()
{
	print_header("MAP ELEMENT ACCESS");

}

///////////////
// MODIFIERS //
///////////////
static void modifier_test()
{
	print_header("MAP Modifier test");

}

struct test {
	public: 
		int			_val;
		std::string	_name;
	public:
		test(int val = 0, std::string name = "unknown") : _val(val), _name(name) {}
		~test() {}

};

std::ostream &operator<<(std::ostream &o, const test &x)
{
	o << "val = " << x._val << " name = " << x._name;
	return (o);
}

static void	stress()
{
	print_header("MAP STRESS TEST");

	ft::map<size_t, test> m;

	for (size_t i = 0; i < 50000000; i++)
		m.insert(ft::make_pair(i, test()));
	whats_in_this_map_yo(m, m.begin(), "stress 1");
}

void	map_test()
{
	constructor_test();
	iterator_test();
	capacity_test();
	element_access_test();
	modifier_test();
	stress();
}
