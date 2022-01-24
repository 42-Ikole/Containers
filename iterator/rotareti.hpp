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

#ifndef ROTARETI_HPP
# define ROTARETI_HPP

# include <iterator_traits.hpp>
# include <iterator>

namespace ft
{
	template <class Iter>
		class reverse_iterator
	{
	//////////////////////
	// Reverse Iterator //
	//////////////////////
	public:

		typedef Iter													iterator_type;
		typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iter>::value_type			value_type;
		typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iter>::pointer				pointer;
		typedef typename ft::iterator_traits<Iter>::reference			reference;
		typedef reverse_iterator<typename Iter::const_iter>				const_riter;

	//////////////////////
	// Member variables //
	//////////////////////
	protected:

		Iter _base;

	//////////////////
	// Construction //
	//////////////////
	public:

		reverse_iterator() {}

		reverse_iterator(Iter base) : _base(base) {}

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

	//////////////////////
	// common operators //
	//////////////////////
	public:

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

	//////////////////////////////
	// Input iterator operators //
	//////////////////////////////
	public:

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

	//////////////////////////////////////
	// Bidirectional iterator operators //
	//////////////////////////////////////
	public:

		reverse_iterator&		operator -- (/* prefix */) {
			_base++;
			return (*this);
		}

		reverse_iterator&		operator -- (int /* postfix */) {
			reverse_iterator tmp = *this;
			--(*this);
			return (*tmp);
		}

	///////////////////////////////////
	// implicit conversion operators //
	///////////////////////////////////
	public:
	
		operator const_riter () const
		{
			return (const_riter(_base));
		}
	
	}; /* end of reverse iterator */

} /* end of namespace */

#endif
