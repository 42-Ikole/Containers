/* ************************************************************************** */
/*                                                                            */
/*      .'(     /`-.     )\.--.       .'(        )\   )\     /`-.      /`-.   */
/*  ,') \  )  ,' _  \   (   ._.'  ,') \  )      (  ',/ /   ,' _  \   ,' _  \  */
/* (  '-' (  (  '-' (    `-.`.   (  '-' (        )    (   (  '-' (  (  '-' (  */
/*  ) .-.  )  )   _  )  ,_ (  \   ) .-.  )      (  \(\ \   )   _  )  ) ,._.'  */
/* (  ,  ) \ (  ,' ) \ (  '.)  ) (  ,  ) \       `.) /  ) (  ,' ) \ (  '      */
/*  )/    )/  )/    )/  '._,_.'   )/    )/           '.(   )/    )/  )/       */
/*                                                                            */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINEAR_HASH_MAP_ROBBIN_FROM_THE_HOOD_STYLE_HPP
# define LINEAR_HASH_MAP_ROBBIN_FROM_THE_HOOD_STYLE_HPP                                                                          

# include <hash.hpp>
# include <utility.hpp>
# include <memory>
# include <hash.hpp>
# include <iostream>
# include <utility.hpp>
# include <pair.hpp>
# include <deque.hpp>
# include <linear_hash_map_iterator.hpp>
# include <rotareti.hpp>

# include <iostream> //

namespace ft
{

//////////////////////////////////
// Primbe bs for static reasons //
//////////////////////////////////

	struct prime_bs
	{
		typedef const std::size_t					prime_type;
		typedef prime_type (*mod_type)(prime_type);

		static prime_type	primes[];
		static mod_type		spec_mod[];
	};

/////////////////////
// Linear hash map //
/////////////////////

	template< class T, class Hash, class Equal, class Alloc >
		class linear_hash_map : prime_bs
	{
	
		//////////////////////////
		// Forward declarations //
		//////////////////////////
		private:

			struct hash_node;

		///////////////
		// type defs //
		///////////////
		public:
			
			typedef T											value_type;
			typedef Hash										hasher;
			typedef Equal										key_equal;
			typedef Alloc										allocator_type;
			typedef ft::deque<T*>								stack_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef	std::ptrdiff_t								difference_type;
			typedef	std::size_t									size_type;
			typedef std::allocator<hash_node>					node_allocator_type;
			typedef std::allocator<hash_node*>					idx_allocator_type;


			/* iterators */

			typedef ft::linear_hash_map_iterator<value_type, hash_node>	iterator;
			typedef typename iterator::const_iter						const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
			
		//////////////////////
		// Member variables //
		//////////////////////
		protected:

		/*
			maak een stack met free pointers
		*/

			hash_node**			_indices;
			hash_node*			_arr;
			hash_node*			_last_empty;
			hasher				_hash;
			key_equal			_equal;
			size_type			_capacity;
			size_type			_size;
			size_type			_maximum_load_factor;
			stack_type			_mem_stack;
			allocator_type		_alloc;
			node_allocator_type	_node_alloc;
			idx_allocator_type	_idx_alloc;
			mod_type			_spec_mod;

		///////////
		// Node? //
		///////////
		private:

			/*
			** ToDo:
			** --------
			** Make a hash node specialization for string,
			** where you save the hash in order to make
			** resizing more efficient with the downside
			** of having 8 extra bytes overhead per node
			*/
			struct hash_node
			{

				///////////////
				// Variables //
				///////////////
				public:
		
					value_type	element;
					hash_node	*next;

			}; /* end of node */

		/////////////
		// CoPlIeN //
		/////////////
		public:

			/* default constructor */
			explicit linear_hash_map( size_type n = 0,
									const hasher& hf = hasher(),
									const key_equal& eql = key_equal(),
									const allocator_type& alloc = allocator_type())
				: _indices(NULL), _arr(NULL), _last_empty(NULL), _hash(hf), _equal(eql), _capacity(0), _size(0), _maximum_load_factor(0), _mem_stack(stack_type()),
					_alloc(alloc), _node_alloc(node_allocator_type()), _idx_alloc(idx_allocator_type()), _spec_mod(NULL)
			{
				(void)n;
			}
		
