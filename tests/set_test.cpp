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
	#include <set>
	namespace ft = std;
#else
	#include <set.hpp>
#endif


template <class T>
void	whats_in_this_set_yo(ft::set<T>& con)
{
	typedef typename ft::set<T>::iterator iterator;

	std::cout << "size: " << con.size() << "\n";
	std::cout << "max size: " << con.max_size() << "\n";
	std::cout << "empty: " << con.empty() << "\n";

	for (iterator i = con.begin(); i != con.end(); ++i)
		std::cout << *i << " ";
	std::cout << "\n";
}

/////////////////
// CONSTRUCTOR //
/////////////////
static void constructor_test()
{

/* default constructor */

	ft::set<std::string> dc;
	whats_in_this_set_yo(dc);


// // /* range constructor */
// 	ft::set<int, std::string> rc(fc.begin(), fc.end() - 21);
// 	std::set<int, std::string> std_rc(std_fc.begin(), std_fc.end() - 21);
// 	compare(rc, std_rc, compare_these_sets_yo, "range constructor");

	for (int i = 0; i < 15; i++) {
		dc.insert(std::to_string(i));
	}

/* copy constructor */
	ft::set<std::string> cc(dc);
	whats_in_this_set_yo(cc);

/* test for deep copy */
	dc.erase(dc.begin());
	whats_in_this_set_yo(cc);
	whats_in_this_set_yo(dc);

/* assigantion operator */
	ft::set<std::string> ass = cc;
	whats_in_this_set_yo(ass);

/* test for deep copy */
	cc.erase(++(dc.begin()));
	whats_in_this_set_yo(cc);
	whats_in_this_set_yo(dc);
}

///////////////
// Observers //
///////////////
static void observer_test()
{
	ft::set<size_t>						set;
	ft::set<size_t>::iterator			itr;
	ft::set<size_t>::const_iterator		citr;

	for (size_t i = 0; i < 15; i++) {
		set.insert(i);
	}

/* testing value compare second argument is bigger */
	itr = set.begin();
	bool res = set.value_comp()(*itr, *(++itr));
	std::cout << "vc: " << res;

/* testing value compare first arguement is bigger */
	res = set.value_comp()(*(++itr), *itr);
	std::cout << "vc: " << res;

/* testing key compare second argument is bigger */
	res = set.key_comp()(*itr, *(++itr));
	std::cout << "kc: " << res;

/* testing key compare first arguement is bigger */
	res = set.key_comp()(*(++itr), *itr);
	std::cout << "kc: " << res;
}

////////////////////
// ELEMENT ACCESS //
////////////////////
static void element_access_test()
{
	ft::set<std::string>		set;

/* opeartor [] */
	for (size_t i = 0; i < 1337; i++) {
		set.insert(std::to_string(i));
	}
	whats_in_this_set_yo(set);

	for (size_t i = 1337; i > 0; --i) {
		set.insert(std::to_string(i));
	}
	whats_in_this_set_yo(set);

	for (size_t i = 0; i < 1337; i++) {
		set.insert(std::to_string(rand()));
	}
	whats_in_this_set_yo(set);

/* swap */
	ft::set<std::string>				tbs;
	tbs.insert("About to get swapped :0");

	set.swap(tbs);
	whats_in_this_set_yo(set);
	whats_in_this_set_yo(tbs);
}

///////////////
// MODIFIERS //
///////////////
static void modifier_test()
{
	ft::set<size_t>	set;
	ft::set<size_t>	empty;

/* insert */
	for (size_t i = 0; i < 5000; i++) {
		set.insert(i);
	}
	whats_in_this_set_yo(set);

/* return value key doesnt exist */
	bool res = set.insert(42069).second;
	std::cout << res;

/* return value key exists */
	res = set.insert(420).second;
	std::cout << res;

/* insert */
	for (size_t i = 0; i < 5555; i++) {
		set.insert(i);
	}
	whats_in_this_set_yo(set);

/* erase */
	while (set.size() > 1337) {
		set.erase(set.begin());
	}
	whats_in_this_set_yo(set);

/* hint insert */
	for (size_t i = 0; i < 5000; i++) {
		set.insert(--set.end(), i);
	}
	whats_in_this_set_yo(set);

/* erase value */
	for (size_t i = set.size(); i > 1337; i--) {
		set.erase(i);
	}
	whats_in_this_set_yo(set);

/* clear */
	set.clear();
	whats_in_this_set_yo(set);

/* clear */
	set.clear();
	whats_in_this_set_yo(set);
}

