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

		node*				root;
		node*				begin; // sentinel for (begin -1)
		node*				end;   // sentinel for (end)
		key_compare			comp;
		size_type			size;
		allocator_type		alloc;
		node_allocator_type	node_alloc;

	/////////////
	// CoPlIeN //
	/////////////
	public:
	
		explicit rnb_tree (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
				: root(NULL), comp(comp), size(0), alloc(alloc), node_alloc(node_allocator_type())
		{
			this->_init_sentinels();
		}

		~rnb_tree()
		{
			this->clear();
			this->_remove_sentinels();
		}

		rnb_tree (const rnb_tree& x)
		{
			this->_init_sentinels();
			*this = x;
		}

		rnb_tree& operator = (const rnb_tree &x)
		{
			this->clear();
			this->_deep_copy_tree(x.root, NULL, false);
			this->size			= x.size;
			this->comp			= x.comp;
			this->_set_sentinels();
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
					std::cout << ((x->color == red) ? "\033[31;01m" : "") << ((x == x->left) ? "[beg]" : "[end]") << "\033[0m" << std::endl;
					return ;
				}
				std::cout << ((x->color == red) ? "\033[31;01m" : "") << "[" << x->value.first << "]\033[0m" << std::endl;
				if ((x->left && x->left->parent != x) || (x->right && x->right->parent != x)) {
					std::cout << x->value.first << "->left = " << x->left->value.first << "->parent = " << x->left->parent->value.first << std::endl;
					std::cout << x->value.first << "->right = " << x->right->value.first << "->parent = " << x->right->parent->value.first << std::endl;
					exit(69);
				}
				// enter the next tree level - left and right branch
				this->_print_tree( prefix + (isLeft ? "│   " : "    "), x->left, true);
				this->_print_tree( prefix + (isLeft ? "│   " : "    "), x->right, false);
			}
		}

	////////////////////
	// Deep copy tree //
	////////////////////
	private:

		void	_deep_copy_tree(const node* x, node* parent, bool isleft)
		{
			if (x == NULL || x == x->left || x == x->right)
				return ;
			
			node* new_node = this->_new_node(x->value);

			new_node->parent = parent;
			if (parent == NULL)
				root = new_node;
			else if (isleft == false)
				parent->right = new_node;
			else
				parent->left = new_node;
			new_node->color = x->color;
			this->_deep_copy_tree(x->left, new_node, true);
			this->_deep_copy_tree(x->right, new_node, false);
		}

	//////////////////
	// Node helpers //
	//////////////////
	private:

		bool	_is_not_null(node* x) const
		{
			if (x == NULL || x == begin || x == end)
				return (false);
			return (true);
		}
		
		bool	_is_null(node* x) const
		{
			return (!_is_not_null(x));
		}

		node*	_new_node(const value_type& val)
		{
			node* ret;

			ret = node_alloc.allocate(1);
			node_alloc.construct(ret, node(val));
			return (ret);
		}

		void	_destroy_node(node* x)
		{
			node_alloc.destroy(x);
			node_alloc.deallocate(x, 1);
		}

		void	_remove_all_nodes(node* x)
		{
			if (this->_is_not_null(x) == false)
				return ;
			this->_remove_all_nodes(x->left);
			this->_remove_all_nodes(x->right);
			this->_destroy_node(x);
		}

		void	_remove_node(node* x)
		{
			if (x == root)
				root = NULL;
			else
			{
				if (x->parent->right == x)
					x->parent->right = NULL;
				else
					x->parent->left = NULL;
			}
			this->_destroy_node(x);
			size--;
		}

		node*	_find_largest_in_subtree(node* x)
		{
			while (_is_not_null(x->right))
				x = x->right;
			return (x);
		}

		ft::pair<node*, bool>	_insert_find_new_parent(const value_type& val)
		{
			node* parent = NULL;
	
			for (node* x = root; _is_not_null(x);) {
				parent = x;

				if (comp(val.first, x->key()) == false) {
					
					/* if this is true then parent has the same value as new node */
					if (comp(parent->key(), val.first) == false)
						return (ft::make_pair(parent, false));

					x = x->right;
				}
				else
					x = x->left;
			}
			return (ft::make_pair(parent, true));
		}

		void	_insert_set_parents(node* new_node, node* parent)
		{
			new_node->parent = parent;
			if (root == NULL) {
				root = new_node;
				this->_set_sentinels();
			}
			else if (comp(new_node->key(), parent->key()) == true) {
				if (parent->left == begin)
					this->_set_sentinelbegin(new_node);
				parent->left = new_node;
			}
			else {
				if (parent->right == end)
					this->_set_sentinelend(new_node);
				parent->right = new_node;
			}
		}


	//////////////////////
	// Sentinel helpers //
	//////////////////////
	private:

		void	_init_sentinels()
		{
			begin = _new_node(value_type());
			begin->color = black;
			begin->left = begin;
			end = _new_node(value_type());
			end->right = end;
			end->color = black;
			begin->parent = end;
		}

		void	_set_sentinelbegin(node* hint = NULL)
		{
			if (hint == NULL && root != NULL)
				hint = root->find_smallest();
			if (hint)
				hint->left = begin;
			begin->parent = hint;
		}

		void	_set_sentinelend(node* hint = NULL)
		{
			if (hint == NULL && root != NULL)
				hint = root->find_biggest();
			if (hint)
				hint->right = end;
			end->parent = hint;
		}

		void	_set_sentinels()
		{
			this->_set_sentinelbegin();
			this->_set_sentinelend();
		}

		void	_remove_sentinels()
		{
			this->_destroy_node(begin);
			this->_destroy_node(end);
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
				root = y;
			
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
				root = y;
			
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
			root->color = black;
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
				if (x == root || x->color == red)
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
				this->_right_rotate(x->parent);
			}

			/* sibling is right child */
			else {
				x->parent->right->color = black;
				this->_left_rotate(x->parent);
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
			return (root);
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
			while (x->is_leaf(begin, end) == false)
			{
				if (_is_not_null(x->left) && _is_null(x->right))
					this->_swap_left_child(x);
				else if (_is_not_null(x->right) && _is_null(x->left))
					this->_swap_right_child(x);
				else
					this->_swap_predecessor(x);
			}
			if (x->right == end || x->left == begin)
				return (true);
			return (false);
		}

		void	_swap_predecessor(node* x)
		{
			node* y = _find_largest_in_subtree(x->left);
			if (x->left == y)
				return this->_swap_left_child(x);

			/* x is root */
			if (x == root)
				root = y;
			
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

			if (x == root)
				root = y;
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

			if (x == root)
				root = y;
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

		bool		empty() const
		{
			return (size == 0);
		}

	

		size_type	max_size() const
		{
			return (node_alloc.max_size());
		}

	///////////////
	// Modifiers //
	///////////////
	public:

		ft::pair<node*, bool>	insert(const value_type& val)
		{
			node*					new_node;
			ft::pair<node*, bool>	parent;

			parent = this->_insert_find_new_parent(val);
			if (parent.second == false)
				return (parent); /* value already exists in map */

			new_node = this->_new_node(val);
			this->_insert_set_parents(new_node, parent.first);
			this->_insert_violation_justifier(new_node);
	
			++size;
			return (ft::make_pair(new_node, true));
		}

		void	erase(node* x)
		{
			if (x == NULL)
				return ;
		
			bool reset_sentinel = this->_move_node_to_leaf(x);
			this->_delete_violation_justifier(x);
			this->_remove_node(x);

			if (reset_sentinel == true)
				this->_set_sentinels();
	
			if (size == 0)
				begin->parent = end;
		}

		void	clear()
		{
			this->_remove_all_nodes(root);
			root = NULL;
			begin->parent = end;
			size = 0;
		}

		void	swap(rnb_tree& x)
		{
			ft::value_swap(this->root, x.root);
			ft::value_swap(this->begin, x.begin);
			ft::value_swap(this->end, x.end);
			ft::value_swap(this->comp, x.comp);
			ft::value_swap(this->size, x.size);
		}

	///////////////
	// Observers //
	///////////////
	public:

		key_compare key_comp() const
		{
			return (comp);
		}

	////////////////
	// Operations //
	////////////////
	public:

		node*	find(const key_type& val) const
		{
			node* x = root;

			while (_is_not_null(x))
			{
				if (comp(val, x->key()) == false) {
					if (comp(x->key(), val) == false)
						return (x);
					x = x->right;
				}
				else
					x = x->left;
			}
			return (end);
		}

	}; /* end of rnb_tree */

} /* end of namespace */

///////////////
// Swapfiets //
///////////////

	template< class Key, class T, class Compare, class Alloc >
		void swap(ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs)
	{
		lhs.swap(rhs);
	}

//////////////////////////
// CoMpArIsOn oPeRaToRs //
//////////////////////////

	template< class Key, class T, class Compare, class Alloc >
		bool operator == (const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template< class Key, class T, class Compare, class Alloc >
		bool operator != (const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
		bool operator  < (const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template< class Key, class T, class Compare, class Alloc >
		bool operator <= ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {
			return !(rhs < lhs);
	}

	template< class Key, class T, class Compare, class Alloc >
		bool operator  > (const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {
			return (rhs < lhs);
	}

	template< class Key, class T, class Compare, class Alloc >
		bool operator >= (const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {
			return !(lhs < rhs);
	}

///////////////////
// unset defines //
///////////////////

	# undef grandparent
	# undef left_uncle	
	# undef right_uncle

#endif /* end of guard */
