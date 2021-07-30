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

# pragma once
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
	# define ctpl	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>	
	# define tpl	template <class Category, class T, class Distance, class Pointer, class Reference >
	# define typ	typename iterator< Category, T, Distance, Pointer, Reference >
	# define itr	iterator< Category, T, Distance, Pointer, Reference >
	# define iitr	InputIterator< Category, T, Distance, Pointer, Reference >
	# define oitr	OutputIterator< Category, T, Distance, Pointer, Reference >
	# define fitr	ForwardIterator< Category, T, Distance, Pointer, Reference >
	# define bitr	BidiretionalIterator< Category, T, Distance, Pointer, Reference >
	# define ritr	RandomAccessIterator< Category, T, Distance, Pointer, Reference >

	ctpl
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
	iterator();
	virtual ~iterator();

	/*
	** Common operators
	*/
	protected:
		iterator	operator ++ ();		//prefix
		iterator	operator ++ (int);	//postfix
		iterator	operator  = (const iterator& x);

	/*
	** Member variables
	*/
		pointer				_ptr;
		iterator_category	_cat;
	};

/*
** InputIterator
*/
	ctpl
	class InputIterator : virtual public itr
	{
	/*
	** Constructor
	*/
	private:
		InputIterator();

	public:
		InputIterator(const InputIterator& x);
		virtual	~InputIterator();

	/*
	** Operator overload
	*/
	protected:
		bool			operator == (const InputIterator& x);
		bool			operator != (const InputIterator& x);
		typ::Pointer	operator * ();
		typ::value_type	operator -> ();
	};

/*
**	OutputIterator
*/
	ctpl
	class OutputIterator : virtual public itr
	{
	/*
	** Constructor
	*/
	private:
		OutputIterator();
	
	public:
		OutputIterator(const OutputIterator& x);
		virtual	~OutputIterator();

	/*
	** Operator overload
	*/
		typ::reference	operator -> ();
	};

/*
** Forward iterator
*/
	ctpl
	class ForwardIterator : public iitr, public oitr
	{
	/*
	** Constructor
	*/
	public:
		ForwardIterator();
		ForwardIterator(const ForwardIterator& x);
		virtual ~ForwardIterator();
	};

/*
** Bidirectional iterator
*/
	ctpl
	class BidirectionalIterator : public fitr
	{
	/*
	** Constructor
	*/
	public:
		BidirectionalIterator();
		BidirectionalIterator(const BidirectionalIterator& x);
		virtual ~BidirectionalIterator();
	
	/*
	** Operator overload
	*/
	protected:
		iterator	operator -- ();		//prefix
		iterator	operator -- (int);	//postfix
	};

/*
** Random access iterator
*/
	ctpl
	class RandomAccessIterator : public bitr
	{
	/*
	** Constructor
	*/
	public:
		RandomAccessIterator();
		RandomAccessIterator(const RandomAccessIterator& x);
		virtual ~RandomAccessIterator();
	
	/*
	** Operator overload
	*/
	protected:
		iterator	operator  + (int);
		iterator	operator  + (const Iterator& x);
		iterator	operator  - (int);
		iterator	operator  - (const Iterator& x);
		bool		operator  < (const Iterator& x);
		bool		operator  > (const Iterator& x);
		bool		operator <= (const Iterator& x);
		bool		operator >= (const Iterator& x);
		iterator	operator += (int);
		iterator	operator -= (int);
		value_type	operator [] (std::size_t n);
	};

}

# include "iterator.ipp"
# include "input.ipp"
# include "output.ipp"
# include "forward.ipp"
# include "bidirectional.ipp"
# include "random_access.ipp"

# undef ctpl
# undef tpl

#endif