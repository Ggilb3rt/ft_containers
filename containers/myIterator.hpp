#ifndef MYITERATOR_HPP
#define MYITERATOR_HPP

#include <cstddef>
#include "iterators_traits.hpp"


template <class Category, class T, class Distance = ptrdiff_t,
			class Pointer = T*, class Reference = T&>
struct MyIterator {
	typedef T         value_type;
	typedef Distance  difference_type;
	typedef Pointer   pointer;
	typedef Reference reference;
	typedef Category  iterator_category;

// this is for forward_iterator_tag, it's not generic, need to put this in iterator_traits ?
	MyIterator(pointer ptr) : _arr_ptr(ptr) {}
	~MyIterator() {}

	reference operator*() const {return *_arr_ptr;}
	pointer operator->() {return _arr_ptr;}

	MyIterator& operator++() {_arr_ptr++; return *this;}
	MyIterator operator++(int) {MyIterator tmp = *this; ++(*this); return tmp;}

	friend bool operator== (const MyIterator& a, const MyIterator& b) {return a._arr_ptr == b._arr_ptr;};
	friend bool operator!= (const MyIterator& a, const MyIterator& b) {return a._arr_ptr != b._arr_ptr;};

	private:
		pointer _arr_ptr;
};

#endif