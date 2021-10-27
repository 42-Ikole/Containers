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
	template < class Key, class T >
		struct map_node
	{

	///////////////
	// type defs //
	///////////////
	public:
			
		typedef Key										key_type;
		typedef T										mapped_type;
		typedef ft::pair<key_type, mapped_type>			value_type;
		typedef	std::ptrdiff_t							difference_type;
		typedef	std::size_t								size_type;
		typedef map_node<key_type, mapped_type>			node;
	
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

		map_node(const value_type& val, node* p = NULL, node* l = NULL, node* r = NULL, colors c = red)
			: value(val), parent(p), left(l), right(r), color(c)
		{}

		~map_node()
		{
		}

		map_node(const map_node& x)
		{
			*this = x;
		}

		map_node&	operator = (const map_node &x)
		{
			this->value		= x.value;
			this->parent	= x.parent;
			this->left		= x.left;
			this->right		= x.right;
			this->color		= x.color;
			return (*this);
		}

	/////////////////////////////
	// Public member functions //
	/////////////////////////////
	public:

		key_type&	key(void)
		{
			return (value.first);
		}

		colors		uncle_color()
		{
			if (parent == parent->parent->right) {
				if (parent->parent->left == NULL)
					return (black);
				return (parent->parent->left->color);
			}
			if (parent->parent->right == NULL)
				return (black);
			return (parent->parent->right->color);
		}

		colors		sibling_color()
		{
			if (this == parent->right) {
				if (parent->left == NULL)
					return (black);
				return (parent->left->color);
			}
			if (parent->right == NULL)
				return (black);
			return (parent->right->color);
		}
		
	}; /* end of map_node */

} /* end of namespace */

# endif
