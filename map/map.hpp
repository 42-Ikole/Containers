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

namespace ft
{

////////////
// MAPPIE //
////////////

	template <	class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
		class map
	{
	///////////////
	// type defs //
	///////////////
		public:
				
			typedef Key										key_type;
			typedef T										mapped_type;
			typedef ft::pair<const key_type, mapped_type>	value_type;
			typedef Compare									key_compare;
			typedef Alloc									allocator_type;
			typedef allocator_type::reference				reference;
			typedef allocator_type::const_reference			const_reference;
			typedef allocator_type::pointer					pointer;
			typedef allocator_type::const_pointer			const_pointer;
			typedef	std::ptrdiff_t							difference_type;
			typedef	std::size_t								size_type;

			/* iterators fkdjfkjdskfjdksjf */


	/////////////
	// CoPlIeN //
	/////////////
		explicit map (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type())
		{

		}

		template <class InputIterator>
			map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
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

	}; /* end of map */

} /* end of namespace */

#endif
