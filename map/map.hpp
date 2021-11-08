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

#ifndef MY_SUPER_EPIC_MAP_HPP
# define MY_SUPER_EPIC_MAP_HPP

# include <memory>
# include <pair.hpp>
# include <rnb_tree.hpp>
# include <utility.hpp>
# include <map_iterator.hpp>

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
			
		typedef Key																	key_type;
		typedef T																	mapped_type;
		typedef ft::pair<key_type, mapped_type>										value_type;
		typedef Compare																key_compare;
		typedef Alloc																allocator_type;
		typedef typename allocator_type::reference									reference;
		typedef typename allocator_type::const_reference							const_reference;
		typedef typename allocator_type::pointer									pointer;
		typedef typename allocator_type::const_pointer								const_pointer;
		typedef ft::rnb_tree<key_type, mapped_type, key_compare, allocator_type>	tree_type;
		typedef typename tree_type::node											node;
		typedef typename tree_type::difference_type									difference_type;
		typedef typename tree_type::size_type										size_type;

		/* iterators fkdjfkjdskfjdksjf */

		typedef ft::map_iterator< value_type, difference_type, ft::bidirectional_iterator_tag, node* >						iterator;
		typedef ft::map_iterator< value_type, difference_type, ft::bidirectional_iterator_tag, node*, const value_type& >	const_iterator; // kan nu geen const pointer

	//////////////////////
	// Member variables //
	//////////////////////
	private:

		tree_type	_tree;

	/////////////
	// CoPlIeN //
	/////////////
	public:
	
		explicit map (const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type())
				: _tree(tree_type(comp, alloc))
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
			this->_tree = x._tree;
			return (*this);
		}

	//////////////////
	// Iterators 🤮 //
	//////////////////
	public:

		iterator begin()
		{
			std::cout << "smallest = " << _tree._root->find_smallest()->value.first << std::endl;
			return (iterator(_tree._root->find_smallest()));
		}

		const_iterator begin() const
		{
			return (iterator(_tree._root->find_smallest()));
		}

		iterator end()
		{
			return (iterator(_tree._root->find_biggest()));
		}

		const_iterator end() const
		{
			return (iterator(_tree._root->find_biggest()));
		}

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
			return (_tree.empty());
		}

		size_type size() const
		{
			return (_tree.size());
		}

		size_type max_size() const
		{
			return (_tree.max_size());
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
		// node*	insert(const value_type& val)
		ft::pair<iterator, bool> insert(const value_type& val)
		{
			return (ft::make_pair(iterator(_tree.insert(val)), true));
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

		void erase(iterator position)
		{
			_tree.erase(position.get_ptr());
		}

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
			return (_tree.key_comp());
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

} /* end of namespace */

#endif
