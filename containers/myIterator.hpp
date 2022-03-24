#ifndef MYITERATOR_HPP
#define MYITERATOR_HPP

#include <cstddef>


struct input_iterator_tag { };
struct output_iterator_tag { };
struct forward_iterator_tag : public input_iterator_tag { };
struct bidirectional_iterator_tag : public forward_iterator_tag { };
struct random_access_iterator_tag : public bidirectional_iterator_tag { };


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

	reference operator*() const {return *_arr_ptr;}
	pointer operator->() {return _arr_ptr;}

	MyIterator& operator++() {_arr_ptr++; return *this;}
	MyIterator operator++(int) {MyIterator tmp = *this; ++(*this); return tmp;}

	friend bool operator== (const MyIterator& a, const MyIterator& b) {return a._arr_ptr == b._arr_ptr;};
	friend bool operator!= (const MyIterator& a, const MyIterator& b) {return a._arr_ptr != b._arr_ptr;};

	private:
		pointer _arr_ptr;
};


template< class _Iterator >
struct iterator_traits;

template<typename _Iterator>
struct iterator_traits
{
	typedef typename _Iterator::iterator_category iterator_category;
	typedef typename _Iterator::value_type        value_type;
	typedef typename _Iterator::difference_type   difference_type;
	typedef typename _Iterator::pointer           pointer;
	typedef typename _Iterator::reference         reference;
};

#endif