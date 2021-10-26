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

	///////////////
	// Rotations //
	///////////////
	private:

		void	_print_tree(node* x)
		{
			if (x == NULL)
				return ;
			this->_print_tree(x->left);
			std::cout << ((x->color == red) ? "\033[31;01m" : "") << "[" << x->value.first << "]\033[0m" << (void*)x;
			std::cout << " parent: " << (void*)x->parent \
					  << " left:   " << (void*)x->left \
					  << " right:  " << (void*)x->right << std::endl;
			this->_print_tree(x->right);
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

		void	_violation_justifier(node* x)
		{
			while (x->parent && x->parent->color == red) {
				if (x->get_uncle_color() == red) {
					x = this->_red_uncle(x);
				}
				else {
					x = this->_black_diamond(x);
					this->_black_line(x);
				}
			}
			_root->color = black;
		}

		/* violation case one */
		node*	_red_uncle(node* x)
		{
			std::cout << "red uncle found, flipping colors!\n\n";
			this->_flip_color(x->parent);
			this->_flip_color(x->grandparent);
			if (x->parent == x->right_uncle)
				this->_flip_color(x->left_uncle);
			else
				this->_flip_color(x->right_uncle);
			return (x->grandparent);
		}

		/* violation case two */
		node*	_black_diamond(node* x)
		{
			node*	y = x->parent;

			/* uncle on left side of grandparent */
			if (x == x->parent->left && x->parent == x->right_uncle) {
				std::cout << "right rotate on black diamond (left child)\n\n";
				this->_right_rotate(x->parent);
			}

			/* uncle on right side of grandparent */
			else if (x == x->parent->right && x->parent == x->left_uncle) {
				std::cout << "left rotate on black diamond (right child)\n\n";
				this->_left_rotate(x->parent);
			}
			
			/* its a line and x is violator*/
			else {
				std::cout << "its not a diamond\n\n";
				return (x);
			}
			
			/* fixed violation and old parent is now new violator (line) */
			return (y);
		}

		void	_black_line(node* x)
		{
			this->_flip_color(x->parent);
			this->_flip_color(x->grandparent);
			/* line on right side of grandparent */
			if (x->parent == x->right_uncle) {
				std::cout << "line on right side of grandpa, doing a left rotate\n\n";
				this->_left_rotate(x->grandparent);
			}

			/* line on left side of grandparent */
			else {
				std::cout << "line on left side of grandpa doing a right rotate\n\n";
				this->_right_rotate(x->grandparent);
			}
		}

		void	_left_rotate(node* pivot)
		{
			node* x = pivot->right;

			pivot->right = x->left;
			if (x->left != NULL)
				x->left->parent = pivot;
			x->parent = pivot->parent;
			if (pivot->parent == NULL)
				_root = x;
			else if (pivot == pivot->parent->left)
				pivot->parent->left = x;
			else
				pivot->parent->right = x;
			x->left = pivot;
			pivot->parent = x;
		}

		void	_right_rotate(node* pivot)
		{
			node* x = pivot->left;

			pivot->left = x->right;
			if (x->right != NULL)
				x->right->parent = pivot;
			x->parent = pivot->parent;
			if (pivot->parent == NULL)
				_root = x;
			else if (pivot == pivot->parent->right)
				pivot->parent->right = x;
			else
				pivot->parent->left = x;
			x->right = pivot;
			pivot->parent = x;
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
				if (_comp(new_node->get_key(), x->get_key()) == true)
					x = x->left;
				else
					x = x->right;
			}

			// set parents
			new_node->parent = parent;
			if (_root == NULL)
				_root = new_node;
			else if (_comp(new_node->get_key(), parent->get_key()) == true)
				parent->left = new_node;
			else
				parent->right = new_node;

			/* fix all the violations */
			this->_violation_justifier(new_node);
	
			_size++;
			this->_print_tree(_root);
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
