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
/*                                                                            */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_ITERATOR_HPP
# define FT_MAP_ITERATOR_HPP

# include <cstddef>
# include <iterator.hpp>
# include <traits.hpp>

namespace ft
{


////////////////////////
// Map Iterator Class //
////////////////////////
	# define itr	ft::iterator< Category, T, Distance, Pointer, Reference >

	template < class T, class Category = ft::bidirectional_iterator_tag,
		class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	class map_iterator : public ft::iterator < Category, T, Distance, Pointer, Reference >
	{

	//////////////
	// Typedefs //
	//////////////
	private:

		typedef ft::map_iterator< T, Category, Distance, T*, T& >				iter;
		typedef ft::map_iterator< T, Category, Distance, const T*, const T& >	const_iter;
	
	public:

		typedef typename itr::value_type		value_type;
		typedef typename itr::difference_type	difference_type;
		typedef typename itr::pointer			pointer;
		typedef typename itr::reference			reference;
		typedef typename itr::iterator_category	iterator_category;


	//////////////////////
	// Member variables //
	//////////////////////
	protected:
		pointer	_ptr;

	/////////////////
	// constructor //
	/////////////////
	public:

		map_iterator(Pointer ptr = NULL) : _ptr(ptr) {}

		map_iterator(const map_iterator& x) {
			*this = x;
		}

		virtual ~map_iterator() {}

	//////////////////////
	// Common operators //
	//////////////////////
	public:

		map_iterator&	operator ++ (/* prefix */) {
			_ptr = _ptr->get_successor();
			return (*this);
		}

		map_iterator	operator ++ (int /* postfix */) {
			map_iterator tmp = *this;
			++(*this);
			return (tmp);
		}

		map_iterator&	operator  = (const map_iterator& x) {
			this->_ptr = x._ptr;
			return (*this);
		}

	//////////////////////////////
	// Input iterator operators //
	//////////////////////////////
	public:

		bool		operator == (const map_iterator& x) {
			return (this->_ptr == x._ptr);			
		}

		bool		operator != (const map_iterator& x) {
			return (this->_ptr != x._ptr);
		}
	
		reference	operator * () {
			return (_ptr->value);
		}

		pointer		operator -> () {
			return &(_ptr->value);
		}

	//////////////////////////////////////
	// Bidirectional iterator operators //
	//////////////////////////////////////
	public:
	
		map_iterator&	operator -- (/* prefix */) {
			_ptr = _ptr->get_predecessor();
			return (*this);
		}

		map_iterator	operator -- (int /* postfix */) {
			map_iterator tmp = *this;
			--(*this);
			return (tmp);
		}

	}; /* end of map_iterator */

} /* end of namespace */

#endif
