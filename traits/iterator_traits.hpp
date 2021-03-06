/* ************************************************************************** */
/*                                                                            */
/*           _____    ____        _                  _____   ____             */
/*          |_ " _|U |  _"\ u U  /"\  u     ___     |_ " _| / __"| u          */
/*            | |   \| |_) |/  \/ _ \/     |_"_|      | |  <\___ \/           */
/*           /| |\   |  _ <    / ___ \      | |      /| |\  u___) |           */
/*          u |_|U   |_| \_\  /_/   \_\   U/| |\u   u |_|U  |____/>>          */
/*          _// \\_  //   \\_  \\    >>.-,_|___|_,-._// \\_  )(  (__)         */
/*         (__) (__)(__)  (__)(__)  (__)\_)-' '-(_/(__) (__)(__)              */
/*                                                                            */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

# include <type_traits.hpp>

namespace ft
{
///////////////////////////
// Has iterator typedefs //
///////////////////////////

	template < class T >
		struct has_iterator_typedefs
	{
		private:
	
			template < class U >
				static int test(...);

			template < class U >
				static char test(
					typename ft::make_type<typename U::value_type>::type*,
					typename ft::make_type<typename U::difference_type>::type*,
					typename ft::make_type<typename U::pointer>::type*,
					typename ft::make_type<typename U::reference>::type*,
					typename ft::make_type<typename U::iterator_category>::type*
				);

		public:
			static const bool value = (sizeof(test<T>(0,0,0,0,0)) == sizeof(char));
	};

//////////
// Tags //
//////////

	struct input_iterator_tag												{};
	struct forward_iterator_tag 		: ft::input_iterator_tag			{};
	struct bidirectional_iterator_tag	: ft::forward_iterator_tag			{};
	struct random_access_iterator_tag	: ft::bidirectional_iterator_tag	{};

/////////////////////
// Iterator traits //
/////////////////////
	
	template <class Iter, bool>
		struct iterator_traits_impl {};

	template < class Iter >
		struct iterator_traits_impl < Iter, true >
	{
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::const_iter			const_iterator;
	};

	template <class Iter>
		struct iterator_traits
			: ft::iterator_traits_impl < Iter, ft::has_iterator_typedefs<Iter>::value >
		{};

	/* pointer specialisation */
	template < class T >
		struct iterator_traits<T*>
	{
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef ft::random_access_iterator_tag	iterator_category;
		typedef const T*						const_iterator;
	};

	/* const pointer specialisation */
	template < class T >
		struct iterator_traits<const T*>
	{
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef ft::random_access_iterator_tag	iterator_category;
		typedef const T*						const_iterator;
	};

///////////////////////////
// has iterator category //
///////////////////////////

	template < class T >
		struct has_iterator_category
	{
	private:
		template < class U >
			static int test(...);

		template < class U >
			static char test(typename U::iterator_category*);

	public:
		static const bool value = sizeof(test<T>(0)) == sizeof(char);
	};

	template < class T, class U, bool = ft::has_iterator_category< ft::iterator_traits<T> >::value>
		struct has_iterator_category_convertible_to
			: public ft::integral_constant
				< 
					bool, 
					std::is_convertible<typename ft::iterator_traits<T>::iterator_category, U>::value
				>
		{};

	template <class T, class U>
		struct has_iterator_category_convertible_to<T, U, false> 
			: public ft::false_type
		{};

/////////////////
// is iterator //
/////////////////

	template < class T >
		struct is_input_iterator
			: public ft::has_iterator_category_convertible_to<T, ft::input_iterator_tag>
		{};

	template < class T >
		struct is_forward_iterator
			: public ft::has_iterator_category_convertible_to<T, ft::forward_iterator_tag>
		{};

	template < class T >
		struct is_bidirectional_iterator
			: public ft::has_iterator_category_convertible_to<T, ft::bidirectional_iterator_tag>
		{};

	template < class T >
		struct is_random_access_iterator
			: public ft::has_iterator_category_convertible_to<T, ft::random_access_iterator_tag>
		{};

} /* end of namespace */

#endif
