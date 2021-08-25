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

# include <sfinae.hpp>

namespace ft
{
////////////////////////////
// true type / false type //
////////////////////////////

	template <class T, T v>
		struct integral_constant {
			static const T value = v;
		};

	template <bool B>
		struct bool_constant : integral_constant<bool, B>{};

		struct true_type : bool_constant<true>{};
		struct false_type : bool_constant<false>{};

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
	template <class T>
		struct is_input_iterator;
	
	template <class Iter, bool>
		struct iterator_traits_impl {};

	template < class Iter >
		struct iterator_traits_impl < Iter, true >
	{
		typedef typename  Iter::value_type			value_type;
		typedef typename  Iter::difference_type		difference_type;
		typedef typename  Iter::pointer				pointer;
		typedef typename  Iter::reference			reference;
		typedef typename  Iter::iterator_category	iterator_category;

		// iterator_traits(typename ft::enable_if< ft::is_input_iterator<Iter>::value, Iter >::type = 0){}
	};

	template <class Iter, bool>
		struct iterator_traits {};

	template < class Iter >
		struct ft::iterator_traits< Iter, true > : iterator_traits_impl
			< Iter, std::is_convertible < typename Iter::iterator_category, input_iterator_tag>::value >
		{};

	/* pointer specialisation */
	template < class T>
		struct iterator_traits<T*>
	{
		typedef T							value_type;
		typedef std::ptrdiff_t				difference_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	/* const pointer specialisation */
	template < class T>
		struct iterator_traits<const T*>
	{
		typedef T							value_type;
		typedef std::ptrdiff_t				difference_type;
		typedef const T*					pointer;
		typedef const T&					reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template < class Itr>

///////////////////////////
// has iterator category //
///////////////////////////

	template <class T>
		struct has_iterator_category
	{
	private:
		template < class U >
			static int test(...);

		template < class U >
			static char test(typename U::iterator_category* = 0);

	public:
		static const bool value = sizeof(test<T>(0)) == 1;
	};

	template < class T, class U, bool = ft::has_iterator_category< ft::iterator_traits<T> >::value>
		struct has_iterator_category_convertible_to
			: public ft::integral_constant< bool, std::is_convertible<
				typename ft::iterator_traits<T>::iterator_category, U>::value>
	{};

	template <class T, class U>
		struct has_iterator_category_convertible_to<T, U, false> : public ft::false_type {};

/////////////////
// is iterator //
/////////////////

	template <class T>
		struct is_input_iterator : public has_iterator_category_convertible_to<T, input_iterator_tag> {};

	template <class T>
		struct is_forward_iterator : public has_iterator_category_convertible_to<T, forward_iterator_tag> {};

	template <class T>
		struct is_bidirectional_iterator : public has_iterator_category_convertible_to<T, bidirectional_iterator_tag> {};

	template <class T>
		struct is_random_access_iterator : public has_iterator_category_convertible_to<T, random_access_iterator_tag> {};

}

#endif
