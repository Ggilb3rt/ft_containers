#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include <cstddef>
#include "../utils/iterators_traits.hpp"

namespace ft {

template <typename T, class Distance = ptrdiff_t,
			class Pointer = T*, class Reference = T&>
class map_iterator {
	public :
		typedef T									value_type;
		typedef Distance							difference_type;
		typedef Pointer								pointer;
		typedef Reference							reference;
		typedef std::bidirectional_iterator_tag		iterator_category;	// use std to be compatible with real containers

		map_iterator() : _root(), _nil(), _current() {}
		map_iterator(pointer ptr) : _root(ptr), _nil(), _current() {}
		map_iterator(const map_iterator &rhs) : _root(rhs._arr_ptr), _nil(), _current() {}
		virtual ~map_iterator() {}

		map_iterator operator= (const map_iterator& rhs) {
			if (this == &rhs)
				return *this;
			this->_current = rhs._current;
            this->_root = rhs._root;
            this->_nil = rhs._nil;
			return *this;
		}

		// const pointer &base() const {return _root;}

		reference operator*() const {return *_current;}
		pointer operator->() const {return &(this->operator*());}

		map_iterator& operator++() {_arr_ptr++; return *this;}
		map_iterator operator++(int) {map_iterator tmp = *this; ++(*this); return tmp;}
		map_iterator& operator--() {_arr_ptr--; return *this;}
		map_iterator operator--(int) {map_iterator tmp = *this; --(*this); return tmp;}
		
		operator map_iterator<const T>() const {
			return map_iterator<const T>(this->_arr_ptr);
		}
	private:
		pointer _root;
		pointer _nil;
		pointer _current;
};

template <typename T>
bool operator== (const map_iterator<T> lhs,
			const map_iterator<T> rhs) {
		return lhs._current == rhs._current;
};

// const
template <typename T_L, typename T_R>
bool operator== (const map_iterator<T_L> lhs,
			const map_iterator<T_R> rhs) {
		return lhs._current == rhs._current;
};


template <typename T>
bool operator!= (const map_iterator<T> lhs,
			const map_iterator<T> rhs) {
		return lhs._current != rhs._current;
};

// const
template <typename T_L, typename T_R>
bool operator!= (const map_iterator<T_L> lhs,
			const map_iterator<T_R> rhs) {
		return lhs._current != rhs._current;
};

}
#endif