			/* empty constructor */
			explicit linear_hash_map (const allocator_type& alloc);
			
			/* range constructor */
			template <class InputIterator>
				linear_hash_map(InputIterator first, InputIterator last,
							size_type n = 0,
							const hasher& hf = hasher(),
							const key_equal& eql = key_equal(),
							const allocator_type& alloc = allocator_type());

			/* copy constructor */
			linear_hash_map(const linear_hash_map& ump);
			linear_hash_map(const linear_hash_map& ump, const allocator_type& alloc);

			/* destructor */
			virtual ~linear_hash_map()
			{
				this->clear();
			}

			linear_hash_map& operator = (const linear_hash_map& x)
			{
				this->_indices				= 	x._indices;
				this->_arr					= 	x._arr;
				this->_hash					= 	x._hash;
				this->_equal				= 	x._equal;
				this->_capacity				= 	x._capacity;
				this->_size					= 	x._size;
				this->_maximum_load_factor	= 	x._maximum_load_factor;
				this->_alloc				= 	x._alloc;
				this->_node_alloc			= 	x._node_alloc;
				this->_idx_alloc			= 	x._idx_alloc;
				this->_spec_mod				= 	x._spec_mod;
			}

		//////////////////////////
		// Construction helpers //
		//////////////////////////
		private:

			size_type	_get_closest_prime(size_type n)
			{
				size_type i = 0;

				while (n < primes[i] && primes[i + 1] != 0)
					++i;
				return (i);
			}

			/* sets spec_mod and maximum_load_factor */
			void _increase_limits(const unsigned int idx)
			{

				if (primes[idx + 1] == 0)
					return ;
				_spec_mod				= spec_mod[idx];
				_maximum_load_factor	= ft::log2pow2(primes[idx]);
				_capacity = primes[idx];
			}

			void	_set_limit(size_type n = 0)
			{
				static unsigned int idx = 0;
	
				if (n == (size_type)-1)
					idx = 0;
				else if (n != 0)
					idx = _get_closest_prime(n);
				else {
					_increase_limits(idx);
					++idx;
				}
			}

			void	_allocate_array()
			{
				_arr		= _node_alloc.allocate(_capacity);
				_last_empty = _arr;
				_indices	= _idx_alloc.allocate(_capacity);
				for (size_type i = 0; i < _capacity; ++i)
					_indices[i] = NULL;
			}

			ft::pair<iterator, bool>	_check_insert(hash_node* cur, const value_type& val)
			{
				unsigned int depth = 0;

				while (cur != NULL) {

					if (_equal(cur->element, val) == true)
						return (ft::make_pair(iterator(cur), false));
					cur = cur->next;
					++depth;
					if (depth >= _maximum_load_factor) {
						this->realloc();
						return (ft::make_pair(this->end(), false));
					}
				}
				return (ft::make_pair(cur, true));
			}

			hash_node*	_get_prev(const hash_node* x,
								 const size_type& idx) const
			{
				hash_node* cur		= _indices[idx];
				hash_node* prev		= NULL;

				while(cur != NULL)
				{
					if (_equal(cur, x) == true)
						return (prev);
					prev	= cur;
					cur		= cur->next;
				}
				return (NULL);
			}

			hash_node*	_get_mem_loc()
			{
				hash_node* loc = NULL;

				if (_mem_stack.empty() == false) {
					loc = _mem_stack.back();
					_mem_stack.pop_back();
				}
				else {
					loc = _last_empty();
					++_last_empty;
				}
				return (loc);
			}

			void	_realloc()
			{
				hash_node** old_indices	= _indices;
				hash_node*	old_arr		= _arr;
				const_iterator i		= this->begin();
				const_iterator old_end	= this->end();

				_set_limit();
				_allocate_array();

				if (old_indices == NULL)
					return ;

				while (i != old_end) {
					this->insert(i);
					_node_alloc.destroy(&(*i));
				}
				_node_alloc.deallocate(old_arr);
				_idx_alloc.deallocate(old_indices);
			}

