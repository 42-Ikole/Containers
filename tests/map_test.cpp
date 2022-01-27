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


template <class first, class second>
void	whats_in_this_map_yo(ft::map<first, second>& con)
{
	typedef typename ft::map<first, second>::iterator iterator;

	std::cout << "size: " << con.size() << "\n";
	std::cout << "max size: " << con.max_size() << "\n";
	std::cout << "empty: " << con.empty() << "\n";

	for (iterator i = con.begin(); i != con.end(); ++i)
		std::cout << (*i).first << " " << (*i).second << " ";
	std::cout << "\n";
}

/////////////////
// CONSTRUCTOR //
/////////////////
static void constructor_test()
{

/* default constructor */

	ft::map<int, std::string> dc;
	whats_in_this_map_yo(dc);


// // /* range constructor */
// 	ft::map<int, std::string> rc(fc.begin(), fc.end() - 21);
// 	std::map<int, std::string> std_rc(std_fc.begin(), std_fc.end() - 21);
// 	compare(rc, std_rc, compare_these_maps_yo, "range constructor");

	for (int i = 0; i < 15; i++) {
		dc.insert(ft::make_pair(i, std::string("yos")));
	}

/* copy constructor */
	ft::map<int, std::string> cc(dc);
	whats_in_this_map_yo(cc);

/* test for deep copy */
	dc.erase(dc.begin());
	whats_in_this_map_yo(cc);
	whats_in_this_map_yo(dc);


/* assigantion operator */
	ft::map<int, std::string> ass = cc;
	whats_in_this_map_yo(ass);

/* test for deep copy */
	cc.erase(++(dc.begin()));
	whats_in_this_map_yo(cc);
	whats_in_this_map_yo(cc);
}

///////////////
// Observers //
///////////////
static void observer_test()
{
	ft::map<size_t, int>							map;
	ft::map<size_t, int>::iterator					itr;
	ft::map<size_t, int>::const_iterator			citr;

	for (size_t i = 0; i < 15; i++) {
		map.insert(ft::make_pair(i, (int)i));
	}

/* testing value compare second argument is bigger */
	itr = map.begin();
	bool res = map.value_comp()(*itr, *(++itr));
	std::cout << "vc: " << res;

/* testing value compare first arguement is bigger */
	res = map.value_comp()(*(++itr), *itr);
	std::cout << "vc: " << res;


/* testing key compare second argument is bigger */
	res = map.key_comp()((*itr).first, (*(++itr)).first);
	std::cout << "kc: " << res;

/* testing key compare first arguement is bigger */
	res = map.key_comp()((*(++itr)).first, (*itr).first);
	std::cout << "kc: " << res;
}

////////////////////
// ELEMENT ACCESS //
////////////////////
static void element_access_test()
{
	ft::map<std::string, unsigned char>		map;

/* opeartor [] */
	for (size_t i = 0; i < 1337; i++) {
		map[std::to_string(i)] = (unsigned char)i;
	}
	whats_in_this_map_yo(map);

	for (size_t i = 1337; i > 0; --i) {
		map[std::to_string(i)] = (unsigned char)i;
	}
	whats_in_this_map_yo(map);

	size_t rando;
	for (size_t i = 0; i < 1337; i++) {
		rando = rand();
		map[std::to_string(rando)] = (unsigned char)i;
	}
	whats_in_this_map_yo(map);

/* swap */
	ft::map<std::string, unsigned char>				tbs;
	tbs["I am going to be swapped"] = 69;

	map.swap(tbs);
	whats_in_this_map_yo(map);
	whats_in_this_map_yo(tbs);
}

///////////////
// MODIFIERS //
///////////////
static void modifier_test()
{
	ft::map<size_t, std::string>	map;
	ft::map<size_t, std::string>	empty;

/* insert */
	for (size_t i = 0; i < 5000; i++) {
		map.insert(ft::make_pair(i, std::string("yos")));
	}
	whats_in_this_map_yo(map);

/* return value key doesnt exist */
	bool res = map.insert(ft::make_pair(42069, std::string("new"))).second;
	std::cout << res;

/* return value key exists */
	res = map.insert(ft::make_pair(420, std::string("exists"))).second;
	std::cout << res;

/* insert */
	for (size_t i = 0; i < 5000; i++) {
		map.insert(ft::make_pair(i, std::string("exists")));
	}
	whats_in_this_map_yo(map);

/* erase */
	while (map.size() > 1337) {
		map.erase(map.begin());
	}
	whats_in_this_map_yo(map);

/* hint insert */
	for (size_t i = 0; i < 5000; i++) {
		map.insert(--map.end(), ft::make_pair(i, std::string("exists")));
	}
	whats_in_this_map_yo(map);

/* erase value */
	for (size_t i = map.size(); i > 1337; i--) {
		map.erase(i);
	}
	whats_in_this_map_yo(map);

/* clear */
	map.clear();
	whats_in_this_map_yo(map);

/* clear */
	map.clear();
	whats_in_this_map_yo(map);
}

