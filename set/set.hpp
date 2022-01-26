/* ************************************************************************** */
/*                                                                            */
/*        .----------------.  .----------------.  .----------------.          */
/*        | .--------------. || .--------------. || .--------------. |        */
/*        | |    _______   | || |  _________   | || |  _________   | |        */
/*        | |   /  ___  |  | || | |_   ___  |  | || | |  _   _  |  | |        */
/*        | |  |  (__ \_|  | || |   | |_  \_|  | || | |_/ | | \_|  | |        */
/*        | |   '.___`-.   | || |   |  _|  _   | || |     | |      | |        */
/*        | |  |`\____) |  | || |  _| |___/ |  | || |    _| |_     | |        */
/*        | |  |_______.'  | || | |_________|  | || |   |_____|    | |        */
/*        | |              | || |              | || |              | |        */
/*        | '--------------' || '--------------' || '--------------' |        */
/*         '----------------'  '----------------'  '----------------'         */
/*																			  */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_CLASS_THAT_IS_COMPLETELY_DIFFERENT_FROM_MY_MAP
# define SET_CLASS_THAT_IS_COMPLETELY_DIFFERENT_FROM_MY_MAP

# include <memory>
# include <pair.hpp>
# include <rnb_tree.hpp>
# include <utility.hpp>
# include <node_iterator.hpp>
# include <iterator_traits.hpp>
# include <rotareti.hpp>

namespace ft
{

/////////
// SET //
/////////

	template < class T,  class Compare = std::less<T>, class Alloc = std::allocator<T> >
		class set
	{

	///////////////
	// type defs //
	///////////////
	public:

		typedef T														value_type;
		typedef Compare													key_compare;
		typedef key_compare												value_compare;
		typedef Alloc													allocator_type;
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;
		typedef ft::rnb_tree<value_type, value_compare, allocator_type>	tree_type;
		typedef typename tree_type::node								node;
		typedef typename tree_type::difference_type						difference_type;
		typedef typename tree_type::size_type							size_type;

		/* Bitchterators */
		typedef ft::node_iterator< ft::bidirectional_iterator_tag, value_type, node >													iterator;
		typedef ft::node_iterator< ft::bidirectional_iterator_tag, value_type, node, difference_type, const_pointer, const_reference >	const_iterator;
		typedef ft::reverse_iterator< iterator >																						reverse_iterator;
		typedef ft::reverse_iterator< const_iterator >																					const_reverse_iterator;

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
		explicit set (const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type())
				: _tree(tree_type(comp, alloc))
		{
		}

		/* range constructor */
		template <class InputIterator>
			set (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
					: _tree(tree_type(comp, alloc))
		{
			for (; first != last; first++)
				_tree.insert(*first);
		}

		~set()
		{
			this->clear();
		}

		set (const set& x)
		{
			*this = x;
		}

		set& operator = (const set &x)
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
			return (reverse_iterator(--(this->end())));
		}

		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(--(this->end())));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(--(this->begin())));
		}

		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(--(this->begin())));
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
			void insert(InputIterator first, InputIterator last,
				typename ft::iterator_traits<InputIterator>::iterator_category* = 0)
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
		size_type erase(const value_type& k)
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

		void swap(set& x)
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
			return (key_compare());
		}

		value_compare value_comp() const
		{
			return (key_compare());
		}
	
	////////////////
	// Operations //
	////////////////
	public:

		iterator find(const value_type& k)
		{
			return (iterator(_tree.find(k)));
		}

		const_iterator find(const value_type& k) const
		{
			return (const_iterator(_tree.find(k)));
		}

		size_type count(const value_type& k) const
		{
			if (_tree.find(k) == _tree.end)
				return (false);
			return (true);
		}

		iterator lower_bound(const value_type& k)
		{
			return (iterator(_tree.lower_bound(k)));
		}

		const_iterator lower_bound(const value_type& k) const
		{
			return (const_iterator(_tree.lower_bound(k)));
		}

		iterator upper_bound(const value_type& k)
		{
			return (iterator(_tree.upper_bound(k)));
		}

		const_iterator upper_bound(const value_type& k) const
		{
			return (const_iterator(_tree.upper_bound(k)));
		}

		ft::pair<iterator, iterator> equal_range(const value_type& k)
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		ft::pair<const_iterator, const_iterator> equal_range(const value_type& k) const
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

		friend bool operator == (const set& lhs, const set& rhs);
		friend bool operator != (const set& lhs, const set& rhs);
		friend bool operator  < (const set& lhs, const set& rhs);
		friend bool operator <= (const set& lhs, const set& rhs);
		friend bool operator  > (const set& lhs, const set& rhs);
		friend bool operator >= (const set& lhs, const set& rhs);

	}; /* end of set */

///////////////
// Swapfiets //
///////////////

	template< class T, class Compare, class Alloc >
		void swap(ft::set<T,Compare,Alloc>& lhs, ft::set<T,Compare,Alloc>& rhs)
	{
		lhs.swap(rhs);
	}

//////////////////////////
// CoMpArIsOn oPeRaToRs //
//////////////////////////

	template< class T, class Compare, class Alloc >
		bool operator == (const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs) {
		return (lhs._tree == rhs._tree);
	}

	template< class T, class Compare, class Alloc >
		bool operator != (const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs) {
		return (lhs._tree != rhs._tree);
	}

	template< class T, class Compare, class Alloc >
		bool operator  < (const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs) {
		return (lhs._tree < rhs._tree);
	}

	template< class T, class Compare, class Alloc >
		bool operator <= ( const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs) {
			return (lhs._tree <= rhs._tree);
	}

	template< class T, class Compare, class Alloc >
		bool operator  > (const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs) {
			return (lhs._tree > rhs._tree);
	}

	template< class T, class Compare, class Alloc >
		bool operator >= (const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs) {
			return (lhs._tree >= rhs._tree);
	}

} /* end of namespace */

#endif
