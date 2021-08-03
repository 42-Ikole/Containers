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

#ifndef REVERSE_HPP
# define REVERSE_HPP

# include <traits.hpp>

namespace ft
{
	template <class Iter>
		class reverse_iterator
	{
	//////////////////////
	// Reverse Iterator //
	//////////////////////
		typedef typename  Iter::value_type			value_type;
		typedef typename  Iter::difference_type		difference_type;
		typedef typename  Iter::pointer				pointer;
		typedef typename  Iter::reference			reference;
		typedef typename  Iter::iterator_category	iterator_category;

	//////////////////////
	// Member variables //
	//////////////////////
	protected:
		Iter _base;

	//////////////////
	// Construction //
	//////////////////
	public:

		reverse_iterator(Iter base = NULL) : _base(base) {}

		template< class U >
			reverse_iterator( const reverse_iterator<U>& x ) {
			*this = x;
		}
	
	/////////////////////////////
	// common member functions //
	/////////////////////////////
	private:

		iterator_category base() const {
			return (this->_base);
		}

	///////////////////////////////
	// common operator overloads //
	///////////////////////////////
		template< class U >
			reverse_iterator&	operator = ( const reverse_iterator<U>& x ) {
			this->_base = x._base;
		}

		reverse_iterator&		operator ++ (/* prefix */) {
			_base--;
			return (*this);
		}

		reverse_iterator&		operator ++ (int /* postfix */) {
			reverse_iterator tmp = *this;
			++(*this);
			return (*tmp);
		}

		bool		operator == (const reverse_iterator& x) {
			return (this->_base == x._base);			
		}

		bool		operator != (const reverse_iterator& x) {
			return (this->_base != x._base);
		}
	
		reference	operator * () {
			return *(this->_ptr);
		}

		pointer		operator -> () {
			return (this->_ptr);
		}
	
	};
}

#endif
