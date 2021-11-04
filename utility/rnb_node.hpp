/* ************************************************************************** */
/*                                                                            */
/*                               L.                                           */
/*                    j.         EW:        ,ft .                             */
/*                    EW,        E##;       t#E Ef.                           */
/*                    E##j       E###t      t#E E#Wi                          */
/*                    E###D.     E#fE#f     t#E E#K#D:                        */
/*                    E#jG#W;    E#t D#G    t#E E#t,E#f.                      */
/*                    E#t t##f   E#t  f#E.  t#E E#WEE##Wt                     */
/*                    E#t  :K#E: E#t   t#K: t#E E##Ei;;;;.                    */
/*                    E#KDDDD###iE#t    ;#W,t#E E#DWWt                        */
/*                    E#f,t#Wi,,,E#t     :K#D#E E#t f#K;                      */
/*                    E#t  ;#W:  E#t      .E##E E#Dfff##E,                    */
/*                    DWi   ,KK: ..         G#E jLLLLLLLLL;                   */
/*                                           fE                               */
/*                                            ,                               */
/*                                                                            */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RNB_NODE_HPP
# define RNB_NODE_HPP

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
		struct rnb_node
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
		typedef rnb_node<key_type, mapped_type>			node;
	
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

		rnb_node(const value_type& val, node* p = NULL, node* l = NULL, node* r = NULL, e_color c = red)
			: value(val), parent(p), left(l), right(r), color(c)
		{}

		~rnb_node()
		{
		}

		rnb_node(const rnb_node& x)
		{
			*this = x;
		}

		rnb_node&	operator = (const rnb_node &x)
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

		void		swap(node* x)
		{
			ft::value_swap(this->parent,	x->parent);
			ft::value_swap(this->left,		x->left);
			ft::value_swap(this->right,		x->right);
			ft::value_swap(this->color,		x->color);
		}

		bool		is_leaf()
		{
			if (this->left == NULL && this->right == NULL)
				return (true);
			return (false);
		}

		void	flip_color(void)
		{
			this->color = (e_color)!this->color;
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
				if (parent->left == NULL || parent->left->left == NULL)
					return (black);
				return (parent->left->left->color);
			}

			/* nephew is on right side */
			if (parent->right == NULL || parent->right->right == NULL)
				return (black);
			return (parent->right->right->color);
		}
		
		e_color		niece_color()
		{
			/* niece is on left side */
			if (this == parent->right) {
				if (parent->left == NULL || parent->left->right == NULL)
					return (black);
				return (parent->left->right->color);
			}

			/* niece is on right side */
			if (parent->right == NULL || parent->right->left == NULL)
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

		
	}; /* end of rnb_node */

} /* end of namespace */

# endif