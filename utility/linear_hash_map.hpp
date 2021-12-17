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

namespace ft
{

//////////////////////////////////
// Primbe bs for static reasons //
//////////////////////////////////

	struct prime_bs
	{
		typedef const std::size_t	prime_type;

		static prime_type primes[];
	};

/////////////////////
// Linear hash map //
/////////////////////

	template< class T, class Hash, class Equal, class Alloc >
		class linear_hash_map : prime_bs
	{

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
			
		//////////////////////
		// Member variables //
		//////////////////////
		protected:

			pointer						_arr;
			hasher						_hash;
			key_equal					_equal;
			size_type					_lpr_limit; // limit for linear probing
			size_type					_capacity;
			allocator_type				_alloc;
			node_allocator_type			_node_alloc;

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
	
				pointer			element;
				unsigned int	probe_depth;

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
				: _arr(NULL), _hash(hf), _equal(eql), _lpr_limit(0), _capacity(0), _alloc(alloc), _node_alloc(node_allocator_type())
			{
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

		//////////////////////////
		// Construction helpers //
		//////////////////////////
		private:

			std::size_t _get_next_prime(void)
			{
				static unsigned int idx = 0;

				if (primes[idx + 1] == 0)
					return (primes[idx]);
				return (primes[idx++]);
			}

			void	_initial_alloc()
			{
				// _arr = alloc.allocate(_capacity);
				// if (n == 0)
				// 	_lpr_limit = ft::log2pow2(_capacity);
			}


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
