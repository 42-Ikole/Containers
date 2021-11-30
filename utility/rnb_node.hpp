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
# include <utility.hpp>

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

		rnb_node(const value_type& val)
			: value(val), parent(NULL), left(NULL), right(NULL), color(red)
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

		bool		is_leaf(node* begin, node* end)
		{
			if ((this->left == NULL && this->right == NULL) || (this->left == begin && this->right == NULL) || (this->right == end && this->left == NULL))
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

	////////////
	// Limits //
	////////////
	public: 

		node*	find_biggest()
		{
			node* tmp = this;

			while (tmp->right != NULL && tmp->right != tmp->right->right)
				tmp = tmp->right;
			return (tmp);
		}

		node*	find_smallest()
		{
			node* tmp = this;

			while (tmp->left != NULL && tmp->left != tmp->left->left)
				tmp = tmp->left;
			return (tmp);
		}

	///////////////
	// Successor //
	///////////////
	public:

		node*	traverse_up_until_no_longer_left_child()
		{
			node* ret = this;

			while (ret->parent && ret == ret->parent->left)
				ret = ret->parent;
			ret = ret->parent;
			return (ret);
		}

		node*	traverse_up_until_no_longer_right_child()
		{
			node* ret = this;

			while (ret->parent && ret == ret->parent->right)
				ret = ret->parent;
			ret = ret->parent;
			return (ret);
		}

		node*	get_predecessor()
		{
			node* ret = this;

			/* has a left subtree */
			if (ret->left != NULL) {
				/* go left once, then go as far as possible */
				ret = ret->left;
				while (ret->right)
					ret = ret->right;
			}
			else
				ret = this->traverse_up_until_no_longer_left_child();
			return (ret);
		}

		node*	get_successor()
		{
			node* ret = this;

			/* has a right subtree */
			if (ret->right != NULL) {
				/* go right once, then go left as far as possible */
				ret = ret->right;
				while (ret->left)
					ret = ret->left;
			}
			else
				ret = this->traverse_up_until_no_longer_right_child();
			return (ret);
		}

	////////////////////////
	// operator overloads //
	////////////////////////
	public:

		value_type&	operator * () {
			return (value);
		}

		
	}; /* end of rnb_node */

} /* end of namespace */

# endif