static void operations_test()
{
	typedef ft::set<size_t>::iterator		iterator;
	typedef ft::set<size_t>::const_iterator	citerator;

	ft::set<size_t>	set;
	iterator		itr;
	citerator		citr;

	for (size_t i = 0; i < 420; i++) {
		set.insert(i);
	}

	/* find */
	itr = set.find((size_t)69);
	std::cout << *itr;
	
	/* const find */
	citr = set.find((size_t)42);
	std::cout << *citr;

	/* find non existing */
	itr = --set.find((size_t)1337);
	std::cout << *itr;
	
	/* const find non existing */
	citr = --set.find((size_t)1337);
	std::cout << *citr;

	/* count */
	bool res = set.count(21);
	std::cout << res;

	/* count non existante */
	res = set.count(42069);
	std::cout << res;

	/* lower bound */
	itr = set.lower_bound((size_t)200);
	std::cout << *itr;
	
	/* lower bound  const */
	citr = set.lower_bound((size_t)69);
	std::cout << *citr;

	/* lower bound existing */
	itr = --set.lower_bound((size_t)-1);
	std::cout << *itr;
	
	/* lower bound non existing */
	citr = --set.lower_bound((size_t)-42);
	std::cout << *citr;

	/* lower bound */
	set.insert((size_t)1337);
	itr = set.lower_bound(1200);
	std::cout << *itr;

	/* upper bound */
	itr = set.upper_bound((size_t)200);
	std::cout << *itr;
	
	/* upper bound  const */
	citr = set.upper_bound((size_t)69);
	std::cout << *citr;

	/* upper bound existing */
	itr = --set.upper_bound((size_t)-1);
	std::cout << *itr;
	
	/* upper bound non existing */
	citr = --set.upper_bound((size_t)-42);
	std::cout << *citr;

	/* upper bound */
	itr = set.upper_bound(1200);
	std::cout << *itr;

	/* equal range */
	ft::pair<iterator, iterator>	pair;
	ft::pair<citerator, citerator>	cpair;

	pair = set.equal_range((size_t)200);
	std::cout << *(pair.first) << *(pair.second);

	/* equal range  const */
	cpair = set.equal_range((size_t)69);
	std::cout << *(cpair.first) << *(cpair.second);

	/* equal range existing */
	pair = set.equal_range((size_t)-1);
	pair.first--; pair.second--;
	std::cout << *(pair.first) << *(pair.second);
	
	/* equal range non existing */
	cpair = set.equal_range((size_t)-42);
	cpair.first--; cpair.second--;
	std::cout << *(cpair.first) << *(cpair.second);

	/* equal range */
	pair = set.equal_range(1200);
	std::cout << *(pair.first) << *(pair.second);
}

static void set_stress()
{
	ft::set<test> set;
	ft::set<test> copy;

	for (size_t i = 0; i < 420690; i++)
		set.insert(test(i, "data"));

	while (set.size() > 1337)
		set.erase(set.begin());

	for (size_t i = 0; i < 420690; ++i)
		set.insert(test(420, "baby"));

	copy = set;

	for (size_t i = set.size(); i > 0; i--)
		set.erase(i);

	for (size_t i = 0; i < 16; i++) {
		set = copy;
		set.clear();
	}

	copy.erase(copy.begin(), copy.end());

}

void	set_test()
{
	print_header("set member functions");

	constructor_test();
	element_access_test(); 
	modifier_test();
	operations_test();
	observer_test();
	set_stress();
}
