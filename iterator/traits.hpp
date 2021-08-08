/* ************************************************************************** */
/*                                                                            */
/*  @@@  @@@@@@@  @@@@@@@@  @@@@@@@    @@@@@@   @@@@@@@   @@@@@@   @@@@@@@    */
/*  @@@  @@@@@@@  @@@@@@@@  @@@@@@@@  @@@@@@@@  @@@@@@@  @@@@@@@@  @@@@@@@@   */
/*  @@!    @@!    @@!       @@!  @@@  @@!  @@@    @@!    @@!  @@@  @@!  @@@   */
/*  !@!    !@!    !@!       !@!  @!@  !@!  @!@    !@!    !@!  @!@  !@!  @!@   */
/*  !!@    @!!    @!!!:!    @!@!!@!   @!@!@!@!    @!!    @!@  !@!  @!@!!@!    */
/*  !!!    !!!    !!!!!:    !!@!@!    !!!@!!!!    !!!    !@!  !!!  !!@!@!     */
/*  !!:    !!:    !!:       !!: :!!   !!:  !!!    !!:    !!:  !!!  !!: :!!    */
/*  :!:    :!:    :!:       :!:  !:!  :!:  !:!    :!:    :!:  !:!  :!:  !:!   */
/*   ::     ::     :: ::::  ::   :::  ::   :::     ::    ::::: ::  ::   :::   */
/*  :       :     : :: ::    :   : :   :   : :     :      : :  :    :   : :   */
/*																			  */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*																			  */
/* ************************************************************************** */

#ifndef TRAITS_HPP
# define TRAITS_HPP

namespace ft
{

//////////
// Tags //
//////////
	struct input_iterator_tag										{};
	struct forward_iterator_tag : input_iterator_tag				{};
	struct bidirectional_iterator_tag : forward_iterator_tag		{};
	struct random_access_iterator_tag : bidirectional_iterator_tag	{};

/////////////////////
// Iterator traits //
/////////////////////
	template< class Iter >
		struct iterator_traits
	{
		typedef typename  Iter::value_type			value_type;
		typedef typename  Iter::difference_type		difference_type;
		typedef typename  Iter::pointer				pointer;
		typedef typename  Iter::reference			reference;
		typedef typename  Iter::iterator_category	iterator_category;
	};

	/* pointer specialisation */
	template< class T >
		struct iterator_traits<T*>
	{
		typedef T							value_type;
		typedef std::ptrdiff_t				difference_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	/* const pointer specialisation */
	template< class T >
		struct iterator_traits<const T*>
	{
		typedef T							value_type;
		typedef std::ptrdiff_t				difference_type;
		typedef const T*					pointer;
		typedef const T&					reference;
		typedef random_access_iterator_tag	iterator_category;
	};

}

#endif
