/* ************************************************************************** */
/*                                                                            */
/*                    _______     __        __      _______                   */
/*                   |   __ "\   /""\      |" \    /"      \                  */
/*                   (. |__) :) /    \     ||  |  |:        |                 */
/*                   |:  ____/ /' /\  \    |:  |  |_____/   )                 */
/*                   (|  /    //  __'  \   |.  |   //      /                  */
/*                  /|__/ \  /   /  \\  \  /\  |\ |:  __   \                  */
/*                 (_______)(___/    \___)(__\_|_)|__|  \___)                 */
/*                                                                            */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

# include <memory>

namespace ft
{
//////////
// PAIR //
//////////

	template <class T1, class T2>
		struct pair
	{

	///////////////
	// type defs //
	///////////////
	public:

		typedef T1	first_type;
		typedef T2	second_type;

	//////////////////////
	// member variables //
	//////////////////////
	public:

		first_type	first;
		second_type	second;

	/////////////
	// CoPlIeN //
	/////////////
	public:

		pair()
			: first(first_type()), second(second_type())
		{}
		
		template<class U, class V>
			pair (const pair<U, V>& pr)
		{
			/*
			** misschien geen copy constructor,
			** kan wss float pair aan int pair assignen
			*/
			*this = pr;
		}
			
		pair (const first_type& a, const second_type& b)
			: first(a), second(b)
		{}

		pair& operator= (const pair& pr)
		{
			this->first		= pr.first;
			this->second	= pr.second;
			return (*this);
		}

	//////////////////////////
	// RELATIONAL OPERATORS //
	//////////////////////////
	public:

		template <class T1, class T2>
			friend	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs);

		template <class T1, class T2>
			friend bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs);

		template <class T1, class T2>
			friend bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs);

		template <class T1, class T2>
			friend bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs);

		template <class T1, class T2>
			friend bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs);

		template <class T1, class T2>
			friend bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs);

	}; /* end of pair */

/////////////////////////////////////////////////////////////////////
// PAIRS RELATIONAL OPERATORS BUT THEY ARE ACTUALLY NOT MY FRIENDS //
/////////////////////////////////////////////////////////////////////

	template <class T1, class T2>
		bool operator == (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}
	
	template <class T1, class T2>
		bool operator != (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T1, class T2>
		bool operator <  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	template <class T1, class T2>
		bool operator <= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T1, class T2>
		bool operator >  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T1, class T2>
		bool operator >= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs < rhs); }

} /* end of namespace */

#endif
