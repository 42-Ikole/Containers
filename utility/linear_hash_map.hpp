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
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef	std::ptrdiff_t								difference_type;
			typedef	std::size_t									size_type;
			typedef std::allocator<hash_node>					node_allocator_type;
			typedef std::allocator<size_type>					idx_allocator_type;
			
		//////////////////////
		// Member variables //
		//////////////////////
		protected:

			hash_node**			_indices;
			hash_node*			_arr;
			hasher				_hash;
			key_equal			_equal;
			size_type			_capacity;
			size_type			_size;
			size_type			_maximum_load_factor;
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
				: _indices(NULL), _arr(NULL), _hash(hf), _equal(eql), _capacity(0), _size(0),
					_alloc(alloc), _node_alloc(node_allocator_type(), _idx_alloc(idx_allocator_type()), _spec_mod(NULL))
			{
				(void)n;
				this->_initial_alloc();
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
				return (primes[i]);
			}

			/* sets spec_mod and maximum_load_factor */
			std::size_t _get_next_prime()
			{
				static unsigned int idx = 0;

				if (primes[idx + 1] == 0)
					return (primes[idx]);
				_spec_mod				= spec_mod[idx];
				_maximum_load_factor	= ft::log2pow2(primes[idx]);
				return (primes[idx++]);
			}

			void	_allocate_array()
			{
				_arr		= _node_alloc(_capacity);
				_indices	= _idx_alloc(_capacity);
				for (size_type i = 0; i < _capacity; ++i)
					_indices[i] = NULL;
			}

			void	_increase_limits()
			{
				_capacity	= _get_next_prime();
			}

		///////////////
		// ITERATORS //
		///////////////
		public:

			iterator				begin() {
				return (iterator(this->_arr));
			}

			const_iterator			begin() const {
				return (const_iterator(this->_arr));
			}

			iterator				end() {
				return (iterator(&this->_arr[this->_size]));
			}

			const_iterator			end() const {
				return (const_iterator(&this->_arr[this->_size]));
			}

			reverse_iterator		rbegin() {
				return (reverse_iterator(&this->_arr[this->_size]));
			}

			const_reverse_iterator	rbegin() const {
				return (const_reverse_iterator(&this->_arr[this->_size]));
			}

			reverse_iterator		rend() {
				return (reverse_iterator(this->_arr));
			}

			const_reverse_iterator	rend() const {
				return (const_reverse_iterator(this->_arr));
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
				for (size_type i = _size - 1; i > 0; --i)
					_alloc.destroy(&arr[i].element);

				_node_alloc.deallocate(_arr, _capacity);
				_arr = NULL;
				_idx_alloc.deallcoate(_indices, _capacity);
				_indices = NULL;
				_size					= 0;
				_capacity				= 0;
				_maximum_load_factor	= 0;
			}

			/* single element insert */
			ft::pair<iterator, bool> insert(const value_type& value)
			{
				if (_size + 1 == _capacity)
					this->_realloc();

				size_type hash_code	= _hash(value); /* for potential optimization purposes */
				size_type idx		= hash_code % _capacity;
				hash_node* cur		= _indices[idx];
				size_type depth		= 0;

				while (cur != NULL) {

					if (_equal(cur.element, value) == True)
						return (ft::make_pair(iterator(cur), false));
					cur = cur->next;
					++depth;
					if (depth >= _maximum_load_factor)
						// klop nog niet helemaal
						this->realloc();
						break ;
				}

				_alloc.construct(&_arr[_size].element, value);
				_arr[_size].next = NULL;

				if (_indices[idx] == NULL)
					_indices[idx] = _arr[_size];
				else
					cur->next = _arr[_size]
				++_size;
				return (ft::make_pair(iterator(&_arr[_size - 1], true)));
			}

			/* you already know this hint is going to be voided */
			iterator insert( const_iterator hint, const value_type& value );

			/* range insert */
			template< class InputIt >
				void insert(InputIt first, InputIt last);

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
