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

#ifndef RNB_TREE_HPP
# define RNB_TREE_HPP

# include <memory>
# include <pair.hpp>
# include <rnb_node.hpp>
# include <utility.hpp>

/////////////////////////////
// defines for readability //
/////////////////////////////

	# define grandparent	parent->parent
	# define left_uncle		parent->parent->left
	# define right_uncle	parent->parent->right

namespace ft
{

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
		class rnb_tree
	{

	///////////////
	// type defs //
	///////////////
	public:
			
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef ft::pair<key_type, mapped_type>				value_type;
		typedef Compare										key_compare;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef	std::ptrdiff_t								difference_type;
		typedef	std::size_t									size_type;
		typedef ft::rnb_node<key_type, mapped_type>			node;
		typedef std::allocator<node>						node_allocator_type;

	//////////////////////
	// Member variables //
	//////////////////////
	public:

		node*				_root;
		node*				_begin; // sentinel for (begin -1)
		node*				_end;   // sentinel for (end)
		key_compare			_comp;
		size_type			_size;
		allocator_type		_alloc;
		node_allocator_type	_node_alloc;

	/////////////
	// CoPlIeN //
	/////////////
	public:
	
		explicit rnb_tree (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
				: _root(NULL), _comp(comp), _size(0), _alloc(alloc), _node_alloc(node_allocator_type())
		{
			_begin = _new_node(value_type());
			_begin->color = black;
			_begin->left = _begin;
			_end = _new_node(value_type());
			_end->right = _end;
			_end->color = black;
		}

		~rnb_tree()
		{

		}

		rnb_tree (const rnb_tree& x)
		{
			*this = x;
		}

		rnb_tree& operator = (const rnb_tree &x)
		{
			this->_comp = x._comp;
			return (*this);
		}

	/////////////
	// Helpers //
	/////////////
	private:

		void	_print_node_address(node* x)
		{
			std::cout << ((x->color == red) ? "\033[31;01m" : "") << "[" << x->value.first << "]\033[0m" << (void*)x;
			std::cout << " parent: " << (void*)x->parent \
					  << " left:   " << (void*)x->left \
					  << " right:  " << (void*)x->right << std::endl;
		}

		void	_print_tree(const std::string& prefix, node* x, bool isLeft)
		{
			if(x != NULL)
			{
				std::cout << prefix;
				std::cout << (isLeft ? "\033[33m├──\033[0m" : "└──" );
				// print the value of the node
				if (x == x->left || x == x->right) {
					std::cout << ((x->color == red) ? "\033[31;01m" : "") << "[sen]\033[0m" << std::endl;
					return ;
				}
				std::cout << ((x->color == red) ? "\033[31;01m" : "") << "[" << x->value.first << "]\033[0m" << std::endl;
				if ((x->left && x->left->parent != x) || (x->right && x->right->parent != x))
					exit(69);
				// enter the next tree level - left and right branch
				this->_print_tree( prefix + (isLeft ? "│   " : "    "), x->left, true);
				this->_print_tree( prefix + (isLeft ? "│   " : "    "), x->right, false);
			}
		}

		bool	_is_not_null(node* x)
		{
			if (x == NULL || x == _begin || x == _end)
				return (false);
			return (true);
		}

		node*	_new_node(const value_type& val)
		{
			node* ret;

			ret = _node_alloc.allocate(1);
			_node_alloc.construct(ret, node(val));
			return (ret);
		}

		void	_destroy_node(node* x)
		{
			_node_alloc.destroy(x);
			_node_alloc.deallocate(x, 1);
		}

		void	_remove_node(node* x)
		{
			if (x == _root)
				_root = NULL;
			else
			{
				if (x->parent->right == x)
					x->parent->right = NULL;
				else
					x->parent->left = NULL;
			}
			this->_destroy_node(x);
			_size--;
		}

		node*	_find_largest_in_subtree(node* x)
		{
			while (_is_not_null(x->right))
				x = x->right;
			return (x);
		}

		void	_set_sentinel_begin(node* hint = NULL)
		{
			if (hint == NULL)
				hint = _root->find_smallest();
			hint->left = _begin;
			_begin->parent = hint;
		}

		void	_set_sentinel_end(node* hint = NULL)
		{
			if (hint == NULL)
				hint = _root->find_biggest();
			hint->right = _end;
			_end->parent = hint;
		}

		void	_set_sentinels()
		{
			this->_set_sentinel_begin();
			this->_set_sentinel_end();
		}

	///////////////
	// Rotations //
	///////////////
	private:

		void	_left_rotate(node* x)
		{
			node* y = x->right;

			/* assign y's left subtree to x */
			x->right = y->left;
			if (_is_not_null(y->left))
				y->left->parent = x;
			y->parent = x->parent;
			
			/* x was root */
			if (x->parent == NULL)
				_root = y;
			
			/* if x was the left child, y becomes left child */
			else if (x == x->parent->left)
				x->parent->left = y;

			/* y becomes right child */
			else
				x->parent->right = y;
	
			y->left = x;
			x->parent = y;
		}

		void	_right_rotate(node* x)
		{	
			node* y = x->left;

			/* assign y's right subtree to x */
			x->left = y->right;
			if (_is_not_null(y->right))
				y->right->parent = x;
			y->parent = x->parent;

			/* x was root */
			if (x->parent == NULL)
				_root = y;
			
			/* if x was a right child, y becomes right child */
			else if (x == x->parent->right)
				x->parent->right = y;

			/* y becomes left child */
			else
				x->parent->left = y;

			y->right = x;
			x->parent = y;
		}

	//////////////////////////
	// Insert violation fix //
	//////////////////////////
	private:

		/* violation routine */
		void	_insert_violation_justifier(node* x)
		{
			while (x->parent && x->parent->color == red) {
				if (x->uncle_color() == red) {
					x = this->_insert_case_one(x);
				}
				else {
					x = this->_insert_case_two(x);
					this->_insert_case_three(x);
				}
			}
			_root->color = black;
		}

		/*
		** Violation case one:
		** -------------------
		** violator has a red uncle.
		** recolor parent, grandparent and uncle
		*/
		node*	_insert_case_one(node* x)
		{
			x->parent->flip_color();
			x->grandparent->flip_color();
			if (x->parent == x->right_uncle)
				x->left_uncle->flip_color();
			else
				x->right_uncle->flip_color();
			return (x->grandparent);
		}

		/*
		** Violation case two:
		** -------------------
		** Diamond with a black uncle.
		** rotate parent of violator in oposite direction
		*/
		node*	_insert_case_two(node* x)
		{
			node*	y = x->parent;

			/* uncle on left side of grandparent */
			if (x == x->parent->left && x->parent == x->right_uncle)
				this->_right_rotate(x->parent);

			/* uncle on right side of grandparent */
			else if (x == x->parent->right && x->parent == x->left_uncle)
				this->_left_rotate(x->parent);
			
			/* its a line and x is violator*/
			else
				return (x);
			
			/* fixed violation and old parent is now new violator (line) */
			return (y);
		}

		/*
		** Violation case three:
		** ---------------------
		** Line with a black uncle
		** flip color of parent and grandparent.
		** then rotate in opposite direction of the line
		*/
		void	_insert_case_three(node* x)
		{
			x->parent->flip_color();
			x->grandparent->flip_color();

			/* line on right side of grandparent */
			if (x->parent == x->right_uncle)
				this->_left_rotate(x->grandparent);

			/* line on left side of grandparent */
			else
				this->_right_rotate(x->grandparent);
		}

	//////////////////////////
	// Delete violation fix //
	//////////////////////////
	private:

		void	_delete_violation_justifier(node* x)
		{
			if (x == NULL)
				return ;
			while (1) {

				/* base case, no violation */
				if (x == _root || x->color == red)
					break ;

				/* case 1 */
				else if (x->sibling_color() == red)
					this->_delete_case_one(x);

				/* case 2, always instantly fixed */
				else if (x->nephew_color() == red) {
					x = this->_delete_case_two(x);
					break ;
				}

				/* case 3 */
				else if (x->niece_color() == red)
					this->_delete_case_three(x);

				/* case 4 */
				else
					x = this->_delete_case_four(x);
			}
			x->color = black;
		}

		/*
		** Violation case one:
		** -------------------
		** x has a red sibling
		** color parent red and sibling black
		** rotate sibling to parent
		*/
		void	_delete_case_one(node* x)
		{
			x->parent->color = red;

			/* sibling is left child */
			if (x == x->parent->right) {
				x->parent->left->color = black;
				this->_right_rotate(x->parent->left);
			}

			/* sibling is right child */
			else {
				x->parent->right->color = black;
				this->_left_rotate(x->parent->right);
			}
		}

		/*
		** Violation case two:
		** -------------------
		** Color sibling same color as parent
		** Color nephew and parent black
		** rotate sibling to parent
		*/
		node*	_delete_case_two(node* x)
		{
			x = x->get_nephew();
	
			/* color sibling same color as parent (of old x) */
			x->parent->color = x->grandparent->color;

			x->grandparent->color = black;
			x->color = black;
		
			/* set x to sibling */
			x = x->parent;

			/* sibling is right child */
			if (x == x->parent->right)
				this->_left_rotate(x->parent);

			/* sibling is left child */
			else
				this->_right_rotate(x->parent);
			
			/* return root because case 1 is final */
			return (_root);
		}


		/*
		** Violation case three:
		** ---------------------
		** color niece black and sibling red
		** rotate niece to sibling
		** results in violation case 2
		*/
		void	_delete_case_three(node* x)
		{
			x = x->get_niece();

			x->color = black;
			x->parent->color = red;

			/* niece is right child */
			if (x == x->parent->right)
				this->_left_rotate(x->parent);
			
			/* niece is left child */
			else
				this->_right_rotate(x->parent);
		}

		/*
		** Violation case four:
		** --------------------
		** color sibling red
		** violation moves to parent :/
		*/
		node*	_delete_case_four(node* x)
		{
			/* sibling is a left child */
			if (x == x->parent->right)
				x->parent->left->color = red;
			
			/* sibling is a right child */
			else
				x->parent->right->color = red;

			return (x->parent);
		}

	////////////////////
	// Erase routines //
	////////////////////
	private:

		bool	_move_node_to_leaf(node* x)
		{
			while (x->is_leaf(_begin, _end) == false)
			{
				if (_is_not_null(x->left) && x->right == NULL)
					this->_swap_left_child(x);
				else if (_is_not_null(x->right) && x->left == NULL)
					this->_swap_right_child(x);
				else
					this->_swap_predecessor(x);
			}
			if (x->right == _end || x->right == _end)
				return (true);
			return (false);
		}

		void	_swap_predecessor(node* x)
		{
			node* y = _find_largest_in_subtree(x->left);
			if (x->left == y)
				return this->_swap_left_child(x);

			/* x is root */
			if (x == _root)
				_root = y;
			
			/* x is a left child */
			else if (x->parent->left == x)
				x->parent->left = y;
			
			/* x is a right child */
			else
				x->parent->right = y;

			/* set child parent links */
			if (x->right)
				x->right->parent = y;
			if (x->left)
				x->left->parent = y;
			
			if (y->parent->right == y)
				y->parent->right = x;
			else
				y->parent->left = x;

			if (y->left)
				y->left->parent = x;
			x->swap(y);
		}

		void	_swap_right_child(node* x)
		{
			node* y = x->right;
			y->parent = x->parent;

			if (x == _root)
				_root = y;
			else {
				if (x->parent->left == x)
					x->parent->left = y;
				else
					x->parent->right = y;
			}
			if (y->right)
				y->right->parent = x;
			if (y->left)
				y->left->parent = x;

			if (x->left)
				x->left->parent = y;

			x->parent = y;
			ft::value_swap(x->left, y->left);
			x->right = y->right;
			y->right = x;
			if (x->right)
				x->right->parent = x;
			ft::value_swap(x->color, y->color);
		}

		void	_swap_left_child(node* x)
		{
			node* y = x->left;
			y->parent = x->parent;

			if (x == _root)
				_root = y;
			else {
				if (x->parent->left == x)
					x->parent->left = y;
				else
					x->parent->right = y;
			}
			if (y->right)
				y->right->parent = x;
			if (y->left)
				y->left->parent = x;
			if (x->right)
				x->right->parent = y;
			x->parent = y;
			ft::value_swap(x->right, y->right);
			x->left = y->left;
			y->left = x;
			if (x->left)
				x->left->parent = x;
			ft::value_swap(x->color, y->color);
		}

	//////////////
	// Capacity //
	//////////////
	public:

		bool empty() const
		{
			return (_size == 0);
		}

		size_type size() const
		{
			return (_size);
		}

		size_type max_size() const
		{
			return (_alloc.max_size());
		}

	///////////////
	// Modifiers //
	///////////////
	public:

		/* single element */
		node*	insert(const value_type& val)
		{
			std::cerr << "\n---inserting: " << val.first << "---\n\n";

			node* new_node	= this->_new_node(val);
			node* parent	= NULL;

			// find node to go to
			for (node* x = _root; _is_not_null(x);) {
				parent = x;
				if (_comp(new_node->key(), x->key()) == true)
					x = x->left;
				else
					x = x->right;
			}

			// set parents
			new_node->parent = parent;
			if (_root == NULL) {
				_root = new_node;
				this->_set_sentinels();
			}
			else if (_comp(new_node->key(), parent->key()) == true) {
				if (parent->left == _begin)
					this->_set_sentinel_begin(new_node);
				parent->left = new_node;
			}
			else {
				if (parent->right == _end)
					this->_set_sentinel_end(new_node);
				parent->right = new_node;
			}

			/* fix all the violations */
			this->_insert_violation_justifier(new_node);
	
			_size++;
			this->_print_tree("", _root, false);
			return (new_node);
		}

		void	erase(node* x)
		{
			std::cout << "\n---deleting: " << x->value.first << "---\n\n";

			bool reset_sentinel = this->_move_node_to_leaf(x);
			this->_delete_violation_justifier(x);
			this->_remove_node(x);
			if (reset_sentinel == true)
				this->_set_sentinels();
			this->_print_tree("", _root, false);
		}

	///////////////
	// Observers //
	///////////////
	public:

		key_compare key_comp() const
		{
			return (_comp);
		}

		// value_compare value_comp() const
		// {

		// }

	}; /* end of rnb_tree */

} /* end of namespace */


///////////////////
// unset defines //
///////////////////

	# undef grandparent
	# undef left_uncle	
	# undef right_uncle

#endif /* end of guard */
