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

namespace ft
{
	template< class T, class Hash, class Equal, class Alloc >
		class linear_hash_map
	{

		#define HASH_CAP 1024

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

			pointer				_arr;
			hasher				_hash;
			key_equal			_equal;
			size_type			_lpr_limit; // limit for linear probing
			size_type			_capacity;
			allocator_type		_alloc;
			node_allocator_type	_node_alloc;

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

			//////////////////
			// Construction //
			//////////////////
	
				hash_node()
					: probe_depth(0)
				{}

				~hash_node()
				{}

				hash_node(const hash_node& x)
				{
					*this = x;
				}

				hash_node& operator = (const hash_node& x)
				{
					this->element		= x.element;
					this->probe_depth	= x.probe_depth;
					return *this;
				}

			///////////////
			// modifiers //
			///////////////

				void	create(const value_type& val)
				{
					_alloc.construct(&element, val);
				}

			//////////
			// swap //
			//////////

				void	swap(const hash_node& x)
				{
					ft::value_swap(this->element, x.element);
					ft::value_swap(this->probe_depth, x.probe_depth);
				}

			}; /* end of node */

		/////////////
		// CoPlIeN //
		/////////////
		public:

			/* default constructor */
			explicit unordered_map(	size_type n = 0,
									const hasher& hf = hasher(),
									const key_equal& eql = key_equal(),
									const allocator_type& alloc = allocator_type())
				: _arr(NULL), _hash(hf), _equal(eql), _lpr_limit(0), _capacity(HASH_CAP), _alloc(alloc), _node_alloc(node_allocator_type())
			{
				this->_initial_alloc();
			}
		
			/* empty constructor */
			explicit unordered_map (const allocator_type& alloc);
			
			/* range constructor */
			template <class InputIterator>
				unordered_map(InputIterator first, InputIterator last,
							size_type n = 0,
							const hasher& hf = hasher(),
							const key_equal& eql = key_equal(),
							const allocator_type& alloc = allocator_type());

			/* copy constructor */
			unordered_map(const unordered_map& ump);
			unordered_map(const unordered_map& ump, const allocator_type& alloc);

		//////////////////////////
		// Construction helpers //
		//////////////////////////
		private:

			void	_initial_alloc()
			{
				_arr = alloc.allocate(_capacity);
				if (n == 0)
					_lpr_limit = ft::log2pow2(_capacity);
			}


	}; /* end of linear_hash_map */

	# undef HASH_CAP

} /* end of namespace */

#endif
