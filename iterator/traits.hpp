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


	// ////////////////////
	// // Input iterator //
	// ////////////////////

	// template< class T >
	// struct is_input_iterator {
	// 	static const bool value = false;
	// };

	// template<>
	// struct is_input_iterator<input_iterator_tag> {
	// 	static const bool value = true;
	// };

	// //////////////////////
	// // forward iterator //
	// //////////////////////

	// template< class T >
	// struct is_forward_iterator {
	// 	static const bool value = false;
	// };

	// template<>
	// struct is_forward_iterator<forward_iterator_tag> {
	// 	static const bool value = true;
	// };

	// ////////////////////////////
	// // bidirectional iterator //
	// ////////////////////////////

	// template< class T >
	// struct is_bidirectional_iterator {
	// 	static const bool value = false;
	// };

	// template<>
	// struct is_bidirectional_iterator<bidirectional_iterator_tag> {
	// 	static const bool value = true;
	// };

	// ////////////////////////////
	// // random access iterator //
	// ////////////////////////////

	// template< class T >
	// struct is_random_access_iterator {
	// 	static const bool value = false;
	// };

	// template<>
	// struct is_random_access_iterator<random_access_iterator_tag> {
	// 	static const bool value = true;
	// };


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

	template< class T >
		struct iterator_traits<T*>;

	template< class T >
		struct iterator_traits<const T*>;

///////////////////////////
// has iterator category //
///////////////////////////

	/* what the actual fuck is this magic spell?!?! */
	template <class Tp>
		struct has_iterator_category
	{
	private:
		struct two {char lx; char lxx;};
		template <class Up> static two test(...);
		template <class Up> static char test(typename Up::iterator_category* = 0);
	public:
		static const bool value = sizeof(test<Tp>(0)) == 1;
	};

	template <class Tp, class Up, bool = has_iterator_category<iterator_traits<Tp> >::value>
		struct has_iterator_category_convertible_to
			: public std::integral_constant<bool, std::is_convertible<typename iterator_traits<Tp>::iterator_category, Up>::value>
	{};

	template <class Tp, class Up>
		struct has_iterator_category_convertible_to<Tp, Up, false> : public false_type {};

/////////////////
// is iterator //
/////////////////

	template <class Tp>
		struct is_input_iterator : public has_iterator_category_convertible_to<Tp, input_iterator_tag> {};

	template <class Tp>
		struct is_forward_iterator : public has_iterator_category_convertible_to<Tp, forward_iterator_tag> {};

	template <class Tp>
		struct is_bidirectional_iterator : public has_iterator_category_convertible_to<Tp, bidirectional_iterator_tag> {};

	template <class Tp>
		struct is_random_access_iterator : public has_iterator_category_convertible_to<Tp, random_access_iterator_tag> {};

}

#endif
