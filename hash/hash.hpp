/* ************************************************************************** */
/*                                                                            */
/*                    (`-').-> (`-')  _  (`-').-> (`-').->                    */
/*                    (OO )__  (OO ).-/  ( OO)_   (OO )__                     */
/*                   ,--. ,'-' / ,---.  (_)--\_) ,--. ,'-'                    */
/*                   |  | |  | | \ /`.\ /    _ / |  | |  |                    */
/*                   |  `-'  | '-'|_.' |\_..`--. |  `-'  |                    */
/*                   |  .-.  |(|  .-.  |.-._)   \|  .-.  |                    */
/*                   |  | |  | |  | |  |\       /|  | |  |                    */
/*                   `--' `--' `--' `--' `-----' `--' `--'                    */
/*                                                                            */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOT_THE_KIND_OF_HASH_YOU_THINK_IT_IS_HPP
# define NOT_THE_KIND_OF_HASH_YOU_THINK_IT_IS_HPP

# include <cstddef>
# include <is_integral.hpp>
# include <string>
# include <sfinae.hpp>

namespace ft
{

///////////////////////////////////
// Hash function based on murmur //
///////////////////////////////////

	template < class T >
		std::size_t funky_hash(T* key, int len, unsigned int seed = 1337)
	{
		const std::size_t	multiplier	= 420 * 69 * (unsigned int)80085;
		const std::size_t	rotate		= 21;
		std::size_t			hash		= seed;
		const unsigned char *data		= (const unsigned char *)key;
		unsigned int		byte		= *((unsigned int *)data);

		while (len >= 4)
		{
			byte = *((unsigned int *)data);

			byte *= multiplier;
			byte ^= byte >> rotate;
			byte *= multiplier;

			hash ^= multiplier;
			hash ^= byte;

			data += 4;
			len -= 4;
		}

		switch (len)
		{
			case 3: hash ^= data[2] << 16;
			case 2: hash ^= data[1] << 8;
			case 1: hash ^= data[0];
					hash *= multiplier;
		}

		hash ^= len;

		hash ^= (hash >> 16);
		hash *= multiplier;
		hash ^= (hash >> 13);
		hash *= multiplier;
		hash ^= (hash >> 16);

		return (hash);
	}

/////////////
// Default //
/////////////

	template < class T, bool >
		struct hash_impl
	{};

//////////////////////////////////
// integral type specialization //
//////////////////////////////////

	template < class T > 
		struct hash_impl< T, true >
	{
		typedef	T			argument_type;
		typedef std::size_t	result_type;

		result_type operator () (const argument_type& key)
		{
			return (result_type)key;
		}
	}; /* end of integral specialization */

/////////
// ugh //
/////////

	template < class T >
		struct hash : ft::hash_impl<T, ft::is_integral<T>::value>
	{};

///////////////////////////
// String specialization //
///////////////////////////

	template <>
		struct hash<std::string>
	{
	//////////////
	// typedefs //
	//////////////

		typedef	std::string	argument_type;
		typedef std::size_t	result_type;

		result_type operator () (argument_type& key)
		{
			return funky_hash(key.c_str(), key.length(), 42069);
		}

	}; /* end of string specialization */

////////////////////////////
// Pointer specialization //
////////////////////////////

	template< class T >
		struct hash<T*>
	{
	//////////////
	// typedefs //
	//////////////

		typedef	T			argument_type;
		typedef std::size_t	result_type;

		result_type operator () (argument_type* key)
		{
			// fix the length
			return funky_hash(key, sizeof(key));
		}

	}; /* end of pointer specialization */

} /* end of namespace */

#endif
