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
		typedef typename ft::iterator_traits<Iter>::const_iterator		const_iter;
		typedef reverse_iterator<const_iter>							const_riter;

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
			reverse_iterator(const reverse_iterator<U>& x) {
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

		reverse_iterator&	operator = (const reverse_iterator& x) {
			this->_base = x._base;
			return *(this);
		}

		reverse_iterator&		operator ++ (/* prefix */) {
			_base--;
			return (*this);
		}

		reverse_iterator		operator ++ (int /* postfix */) {
			reverse_iterator tmp = *this;
			++(*this);
			return (tmp);
		}

	//////////////////////////////
	// Input iterator operators //
	//////////////////////////////
	public:

		template< class Iterator1, class Iterator2 >
			friend bool operator  == (const reverse_iterator<Iterator1>& lhs,
							const reverse_iterator<Iterator2>& rhs);

		template< class Iterator1, class Iterator2 >
			friend bool operator  != (const reverse_iterator<Iterator1>& lhs,
							const reverse_iterator<Iterator2>& rhs);
	
		reference	operator * () {
			return *(_base);
		}

		pointer		operator -> () {
			return &(*(_base));
		}

	//////////////////////////////////////
	// Bidirectional iterator operators //
	//////////////////////////////////////
	public:

		reverse_iterator&		operator -- (/* prefix */) {
			_base++;
			return (*this);
		}

		reverse_iterator		operator -- (int /* postfix */) {
			reverse_iterator tmp = *this;
			--(*this);
			return (tmp);
		}

	//////////////////////////////////////
	// Random access iterator operators //
	//////////////////////////////////////
	public:

		reverse_iterator		operator  + (difference_type n) const {
			return (reverse_iterator(_base - n));
		}

		template< class It >
			friend reverse_iterator<It>
				operator  + (typename reverse_iterator<It>::difference_type n,
						const reverse_iterator<It>& it);

		reverse_iterator		operator  - (difference_type n) const {
			return (reverse_iterator(_base + n));
		}

		template< class It >
			friend typename reverse_iterator<It>::difference_type
				operator  - ( const reverse_iterator<It>& lhs,
						const reverse_iterator<It>& rhs );

		reverse_iterator&		operator += (difference_type n) {
			_base -= n;
			return (*this);
		}

		reverse_iterator&		operator -= (difference_type n) {
			_base += n;
			return (*this);
		}

		reference				operator [] (difference_type n) {
			return (_base[n]);
		}

		template< class Iterator1, class Iterator2 >
			friend bool operator  < (const ft::reverse_iterator<Iterator1>& lhs,
							const ft::reverse_iterator<Iterator2>& rhs);

		template< class Iterator1, class Iterator2 >
			friend bool operator  <= (const ft::reverse_iterator<Iterator1>& lhs,
							const ft::reverse_iterator<Iterator2>& rhs);

		template< class Iterator1, class Iterator2 >
			friend bool operator  > (const ft::reverse_iterator<Iterator1>& lhs,
							const ft::reverse_iterator<Iterator2>& rhs);
		
		template< class Iterator1, class Iterator2 >
			friend bool operator >= (const ft::reverse_iterator<Iterator1>& lhs,
							const ft::reverse_iterator<Iterator2>& rhs);
	

	///////////////////////////////////
	// implicit conversion operators //
	///////////////////////////////////
	public:
	
		operator const_riter () const
		{
			return (const_riter(_base));
		}
	
	}; /* end of reverse iterator */


///////////
// Frens //
///////////

	template< class It >
		ft::reverse_iterator<It> operator  +
			(typename ft::reverse_iterator<It>::difference_type n,
				const ft::reverse_iterator<It>& it)
	{
		return (it + n);
	}


	template< class It >
		typename ft::reverse_iterator<It>::difference_type
			operator  - ( const ft::reverse_iterator<It>& lhs,
				const ft::reverse_iterator<It>& rhs )
	{
		return (lhs._base - rhs._base);
	}

	template< class Iterator1, class Iterator2 >
		bool operator  == (const ft::reverse_iterator<Iterator1>& lhs,
						const ft::reverse_iterator<Iterator2>& rhs)
	{
		return (lhs._base == rhs._base);
	}

	template< class Iterator1, class Iterator2 >
		bool operator  != (const ft::reverse_iterator<Iterator1>& lhs,
						const ft::reverse_iterator<Iterator2>& rhs)
	{
		return (lhs._base != rhs._base);
	}

	template< class Iterator1, class Iterator2 >
		bool operator  < (const ft::reverse_iterator<Iterator1>& lhs,
						const ft::reverse_iterator<Iterator2>& rhs)
	{
		return (lhs._base < rhs._base);
	}

	template< class Iterator1, class Iterator2 >
		bool operator  <= (const ft::reverse_iterator<Iterator1>& lhs,
						const ft::reverse_iterator<Iterator2>& rhs)
	{
		return (lhs._base <= rhs._base);
	}

	template< class Iterator1, class Iterator2 >
		bool operator  > (const ft::reverse_iterator<Iterator1>& lhs,
						const ft::reverse_iterator<Iterator2>& rhs)
	{
		return (lhs._base > rhs._base);
	}
	
	template< class Iterator1, class Iterator2 >
		bool operator >= (const ft::reverse_iterator<Iterator1>& lhs,
						const ft::reverse_iterator<Iterator2>& rhs)
	{
		return (lhs._base >= rhs._base);
	}

} /* end of namespace */

#endif
