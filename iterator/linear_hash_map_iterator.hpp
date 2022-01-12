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

	template < class T, class Indices, class Buckets, class Category = ft::forward_iterator_tag,
		class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T& >
			struct linear_hash_map_iterator : ft::iterator<Category, T, Distance, Pointer, Reference>
	{

	//////////////
	// Typedefs //
	//////////////
	private:

		typedef ft::linear_hash_map_iterator<T, Indices, Buckets, Category, Distance, const T*, const T& >	const_iter;

	public:

		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Indices		head;
		typedef Buckets		bucket;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;

	//////////////////////
	// Member variables //
	//////////////////////
	protected:

		head*	_arr;
		bucket*	_cur;

	/////////////////
	// constructor //
	/////////////////
	public:

		linear_hash_map_iterator(head* head = NULL) : _arr(head), _cur(*head) {}

		linear_hash_map_iterator(const linear_hash_map_iterator& x) {
			*this = x;
		}

		virtual ~linear_hash_map_iterator() {}

	/////////////////
	// Get pointer //
	/////////////////
	public:

		bucket*	get_ptr(void)
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
			return (const_iter(_ptr));
		}

	}; /* end of linear hash map iterator */

} /* end of namespace */

#endif
