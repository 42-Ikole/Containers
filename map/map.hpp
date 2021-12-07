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
# include <node_iterator.hpp>
# include <rotareti.hpp>

namespace ft
{

////////////
// MAPPIE //
////////////

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<Key, T> > >
		class map
	{

	///////////////
	// type defs //
	///////////////
	public:
			
		typedef Key																key_type;
		typedef T																mapped_type;
		typedef ft::pair<key_type, mapped_type>									value_type;
		typedef Compare															key_compare;
		typedef Alloc															allocator_type;
		typedef typename allocator_type::reference								reference;
		typedef typename allocator_type::const_reference						const_reference;
		typedef typename allocator_type::pointer								pointer;
		typedef typename allocator_type::const_pointer							const_pointer;
		typedef ft::rnb_tree<value_type, key_type, key_compare, allocator_type>	tree_type;
		typedef typename tree_type::node										node;
		typedef typename tree_type::difference_type								difference_type;
		typedef typename tree_type::size_type									size_type;

		/* iterators fkdjfkjdskfjdksjf */

		typedef ft::node_iterator< ft::bidirectional_iterator_tag, value_type, node >													iterator;
		typedef ft::node_iterator< ft::bidirectional_iterator_tag, value_type, node, difference_type, const_pointer, const_reference >	const_iterator;
		typedef ft::reverse_iterator< iterator >																						reverse_iterator;
		typedef ft::reverse_iterator< const_iterator >																					const_reverse_iterator;


	////////////////
	// ?????????? //
	////////////////
	private:

		class value_compare
		{   
			public:

				Compare comp;

				value_compare(Compare c = Compare()) : comp(c) {}

				bool operator() (const value_type& x, const value_type& y) const
				{
					return comp(x.first, y.first);
				}
		}; /* end of ?????? */

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
	
	//////////////////////
	// Helper functions //
	//////////////////////
	private:

		node*	_lower_bound(const key_type& k) const
		{
			const_iterator ret = this->find(k);

			if (ret != this->end())
				return (ret.get_ptr());
			ret = this->begin();
			while (ret != this->end() && _tree.comp(k, (*ret).first) == false)
				++ret;
			return (ret.get_ptr());
		}

		node*	_upper_bound(const key_type& k) const
		{
			const_iterator ret;
			for (ret = this->begin(); ret != this->end(); ++ret) {
				if (_tree.comp(k, (*ret).first) == true) {
					if (_tree.comp((*ret).first, k) == true)
						continue ;
					break ;
				}
			}
			return (ret.get_ptr());
		}

	//////////////////
	// Iterators 🤮 //
	//////////////////
	public:

		iterator begin() 
		{
			return (iterator(_tree.begin->parent));
		}

		const_iterator begin() const
		{
			return (iterator(_tree.begin->parent));
		}

		iterator end()
		{
			return (iterator(_tree.end));
		}

		const_iterator end() const
		{
			return (iterator(_tree.end));
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(_tree.end));
		}

		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(_tree.end));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(_tree.begin));
		}

		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(_tree.begin));
		}

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
			return (_tree.size);
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
		ft::pair<iterator, bool> insert(const value_type& val)
		{
			ft::pair<node*, bool> inserted = _tree.insert(val);
			return (ft::make_pair(iterator(inserted.first), inserted.second));
		}

		/* with hint */
		iterator insert(iterator position, const value_type& val)
		{
			(void)position;
			return (this->insert(val).first);
		}
	
		/* range */
		template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
		{
			for (; first != last; ++first)
				this->insert(first);
		}

		/* itr erase */
		void erase(iterator position)
		{
			_tree.erase(position.get_ptr());
		}

		/* value erase */
		size_type erase(const key_type& k)
		{
			node* x = _tree.find(k);

			if (x == _tree.end)
				return (0);
			_tree.erase(x);
			return (1);
		}

		/* range erase */
		void erase(iterator first, iterator last)
		{
			while (first != last)
				this->erase(first++);
		}

		void swap(map& x)
		{
			this->_tree.swap(x._tree);
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

		value_compare value_comp() const
		{
			return (value_compare());
		}
	
	////////////////
	// Operations //
	////////////////
	public:

		iterator find(const key_type& k)
		{
			return (iterator(_tree.find(k)));
		}

		const_iterator find(const key_type& k) const
		{
			return (const_iterator(_tree.find(k)));
		}

		size_type count(const key_type& k) const
		{
			if (_tree.find(k) == _tree.end)
				return (false);
			return (true);
		}

		iterator lower_bound(const key_type& k)
		{
			return (iterator(_lower_bound(k)));
		}

		const_iterator lower_bound(const key_type& k) const
		{
			return (const_iterator(_lower_bound(k)));
		}

		iterator upper_bound(const key_type& k)
		{
			return (iterator(_upper_bound(k)));
		}

		const_iterator upper_bound(const key_type& k) const
		{
			return (const_iterator(_upper_bound(k)));
		}

		ft::pair<iterator, iterator> equal_range(const key_type& k)
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

	///////////////
	// ALLOCATOR //
	///////////////
	public:

		allocator_type	get_allocator() const
		{
			return (_tree.alloc);
		}

	////////////////
	// Bleh frens //
	////////////////
	public:

		friend bool operator == (const map& lhs, const map& rhs);
		friend bool operator != (const map& lhs, const map& rhs);
		friend bool operator  < (const map& lhs, const map& rhs);
		friend bool operator <= (const map& lhs, const map& rhs);
		friend bool operator  > (const map& lhs, const map& rhs);
		friend bool operator >= (const map& lhs, const map& rhs);

	}; /* end of map */

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
		return (lhs._tree == rhs._tree);
	}

	template< class Key, class T, class Compare, class Alloc >
		bool operator != (const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {
		return (lhs._tree != rhs._tree);
	}

	template< class Key, class T, class Compare, class Alloc >
		bool operator  < (const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {
		return (lhs._tree < rhs._tree);
	}

	template< class Key, class T, class Compare, class Alloc >
		bool operator <= ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {
			return (lhs._tree <= rhs._tree);
	}

	template< class Key, class T, class Compare, class Alloc >
		bool operator  > (const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {
			return (lhs._tree > rhs._tree);
	}

	template< class Key, class T, class Compare, class Alloc >
		bool operator >= (const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {
			return (lhs._tree >= rhs._tree);
	}

} /* end of namespace */

#endif