static void operations_test()
{
	typedef ft::map<size_t, char>::iterator			iterator;
	typedef ft::map<size_t, char>::const_iterator	citerator;

	ft::map<size_t, char>		map;
	iterator					itr;
	citerator				citr;

	for (size_t i = 0; i < 420; i++) {
		map[i] = (char)i;
	}

	/* find */
	itr = map.find((size_t)69);
	std::cout << (*itr).first << (*itr).second;
	
	/* const find */
	citr = map.find((size_t)42);
	std::cout << (*citr).first << (*citr).second;

	/* find non existing */
	itr = --map.find((size_t)1337);
	std::cout << (*itr).first << (*itr).second;
	
	/* const find non existing */
	citr = --map.find((size_t)1337);
	std::cout << (*citr).first << (*citr).second;

	/* count */
	bool res = map.count(21);
	std::cout << res;

	/* count non existante */
	res = map.count(42069);
	std::cout << res;

	/* lower bound */
	itr = map.lower_bound((size_t)200);
	std::cout << (*itr).first << (*itr).second;
	
	/* lower bound  const */
	citr = map.lower_bound((size_t)69);
	std::cout << (*citr).first << (*citr).second;

	/* lower bound existing */
	itr = --map.lower_bound((size_t)-1);
	std::cout << (*itr).first << (*itr).second;
	
	/* lower bound non existing */
	citr = --map.lower_bound((size_t)-42);
	std::cout << (*citr).first << (*citr).second;

	/* lower bound */
	map[1337] = 'a';
	itr = map.lower_bound(1200);
	std::cout << (*itr).first << (*itr).second;

	/* upper bound */
	itr = map.upper_bound((size_t)200);
	std::cout << (*itr).first << (*itr).second;
	
	/* upper bound  const */
	citr = map.upper_bound((size_t)69);
	std::cout << (*citr).first << (*citr).second;

	/* upper bound existing */
	itr = --map.upper_bound((size_t)-1);
	std::cout << (*itr).first << (*itr).second;
	
	/* upper bound non existing */
	citr = --map.upper_bound((size_t)-42);
	std::cout << (*citr).first << (*citr).second;

	/* upper bound */
	itr = map.upper_bound(1200);
	std::cout << (*itr).first << (*itr).second;

	/* equal range */
	ft::pair<iterator, iterator>	pair;
	ft::pair<citerator, citerator>	cpair;

	pair = map.equal_range((size_t)200);
	std::cout << (*(pair.first)).first << (*(pair.first)).second << (*(pair.second)).first << (*(pair.second)).second;

	/* equal range  const */
	cpair = map.equal_range((size_t)69);
	std::cout << (*(cpair.first)).first << (*(cpair.first)).second << (*(cpair.second)).first << (*(cpair.second)).second;

	/* equal range existing */
	pair = map.equal_range((size_t)-1);
	pair.first--; pair.second--;
	std::cout << (*(pair.first)).first << (*(pair.first)).second << (*(pair.second)).first << (*(pair.second)).second;
	
	/* equal range non existing */
	cpair = map.equal_range((size_t)-42);
	cpair.first--; cpair.second--;
	std::cout << (*(cpair.first)).first << (*(cpair.first)).second << (*(cpair.second)).first << (*(cpair.second)).second;

	/* equal range */
	pair = map.equal_range(1200);
	std::cout << (*(pair.first)).first << (*(pair.first)).second << (*(pair.second)).first << (*(pair.second)).second;
}

static void map_stress()
{
	ft::map<std::size_t, test> map;
	ft::map<std::size_t, test> copy;

	for (size_t i = 0; i < 420690; i++)
		map.insert(ft::make_pair(i, test(420, "data")));

	while (map.size() > 1337)
		map.erase(map.begin());

	for (size_t i = 0; i < 420690; ++i)
		map[i] = test(420, "baby");

	copy = map;

	for (size_t i = map.size(); i > 0; i--)
		map.erase(i);

	for (size_t i = 0; i < 16; i++) {
		map = copy;
		map.clear();
	}

	copy.erase(copy.begin(), copy.end());

}

void	map_test()
{
	print_header("map member functions");

	constructor_test();
	element_access_test(); 
	modifier_test();
	operations_test();
	observer_test();
	map_stress();
}