		///////////////
		// ITERATORS //
		///////////////
		public:

			iterator				begin() {
				return (iterator(_indices));
			}

			const_iterator			begin() const {
				return (const_iterator(_indices));
			}

			iterator				end() {
				return (iterator(&_indices[_size]));
			}

			const_iterator			end() const {
				return (const_iterator(&_indices[_size]));
			}
	
		//////////////
		// CAPACITY //
		//////////////
		public:

			size_type	size() const
			{
				return (_size);
			}

			size_type	max_size() const
			{
				/* this is broken */
				return (_alloc.max_size());
			}

			bool		empty() const
			{
				return (_size == 0);
			}

		///////////////
		// Modifiers //
		///////////////
		public:

			void clear() throw()
			{
				if (_arr == NULL)
					return ;

				for (iterator i = this->begin(); i != this->end(); ++i)
					_alloc.destroy(&(*i));

				_node_alloc.deallocate(_arr, _capacity);
				_arr		= NULL;
				_last_empty	= NULL;
				_idx_alloc.deallocate(_indices, _capacity);
				_indices				= NULL;
				_size					= 0;
				_capacity				= 0;
				_maximum_load_factor	= 0;
				_set_limit((size_type)-1);
				_mem_stack.clear();
			}

			/* single element insert */
			ft::pair<iterator, bool> insert(const value_type& val)
			{
				/* not enough space */
				if (_size + 1 >= _capacity)
					this->_realloc();

				size_type					hash_code = _hash(val);
				size_type					idx;
				hash_node*					cur;
				ft::pair<iterator, bool>	prev;

				while (true)
				{
					idx		= _spec_mod(hash_code);
					prev	= _check_insert(_indices[idx], val);
					
					/* a reallocation happened, try again */
					if (prev.first == this->end())
						continue ;

					/* value already exists */
					if (prev.second == false)
						return (prev);

					/* insert new element after prev */
					break ;
				}

				hash_node* loc = _get_mem_loc();

				_alloc.construct(&loc->element, val);
				loc->next = NULL;

				if (_indices[idx] == NULL)
					_indices[idx] = loc;
				else
					prev->next = loc;
				++_size;
				return (ft::make_pair(iterator(loc, true)));
			}

			/* you already know this hint is going to be voided */
			iterator insert(const_iterator hint, const value_type& val)
			{
				(void)hint;
				return (this->insert(val).first);
			}

			/* range insert */
			template< class InputIt >
				void insert(InputIt first, InputIt last)
			{
				while (first != last)
				{
					this->insert(*first);
					++first;
				}
			}

		/* pretty sure i dont need this one */
			// iterator erase(iterator pos)
			// {
			// }

			/* element erase */
			iterator erase(const_iterator pos)
			{
				hash_node* cur		= pos.get_ptr();
				size_type hash_code = _hash(cur);
				size_type idx		= _spec_mod(hash_code);
				hash_node* prev		= _get_prev(cur, idx);

				_alloc.destroy(cur->element);
				if (cur == _indices[idx])
					_indices[idx] = cur->next;
				else if (prev != NULL)
					prev->next = cur->next;

				_mem_stack.push_back(cur);
				--_size;

				return (++pos);
			}

			/* range erase */
			iterator erase(const_iterator first, const_iterator last)
			{
				while (first != last)
					first = this->erase(first);
				return (++first);
			}

			// /* key erase */
			// size_type erase(const Key& key)
			// {
			// 	const_iterator pos = this->find(key);
				
			// 	if (pos == this->end())
			// 		return (0);
			// 	this->erase(pos);
			// 	return (1);
			// }

		///////////////////
		// Get allocator //
		///////////////////
		public:

			allocator_type& get_allocator()
			{
				return _alloc;
			}

	}; /* end of linear_hash_map */

} /* end of namespace */

#endif
