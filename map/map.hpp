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

#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <pair.hpp>
# include <map_node.hpp>
# include <utility.hpp>

namespace ft
{

/////////////////////////////
// defines for readability //
/////////////////////////////

	# define grandparent	parent->parent
	# define left_uncle		parent->parent->left
	# define right_uncle	parent->parent->right

////////////
// MAPPIE //
////////////

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
		class map
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
		typedef ft::map_node<key_type, mapped_type>			node;
		typedef std::allocator<node>						node_allocator_type;

		/* iterators fkdjfkjdskfjdksjf */

	//////////////////////
	// Member variables //
	//////////////////////
	private:

		node*				_root;
		key_compare			_comp;
		size_type			_size;
		allocator_type		_alloc;
		node_allocator_type	_node_alloc;

	/////////////
	// CoPlIeN //
	/////////////
	public:
	
		explicit map (const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type())
				: _root(NULL), _comp(comp), _size(0), _alloc(alloc), _node_alloc(node_allocator_type())
		{
		
		}

		// template <class InputIterator>
		// 	map (InputIterator first, InputIterator last,
		// 		const key_compare& comp = key_compare(),
		// 		const allocator_type& alloc = allocator_type())
		// 			: _root(NULL), _comp(comp), _size(0), _alloc(alloc), _node_alloc(node_allocator_type())
		// {

		// }

		~map()
		{

		}

		map (const map& x)
		{
			*this = x;
		}

		map& operator = (const map &x)
		{
			this->_comp = x._comp;
			return (*this);
		}

	/////////////
	// Helpers //
	/////////////
	private:

		void	_print_tree(const std::string& prefix, node* x, bool isLeft)
		{
			if( x != NULL )
			{
				std::cout << prefix;

				std::cout << (isLeft ? "\033[33m├──\033[0m" : "└──" );

				// print the value of the node
				std::cout << ((x->color == red) ? "\033[31;01m" : "") << "[" << x->value.first << "]\033[0m" << std::endl;

				// enter the next tree level - left and right branch
				this->_print_tree( prefix + (isLeft ? "│   " : "    "), x->left, true);
				this->_print_tree( prefix + (isLeft ? "│   " : "    "), x->right, false);
			}
		}

		node*	_new_node(const value_type& val)
		{
			node* ret;

			ret = _node_alloc.allocate(1);
			_node_alloc.construct(ret, node(val));
			return (ret);
		}

		void	_flip_color(node* x)
		{
			x->color = (colors)!x->color;
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
			if (y->left != NULL)
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
			if (y->right != NULL)
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
					x = this->_red_uncle(x);
				}
				else {
					x = this->_black_diamond(x);
					this->_black_line(x);
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
		node*	_red_uncle(node* x)
		{
			this->_flip_color(x->parent);
			this->_flip_color(x->grandparent);
			if (x->parent == x->right_uncle)
				this->_flip_color(x->left_uncle);
			else
				this->_flip_color(x->right_uncle);
			return (x->grandparent);
		}

		/*
		** Violation case two:
		** -------------------
		** Diamond with a black uncle.
		** rotate parent of violator in oposite direction
		*/
		node*	_black_diamond(node* x)
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
		void	_black_line(node* x)
		{
			this->_flip_color(x->parent);
			this->_flip_color(x->grandparent);

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
			while (x != NULL) {

				/* base case, no violation */
				if (x == _root || x->color == red)
					break ;

				/* case 1 */
				else if (x->sibling_color() == red)
					this->_red_sibling(x);

				/* case 2, always instantly fixed */
				else if (x->nephew_color() == red) {
					x = this->_red_nephew(x);
					break ;
				}
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
		void	_red_sibling(node* x)
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
		void	_red_nephew(node* x)
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
				this->_left_rotate(x);

			/* sibling is left child */
			else
				this->_right_rotate(x);
			
			/* return root because case 1 is final */
			return (_root);
		}


	//////////////////
	// Iterators 🤮 //
	//////////////////
	public:

		// iterator begin()
		// {

		// }

		// const_iterator begin() const
		// {

		// }

		// iterator end()
		// {

		// }

		// const_iterator end() const
		// {

		// }

		// reverse_iterator rbegin()
		// {

		// }

		// const_reverse_iterator rbegin() const
		// {

		// }

		// reverse_iterator rend()
		// {

		// }

		// const_reverse_iterator rend() const
		// {

		// }

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

	////////////////////
	// Element access //
	////////////////////
	public:

		mapped_type& operator[] (const key_type& k)
		{
			return (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second;
		}

	///////////////
	// Modifiers //
	///////////////
	public:

		/* single element */
		// ft::pair<iterator, bool> insert(const value_type& val)
		void	insert(const value_type& val)
		{
			std::cerr << "\n---inserting: " << val.first << "---\n\n";
			node* new_node	= this->_new_node(val);
			node* parent	= NULL;

			// find node to go to
			for (node* x = _root; x != NULL;) {
				parent = x;
				if (_comp(new_node->key(), x->key()) == true)
					x = x->left;
				else
					x = x->right;
			}

			// set parents
			new_node->parent = parent;
			if (_root == NULL)
				_root = new_node;
			else if (_comp(new_node->key(), parent->key()) == true)
				parent->left = new_node;
			else
				parent->right = new_node;

			/* fix all the violations */
			this->_insert_violation_justifier(new_node);
	
			_size++;
			this->_print_tree("", _root, false);
			// return (ft::makepair())
		}

		/* with hint */
		// iterator insert(iterator position, const value_type& val)
		// {

		// }
	
		// /* range */
		// template <class InputIterator>
		// 	void insert(InputIterator first, InputIterator last)
		// {
			
		// }

		// void erase(iterator position)
		// {

		// }

		// size_type erase(const key_type& k)
		// {

		// }

		// void erase(iterator first, iterator last)
		// {

		// }

		// void swap(map& x)
		// {

		// }

		// void clear()
		// {

		// }
	
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
	
	////////////////
	// Operations //
	////////////////
	public:

		// iterator find(const key_type& k)
		// {

		// }

		// const_iterator find(const key_type& k) const
		// {
			
		// }

		// size_type count(const key_type& k) const
		// {

		// }

		// iterator lower_bound(const key_type& k)
		// {

		// }

		// const_iterator lower_bound(const key_type& k) const
		// {

		// }

		// iterator upper_bound(const key_type& k)
		// {

		// }

		// const_iterator upper_bound(const key_type& k) const
		// {

		// }

		// ft::pair<iterator, iterator> equal_range(const key_type& k)
		// {

		// }

		// ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
		// {

		// }

	}; /* end of map */

	# undef grandparent
	# undef left_uncle	
	# undef right_uncle

} /* end of namespace */

#endif
