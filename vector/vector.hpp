/* ************************************************************************** */
/*	      __   __   ______     ______     ______   ______     ______		  */   
/*	     /\ \ / /  /\  ___\   /\  ___\   /\__  _\ /\  __ \   /\  == \		  */
/*	     \ \ \'/   \ \  __\   \ \ \____  \/_/\ \/ \ \ \/\ \  \ \  __<		  */
/*	      \ \__|    \ \_____\  \ \_____\    \ \_\  \ \_____\  \ \_\ \_\ 	  */
/*	       \/_/      \/_____/   \/_____/     \/_/   \/_____/   \/_/ /_/ 	  */
/*																			  */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*																			  */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# pragma once
# include <memory>

namespace ft {

	# define tpl template < class T, class Alloc >
	# define vec vector< T, Alloc >

	template < class T, class Alloc = std::allocator<T> >
	class vector {
		public:
			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef std::size_t										size_type;
			typedef std::ptrdiff_t									difference_type;
			typedef value_type&										reference;
			typedef const value_type&								const_reference;
			typedef value_type*										pointer;
			typedef const value_type*								const_pointer;
			typedef RandomAccessIterator<T*, T&>					iterator;
			typedef RandomAccessIterator<const T*, const T&>		const_iterator;
			typedef ReverseRandomAccessIterator<T*, T&>				reverse_iterator;
			typedef ReverseRandomAccessIterator<const T*, const T&>	const_reverse_iterator;

		private:
			vector();

		public:
		/*
		** CoPlIeN
		*/
			vector(/*constructor stuff */);
			virtual ~vector();
			vector(const vector &v);
			Vector &operator = (const vector &v);
	
		/*
		** ITERATORS
		*/
			iterator				begin();
			const_iterator			begin() const;
			iterator				end();
			const_iterator			end() const;
			reverse_iterator		rbegin();
			const_reverse_iterator	rbegin() const;
			reverse_iterator		rend();
			const_reverse_iterator	rend() const;

		/*
		** CAPACITY
		*/
			size_type	size() const;
			size_type	max_size() const;
			void		resize (size_type n, value_type val = value_type());
			size_type	capacity() const;
			bool		empty() const;
			void		reserve (size_type n);

		/*
		** ELEMENT ACCESS
		*/
			reference		operator[] (size_type n);
			const_reference	operator[] (size_type n) const;
			reference		at (size_type n);
			const_reference	at (size_type n) const;
			reference		front();
			const_reference	front() const;
			reference		back();
			const_reference	back() const;

		/*
		** MODIFIERS
		*/
			template	<class InputIterator> 	//waarom moet dit?
			void		assign (InputIterator first, InputIterator last);
			void		assign (size_type n, const value_type& val);
			void		push_back (const value_type& val);
			void		pop_back();
			iterator	insert (iterator position, const value_type& val);	
			void 		insert (iterator position, size_type n, const value_type& val);
			template	<class InputIterator>
			void 		insert (iterator position, InputIterator first, InputIterator last);
			iterator	erase (iterator position);
			iterator	erase (iterator first, iterator last);
			void		swap (vector& x);
			void		clear();

		/*
		** ALLOCATOR
		*/
			allocator_type	get_allocator() const;
	};
}

# include "iterators.ipp"

#endif
