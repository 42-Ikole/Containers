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

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

namespace ft {

/*
** Tags
*/
	struct input_iterator_tag			{};
	struct output_iterator_tag			{};
	struct forward_iterator_tag			{};
	struct bidirectional_iterator_tag	{};
	struct random_access_iterator_tag	{};

/*
** Iterator base class
*/
	# define itr	iterator< Category, T, Distance, Pointer, Reference >

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
	/*
	** Typedefs 
	*/
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;

	/*
	** constructor
	*/
	protected:

		iterator(const iterator& x) {
			*this = x;
		}

		virtual ~iterator() {}
	
	protected:
		iterator(Pointer ptr = NULL) : _ptr(ptr) {}

	/*
	** Common operators
	*/
	protected:

		iterator&	operator ++ (/* prefix */) {
			_ptr++;
			return (*this);
		}

		iterator&	operator ++ (int /* postfix */) {
			iterator tmp = *this;
			++(*this);
			return *tmp;
		}

		iterator	operator  = (const iterator& x) {
			this->_ptr = x._ptr;
			return (*this);
		}

	/*
	** Member variables
	*/
	protected:

		pointer	_ptr;
	};

/*
** InputIterator
*/
	template <class T, class Category = ft::input_iterator_tag, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	class InputIterator : public iterator< Category, T, Distance, Pointer, Reference >
	{
	/*
	** Typedefs 
	*/
		typedef typename  itr::value_type			value_type;
		typedef typename  itr::difference_type		difference_type;
		typedef typename  itr::pointer				pointer;
		typedef typename  itr::reference			reference;
		typedef typename  itr::iterator_category	iterator_category;

	/*
	** Constructor
	*/
	private:
		InputIterator();

	public:

		InputIterator(const InputIterator& x) {
			*this = x;
		}

		virtual	~InputIterator() {}
	
	protected:
		InputIterator(Pointer ptr = NULL) 
			: iterator< Category, T, Distance, Pointer, Reference >(ptr) {}

	/*
	** Operator overload
	*/
	protected:

		bool		operator == (const InputIterator& x) {
			return (this->_ptr == x._ptr);			
		}

		bool		operator != (const InputIterator& x) {
			return (this->_ptr != x._ptr);
		}
	
		reference	operator * () {
			return *(this->_ptr);
		}

		pointer		operator -> () {
			return (this->_ptr);
		}

	};

/*
** Forward iterator
*/
	template <class T, class Category = ft::forward_iterator_tag, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	class ForwardIterator : public InputIterator< Category, T, Distance, Pointer, Reference >
	{
	/*
	** Typedefs 
	*/
		typedef typename  itr::value_type			value_type;
		typedef typename  itr::difference_type		difference_type;
		typedef typename  itr::pointer				pointer;
		typedef typename  itr::reference			reference;
		typedef typename  itr::iterator_category	iterator_category;

	/*
	** Constructor
	*/
	public:

		ForwardIterator(Pointer ptr = NULL) 
			: InputIterator< Category, T, Distance, Pointer, Reference >(ptr) {}

		ForwardIterator(const ForwardIterator& x) {
			*this = x;
		}
	
		virtual ~ForwardIterator() {}
	};

/*
** Bidirectional iterator
*/
	template <class T, class Category = ft::bidirectional_iterator_tag, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	class BidirectionalIterator : public ForwardIterator< Category, T, Distance, Pointer, Reference >
	{
	/*
	** Typedefs 
	*/
		typedef typename  itr::value_type			value_type;
		typedef typename  itr::difference_type		difference_type;
		typedef typename  itr::pointer				pointer;
		typedef typename  itr::reference			reference;
		typedef typename  itr::iterator_category	iterator_category;

	/*
	** Constructor
	*/
	public:

		BidirectionalIterator(Pointer ptr = NULL) 
			: ForwardIterator< Category, T, Distance, Pointer, Reference >(ptr) {}
	
		BidirectionalIterator(const BidirectionalIterator& x) {
			*this = x;
		}

		virtual ~BidirectionalIterator() {}
	
	/*
	** Operator overload
	*/
	protected:
		
		BidirectionalIterator&	operator -- (/* prefix */) {
			this->_ptr--;
			return (*this);
		}

		BidirectionalIterator&	operator -- (int /* postfix */) {
			BidirectionalIterator tmp = *this;
			--(*this);
			return (tmp);
		}
	};

/*
** Random access iterator
*/
	template <class T, class Category = ft::random_access_iterator_tag, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	class RandomAccessIterator : public BidirectionalIterator< Category, T, Distance, Pointer, Reference >
	{
	/*
	** Typedefs 
	*/
		typedef typename  itr::value_type			value_type;
		typedef typename  itr::difference_type		difference_type;
		typedef typename  itr::pointer				pointer;
		typedef typename  itr::reference			reference;
		typedef typename  itr::iterator_category	iterator_category;

	/*
	** Constructor
	*/
	public:

		RandomAccessIterator(Pointer ptr = NULL)
			: BidirectionalIterator< Category, T, Distance, Pointer, Reference >(ptr) {}

		RandomAccessIterator(const RandomAccessIterator& x) {
			*this = x;
		}

		virtual ~RandomAccessIterator() {}
	
	/*
	** Operator overload
	*/
	protected:

		RandomAccessIterator	operator  + (difference_type val) {
			return (RandomAccessIterator(this->_ptr + val));
		}

		RandomAccessIterator	operator  + (const RandomAccessIterator& x) {
			return (RandomAccessIterator(*this + x));
		}

		RandomAccessIterator	operator  - (difference_type val) {
			return (RandomAccessIterator(this->_ptr - val));
		}

		difference_type			operator  - (const RandomAccessIterator& x) {
			return (RandomAccessIterator(this->_ptr - x._ptr));
		}

		bool					operator  < (const RandomAccessIterator& x) {
			return (this->_ptr < x._ptr);
		}

		bool					operator  > (const RandomAccessIterator& x) {
			return (this->_ptr > x._ptr);
		}

		bool					operator <= (const RandomAccessIterator& x) {
			return (this->_ptr <= x._ptr);
		}

		bool					operator >= (const RandomAccessIterator& x) {
			return (this->_ptr >= x._ptr);
		}

		RandomAccessIterator&	operator += (difference_type val) {
			this->_ptr += val;
			return (*this);
		}

		RandomAccessIterator&	operator -= (difference_type val) {
			this->_ptr -= val;
			return (*this);
		}

		reference				operator [] (std::size_t n) {
			return (*(this->_ptr + n));
		}

	};

}

# undef itr

#endif
