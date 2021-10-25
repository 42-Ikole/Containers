/* ************************************************************************** */
/*                                                                            */
/*                              o   o   O   o--o                              */
/*                              |\ /|  / \  |   |                             */
/*                              | O | o---o O--o                              */
/*                              |   | |   | |                                 */
/*                              o   o o   o o                                 */
/*																			  */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_NODE_HPP
# define MAP_NODE_HPP

# include <memory>
# include <pair.hpp>

namespace ft
{

////////////////
// COLOR ENUM //
////////////////

	enum colors {
		red,
		black
	};

//////////////
// MAP NODE //
//////////////
	template < class Key, class T, class Compare >
		struct map_node
	{

	///////////////
	// type defs //
	///////////////
	public:
			
		typedef Key												key_type;
		typedef T												mapped_type;
		typedef ft::pair<const key_type, mapped_type>			value_type;
		typedef Compare											key_compare;
		typedef	std::ptrdiff_t									difference_type;
		typedef	std::size_t										size_type;
		typedef map_node<key_type, mapped_type, key_compare>	node;
	
	//////////////////////
	// Member variables //
	//////////////////////
	public:

		value_type	value;
		node*		parent;
		node*		left;
		node*		right;
		colors		color;

	/////////////////
	// constructor //
	/////////////////
	public:

		map_node(value_type& val, node* p = NULL, node* l = NULL, node* r = NULL, colors c = red)
			: value(val), parent(p), left(l), right(r), color(c)
		{}

	/////////////////////////////
	// Public member functions //
	/////////////////////////////
	public:

		key_type&	get_key(void)
		{
			return (value.first);
		}
		
	}; /* end of map_node */

} /* end of namespace */

# endif
