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

namespace ft
{

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
			
		typedef Key													key_type;
		typedef T													mapped_type;
		typedef ft::pair<const key_type, mapped_type>				value_type;
		typedef Compare												key_compare;
		typedef Alloc												allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef	std::ptrdiff_t										difference_type;
		typedef	std::size_t											size_type;
		typedef ft::map_node<key_type, mapped_type, key_compare>	node;
		typedef std::allocator<node>								node_allocator_type;

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

		template <class InputIterator>
			map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
					: _root(NULL), _comp(comp), _size(0), _alloc(alloc), _node_alloc(node_allocator_type())
		{

		}

		~map()
		{

		}

		map (const map& x)
		{
			*this = x;
		}

		map& operator = (const map &x)
		{
			return (*this);
		}

	///////////////
	// Rotations //
	///////////////
	private:

		void	left_rotate(node* pivot)
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

		void	right_rotate(node* pivot)
		{

		}

	//////////////////
	// Iterators 🤮 //
	//////////////////
	public:

		iterator begin()
		{

		}

		const_iterator begin() const
		{

		}

		iterator end()
		{

		}

		const_iterator end() const
		{

		}

		reverse_iterator rbegin()
		{

		}

		const_reverse_iterator rbegin() const
		{

		}

		reverse_iterator rend()
		{

		}

		const_reverse_iterator rend() const
		{

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

	////////////////////
	// Element access //
	////////////////////
	public:

		mapped_type& operator[] (const key_type& k)
		{
			return (*((this->insert(make_pair(k, mapped_type()))).first)).second;
		}

	///////////////
	// Modifiers //
	///////////////
	public:

		/* single element */
		ft::pair<iterator, bool> insert(const value_type& val)
		{

		}

		/* with hint */
		iterator insert(iterator position, const value_type& val)
		{

		}
	
		/* range */
		template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
		{
			
		}

		void erase(iterator position)
		{

		}

		size_type erase(const key_type& k)
		{

		}

		void erase(iterator first, iterator last)
		{

		}

		void swap(map& x)
		{

		}

		void clear()
		{

		}
	
	///////////////
	// Observers //
	///////////////
	public:

		key_compare key_comp() const
		{

		}

		value_compare value_comp() const
		{

		}
	
	////////////////
	// Operations //
	////////////////
	public:

		iterator find(const key_type& k)
		{

		}

		const_iterator find(const key_type& k) const
		{
			
		}

		size_type count(const key_type& k) const
		{

		}

		iterator lower_bound(const key_type& k)
		{

		}

		const_iterator lower_bound(const key_type& k) const
		{

		}

		iterator upper_bound(const key_type& k)
		{

		}

		const_iterator upper_bound(const key_type& k) const
		{

		}

		ft::pair<iterator, iterator> equal_range(const key_type& k)
		{

		}

		ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
		{

		}

	}; /* end of map */

} /* end of namespace */

#endif
