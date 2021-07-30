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
	# define tpl template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>	
	
	tpl
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
	** Common operators
	*/
	protected:
		reference	operator ++ ();		//prefix
		value_type	operator ++ (int);	//postfix
		reference	operator  = (const iterator& x);

	/*
	** Member variables
	*/
		pointer				_ptr;
		iterator_category	_cat;
	};

/*
** InputIterator
*/
	tpl
	class InputIterator : public iterator
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
		Pointer			operator -> ();
		value_type	operator -> ();
	};

/*
**	OutputIterator
*/
	tpl
	class OutputIterator : public iterator
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
		reference	operator -> ();
	};

/*
** Forward iterator
*/
	tpl
	class ForwardIterator : public virtual InputIterator, public virtual OutputIterator
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
	tpl
	class BidirectionalIterator : public ForwardIterator
	{
	/*
	** Constructor
	*/
	public:
		ForwardIterator();
		ForwardIterator(const ForwardIterator& x);
		virtual ~ForwardIterator();
	
	/*
	** Operator overload
	*/
	protected:
		reference	operator -- ();		//prefix
		value_type	operator -- (int);	//postfix
	};

/*
** Random access iterator
*/
	tpl
	class RandomAccessIterator : public BidirectionalIterator
	{
	/*
	** Constructor
	*/
	public:
		ForwardIterator();
		ForwardIterator(const ForwardIterator& x);
		virtual ~ForwardIterator();
	
	/*
	** Operator overload
	*/
	protected:
		value_type	operator  + (int);
		value_type	operator  + (const Iterator& x);
		value_type	operator  - (int);
		value_type	operator  - (const Iterator& x);
		bool		operator  < (const Iterator& x);
		bool		operator  > (const Iterator& x);
		bool		operator <= (const Iterator& x);
		bool		operator >= (const Iterator& x);
		value_type	operator += (int);
		value_type	operator -= (int);
		value_type	operator [] (std::size_t n);
	};

	# undef tpl
}

#endif