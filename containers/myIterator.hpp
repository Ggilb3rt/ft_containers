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

	MyIterator() : _arr_ptr(NULL) {}
	MyIterator(pointer ptr) : _arr_ptr(ptr) {}
	MyIterator(const MyIterator &rhs) : _arr_ptr(rhs._arr_ptr) {}
	~MyIterator() {}

	//? PK friend ?
	//friend bool operator==(const MyIterator& a, const MyIterator& b) {return a._arr_ptr == b._arr_ptr;};
	// friend bool operator!=(const MyIterator& a, const MyIterator& b) {return a._arr_ptr != b._arr_ptr;};
	bool operator== (const MyIterator& rhs) {return this->_arr_ptr == rhs._arr_ptr;};
	bool operator!= (const MyIterator& rhs) {return !(*this == rhs);};

	reference operator*() const {return *_arr_ptr;}
	pointer operator->() const {return _arr_ptr;}

	void operator= (MyIterator rhs) {this->_arr_ptr = rhs._arr_ptr;}

	MyIterator& operator++() {_arr_ptr++; return *this;}
	MyIterator operator++(int) {MyIterator tmp = *this; ++(*this); return tmp;}
	MyIterator& operator--() {_arr_ptr--; return *this;}
	MyIterator operator--(int) {MyIterator tmp = *this; --(*this); return tmp;}

	//! fonctionne avec a +/- n MAIS ne fonctionne pas avec n +/- a
	MyIterator operator+(const difference_type& rhs) const {return MyIterator(this->_arr_ptr + rhs);}
	MyIterator operator-(const difference_type& rhs) const {return MyIterator(this->_arr_ptr - rhs);}
	difference_type operator+(const MyIterator& rhs) const {return _arr_ptr + rhs._arr_ptr;}
	difference_type operator-(const MyIterator& rhs) const {return _arr_ptr - rhs._arr_ptr;}
	// MyIterator operator+(int const & rhs) {return this->_arr_ptr + rhs;}
	// MyIterator operator-(int const & rhs) {return this->_arr_ptr - rhs;}
	// friend MyIterator operator+(MyIterator lhs, const difference_type& rhs) {lhs += rhs; return lhs;}

	bool operator>(MyIterator const & rhs) const { return this->_arr_ptr > rhs._arr_ptr;}
	bool operator>=(MyIterator const & rhs) const { return this->_arr_ptr >= rhs._arr_ptr;}
	bool operator<(MyIterator const & rhs) const { return this->_arr_ptr < rhs._arr_ptr;}
	bool operator<=(MyIterator const & rhs) const { return this->_arr_ptr <= rhs._arr_ptr;}

	MyIterator& operator+=(difference_type const & rhs) {this->_arr_ptr += rhs; return *this;}
	MyIterator& operator-=(difference_type const & rhs) {this->_arr_ptr -= rhs; return *this;}

	reference operator[](const unsigned int index) {return *(_arr_ptr + index);};

	private:
		pointer _arr_ptr;
};

#endif