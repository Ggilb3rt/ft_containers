#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

template <typename T>
class	vector {

// T*		array
// iterator _begin
// iterator _end
// iterator _end_reserve

/****************************/
/*			Coplien			*/
/****************************/
	// Default
	explicit vector(const allocator_type& alloc = allocator_type());
	//	Fill
	explicit vector(size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type());
	// Range
	template <class InputIterator>
	vector(InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type());
	// Copy
	vector(const vector& x);

/****************************/
/*			Iterators		*/
/****************************/


/****************************/
/*			Capacity		*/
/****************************/


/****************************/
/*			El access		*/
/****************************/


/****************************/
/*			Modifiers		*/
/****************************/


/****************************/
/*			Allocator		*/
/****************************/


};


#endif