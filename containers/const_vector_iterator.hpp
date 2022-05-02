#ifndef CONST_VECTOR_ITERATOR_HPP
#define CONST_VECTOR_ITERATOR_HPP

#include <cstddef>
#include "iterators_traits.hpp"
#include "vector_iterator.hpp"

namespace ft {

template <class Category, class T, class Distance = ptrdiff_t,
			class Pointer = T*, class Reference = T&>
struct ConstVectorIterator {
	typedef const T				value_type;
	typedef Distance			difference_type;
	typedef Pointer				pointer;
	typedef Reference			reference;
	typedef Category			iterator_category;
	typedef const reference		const_reference;

	ConstVectorIterator() : _arr_ptr() {}
	ConstVectorIterator(pointer ptr) : _arr_ptr(ptr) {}
	ConstVectorIterator(const VectorIterator<T> &rhs) : _arr_ptr(rhs._arr_ptr) {}
	ConstVectorIterator(const ConstVectorIterator &rhs) : _arr_ptr(rhs._arr_ptr) {}
	~ConstVectorIterator() {}

	bool operator== (ConstVectorIterator const & rhs) {return this->_arr_ptr == rhs._arr_ptr;};
	bool operator!= (ConstVectorIterator const & rhs) {return !(*this == rhs);};

	const_reference operator*() {return *_arr_ptr;}
	pointer operator->() const {return _arr_ptr;}

	void operator= (const ConstVectorIterator &rhs) {this->_arr_ptr = rhs._arr_ptr;}

	ConstVectorIterator& operator++() {_arr_ptr++; return *this;}
	ConstVectorIterator operator++(int) {ConstVectorIterator tmp = *this; ++(*this); return tmp;}
	ConstVectorIterator& operator--() {_arr_ptr--; return *this;}
	ConstVectorIterator operator--(int) {ConstVectorIterator tmp = *this; --(*this); return tmp;}

	//! fonctionne avec a +/- n MAIS ne fonctionne pas avec n +/- a
	ConstVectorIterator operator+(const difference_type& rhs) const {std::cout << this << std::endl; return ConstVectorIterator(this->_arr_ptr + rhs);}
	ConstVectorIterator operator-(const difference_type& rhs) const {return ConstVectorIterator(this->_arr_ptr - rhs);}
	difference_type operator+(const ConstVectorIterator& rhs) const {return rhs._arr_ptr + _arr_ptr;} // real doesn't works
	difference_type operator-(const ConstVectorIterator& rhs) const {std::cout << "diff" << std::endl; return _arr_ptr - rhs._arr_ptr;}
	// ConstVectorIterator operator+(int const & rhs) {return this->_arr_ptr + rhs;}
	// ConstVectorIterator operator-(int const & rhs) {return this->_arr_ptr - rhs;}
	// friend ConstVectorIterator operator+(ConstVectorIterator lhs, const difference_type& rhs) {lhs += rhs; return lhs;}

	bool operator>(ConstVectorIterator const & rhs) const { return this->_arr_ptr > rhs._arr_ptr;}
	bool operator>=(ConstVectorIterator const & rhs) const { return this->_arr_ptr >= rhs._arr_ptr;}
	bool operator<(ConstVectorIterator const & rhs) const { return this->_arr_ptr < rhs._arr_ptr;}
	bool operator<=(ConstVectorIterator const & rhs) const { return this->_arr_ptr <= rhs._arr_ptr;}

	ConstVectorIterator& operator+=(difference_type const & rhs) {this->_arr_ptr += rhs; return *this;}
	ConstVectorIterator& operator-=(difference_type const & rhs) {this->_arr_ptr -= rhs; return *this;}

	const_reference operator[](const unsigned int index) {return *(_arr_ptr + index);};

	private:
		pointer _arr_ptr;
};

}

#endif