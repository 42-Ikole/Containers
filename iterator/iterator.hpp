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
/*                                                                            */
/* ************************************************************************** */

namespace ft {

/////////////////////////
// Iterator base class //
/////////////////////////

	# define itr	ft::iterator< Category, T, Distance, Pointer, Reference >

	template <class Category, class T, class Distance = std::ptrdiff_t,
          class Pointer = T*, class Reference = T&>
	struct iterator {
	//////////////
	// Typedefs //
	//////////////
	
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};

///////////////////////////////////
// Non member iterator functions //
///////////////////////////////////

	template<class Iter>
		typename iterator_traits<Iter>::difference_type
			distance (Iter first, Iter last)
	{
		typename iterator_traits<Iter>::difference_type dist = 0;

		while (first != last) {
			first++;
			dist++;
		}
		return (dist);
	}

	template <class Iter, class Distance>
		void advance (Iter& it, Distance n)
	{
		it += n;
	}

} /* end of namespace */
