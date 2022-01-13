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

#ifndef HIPPITY_HOPPTIY_THIS_IS_HASH_MAP_PROPERTY
# define HIPPITY_HOPPTIY_THIS_IS_HASH_MAP_PROPERTY

# include <iterator_traits.hpp>
# include <iterator.hpp>
# include <sfinae.hpp>

namespace ft {

///////////////////////////////////
// linear hashmap iterator class //
///////////////////////////////////

	template < class T, class Link, class Category = ft::forward_iterator_tag,
		class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T& >
			struct linear_hash_map_iterator : ft::iterator<Category, T, Distance, Pointer, Reference>
	{

	//////////////
	// Typedefs //
	//////////////
	public:

		typedef ft::linear_hash_map_iterator<T, Link, Category, Distance, const T*, const T& >	const_iter;

	public:

		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Link		link;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;

	//////////////////////
	// Member variables //
	//////////////////////
	protected:

		link**	_arr;
		link*	_cur;

	/////////////////
	// constructor //
	/////////////////
	private:

		void is_forward_iterator(typename ft::forward_iterator_tag const &) {}

	public:

		linear_hash_map_iterator(link** head) : _arr(head), _cur(*head) {}

		linear_hash_map_iterator(link** head, link* cur) : _arr(head), _cur(cur) {}

		linear_hash_map_iterator() : _arr(NULL), _cur(NULL)
		{
			this->is_forward_iterator(typename ft::iterator_traits<linear_hash_map_iterator>::iterator_category());
		}

		linear_hash_map_iterator(const linear_hash_map_iterator& x) {
			*this = x;
		}

		virtual ~linear_hash_map_iterator() {}

	/////////////////
	// Get pointer //
	/////////////////
	public:

		link*	get_ptr(void)
		{
			return (_cur);
		}

	//////////////////////
	// Common operators //
	//////////////////////
	public:

		linear_hash_map_iterator&	operator ++ (/* prefix */) {
			if (_cur->next != NULL)
				_cur = _cur->next;
			else {
				++_arr;
				while (*_arr == NULL)
					++_arr;
				_cur = *_arr;
			}
			return (*this);
		}

		linear_hash_map_iterator	operator ++ (int /* postfix */) {
			linear_hash_map_iterator tmp = *this;
			++(*this);
			return (tmp);
		}

		linear_hash_map_iterator&	operator  = (const linear_hash_map_iterator& x) {
			this->_arr = x._arr;
			this->_cur = x._cur;
			return (*this);
		}

	//////////////////////////////
	// Input iterator operators //
	//////////////////////////////
	private:

		void is_input_iterator(typename ft::input_iterator_tag const &) {}

	public:

		bool operator == (const linear_hash_map_iterator& x)
		{
			this->is_input_iterator(typename ft::iterator_traits<linear_hash_map_iterator>::iterator_category());
			return (this->_arr == x._arr && this->_cur == x._cur);			
		}

		bool operator != (const linear_hash_map_iterator& x)
		{
			this->is_input_iterator(typename ft::iterator_traits<linear_hash_map_iterator>::iterator_category());
			return !(*this == x);
		}
	
		reference operator * ()
		{
			this->is_input_iterator(typename ft::iterator_traits<linear_hash_map_iterator>::iterator_category());
			return (_cur->element);
		}

		pointer operator -> () 
		{
			this->is_input_iterator(typename ft::iterator_traits<linear_hash_map_iterator>::iterator_category());
			return (&(_cur->element));
		}

	///////////////////////////////////
	// implicit conversion operators //
	///////////////////////////////////
	public:
	
		operator const_iter () const
		{
			return (const_iter(_arr, _cur));
		}

	}; /* end of linear hash map iterator */

} /* end of namespace */

#endif
