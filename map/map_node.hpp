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

	enum e_color {
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
		e_color		color;

	/////////////////
	// constructor //
	/////////////////
	public:

		map_node(const value_type& val, node* p = NULL, node* l = NULL, node* r = NULL, e_color c = red)
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


	//////////////////////////
	// Node relation e_color //
	//////////////////////////
	public:

		e_color		uncle_color()
		{
			/* uncle is on left side */
			if (parent == parent->parent->right) {
				if (parent->parent->left == NULL)
					return (black);
				return (parent->parent->left->color);
			}

			/* uncle is on right side */
			if (parent->parent->right == NULL)
				return (black);
			return (parent->parent->right->color);
		}

		e_color		sibling_color()
		{
			/* sibling is on left side */
			if (this == parent->right) {
				if (parent->left == NULL)
					return (black);
				return (parent->left->color);
			}

			/* sibling is on right side */
			if (parent->right == NULL)
				return (black);
			return (parent->right->color);
		}

		e_color		nephew_color()
		{
			/* nephew is on left side */
			if (this == parent->right) {
				if (parent->left->left == NULL)
					return (black);
				return (parent->left->left->color);
			}

			/* nephew is on right side */
			if (parent->right->right == NULL)
				return (black);
			return (parent->right->right->color);
		}
		
		e_color		niece_color()
		{
			/* niece is on left side */
			if (this == parent->right) {
				if (parent->left->right == NULL)
					return (black);
				return (parent->left->right->color);
			}

			/* niece is on right side */
			if (parent->right->left == NULL)
				return (black);
			return (parent->right->left->color);
		}

	//////////////////
	// get relation //
	//////////////////
	public:

		node*	get_nephew(void)
		{
			if (this == parent->right)
				return (parent->left->left);
			return (parent->right->right);
		}

		node*	get_niece(void)
		{
			if (this == parent->right)
				return (parent->left->right);
			return (parent->right->left);
		}

		
	}; /* end of map_node */

} /* end of namespace */

# endif
