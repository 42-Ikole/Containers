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
	
		/* default constructor */
		explicit map (const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type())
				: _tree(tree_type(comp, alloc))
		{
		}

		/* range constructor */
		template <class InputIterator>
			map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
					: _tree(tree_type(comp, alloc))
		{
			for (; first != last; first++)
				_tree.insert(*first);
		}

		~map()
		{
			this->clear();
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
			return (iterator(_tree._begin->parent));
		}

		const_iterator begin() const
		{
			return (iterator(_tree._begin->parent));
		}

		iterator end()
		{
			return (iterator(_tree._end));
		}

		const_iterator end() const
		{
			return (iterator(_tree._end));
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
			ft::pair<node*, bool> inserted = _tree.insert(val);
			return (ft::make_pair(iterator(inserted.first), inserted.second));
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

		/* itr erase */
		void erase(iterator position)
		{
			_tree.erase(position.get_ptr());
		}

		/* value erase */
		// size_type erase(const key_type& k)
		// {

		// }

		/* range erase */
		void erase(iterator first, iterator last)
		{
			for (; first != last; first++)
				this->_tree.erase(first.get_ptr());
		}

		void swap(map& x)
		{
			ft::value_swap(this->_tree, x._tree);
		}

		void clear()
		{
			this->_tree.clear();
		}
	
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
