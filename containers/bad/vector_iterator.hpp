#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <cstddef>
#include "./iterators_traits.hpp"

namespace ft {

template <typename T, class Distance = ptrdiff_t,
			class Pointer = T*, class Reference = T&>
class random_access_iterator {
	public :
		typedef T									value_type;
		typedef Distance							difference_type;
		typedef Pointer								pointer;
		typedef Reference							reference;
		typedef std::random_access_iterator_tag		iterator_category;	// use std to be compatible with real containers

		random_access_iterator() : _arr_ptr() {}
		random_access_iterator(pointer ptr) : _arr_ptr(ptr) {}
		random_access_iterator(const random_access_iterator &rhs) : _arr_ptr(rhs._arr_ptr) {}
		virtual ~random_access_iterator() {}

		random_access_iterator operator= (const random_access_iterator& rhs) {
			if (this == &rhs)
				return *this;
			this->_arr_ptr = rhs._arr_ptr;
			return *this;
		}

		const pointer &base() const {return _arr_ptr;}

		reference operator*() const {return *_arr_ptr;}
		pointer operator->() const {return &(this->operator*());}

		bool operator>(random_access_iterator & rhs) { return this->_arr_ptr > rhs._arr_ptr;}
		bool operator<(random_access_iterator & rhs) { return this->_arr_ptr < rhs._arr_ptr;}
		bool operator>=(random_access_iterator const & rhs) const { return this->_arr_ptr >= rhs._arr_ptr;}
		bool operator<=(random_access_iterator const & rhs) const { return this->_arr_ptr <= rhs._arr_ptr;}
		// friend bool operator>(random_access_iterator const & lhs, random_access_iterator const & rhs) { return lhs._arr_ptr > rhs._arr_ptr;}
		// friend bool operator<(random_access_iterator const & lhs, random_access_iterator const & rhs) { return lhs._arr_ptr < rhs._arr_ptr;}

		random_access_iterator& operator++() {_arr_ptr++; return *this;}
		random_access_iterator operator++(int) {random_access_iterator tmp = *this; ++(*this); return tmp;}
		random_access_iterator& operator--() {_arr_ptr--; return *this;}
		random_access_iterator operator--(int) {random_access_iterator tmp = *this; --(*this); return tmp;}

		random_access_iterator operator+(const difference_type& rhs) const {return random_access_iterator(this->_arr_ptr + rhs);}
		random_access_iterator operator-(const difference_type& rhs) const {return random_access_iterator(this->_arr_ptr - rhs);}

		random_access_iterator& operator+=(difference_type const & rhs) {this->_arr_ptr += rhs; return *this;}
		random_access_iterator& operator-=(difference_type const & rhs) {this->_arr_ptr -= rhs; return *this;}

		reference operator[](difference_type n) const {return *(operator+(n));};
		
		operator random_access_iterator<const T>() const {
			return random_access_iterator<const T>(this->_arr_ptr);
		}
	private:
		pointer _arr_ptr;
};

template <typename T>
bool operator== (const random_access_iterator<T> lhs,
			const random_access_iterator<T> rhs) {
		return lhs.base() == rhs.base();
};

// const
template <typename T_L, typename T_R>
bool operator== (const random_access_iterator<T_L> lhs,
			const random_access_iterator<T_R> rhs) {
		return lhs.base() == rhs.base();
};


template <typename T>
bool operator!= (const random_access_iterator<T> lhs,
			const random_access_iterator<T> rhs) {
		return lhs.base() != rhs.base();
};

// const
template <typename T_L, typename T_R>
bool operator!= (const random_access_iterator<T_L> lhs,
			const random_access_iterator<T_R> rhs) {
		return lhs.base() != rhs.base();
};


template <typename T>
bool operator< (const random_access_iterator<T> lhs,
			const random_access_iterator<T> rhs) {
		return lhs.base() < rhs.base();
};

// const
template <typename T_L, typename T_R>
bool operator< (const random_access_iterator<T_L> lhs,
			const random_access_iterator<T_R> rhs) {
		return lhs.base() < rhs.base();
};


template <typename T>
bool operator<= (const random_access_iterator<T> lhs,
			const random_access_iterator<T> rhs) {
		return lhs.base() <= rhs.base();
};

// const
template <typename T_L, typename T_R>
bool operator<= (const random_access_iterator<T_L> lhs,
			const random_access_iterator<T_R> rhs) {
		return lhs.base() <= rhs.base();
};

template <typename T>
bool operator> (const random_access_iterator<T> lhs,
			const random_access_iterator<T> rhs) {
		return lhs.base() > rhs.base();
};

// const
template <typename T_L, typename T_R>
bool operator> (const random_access_iterator<T_L> lhs,
			const random_access_iterator<T_R> rhs) {
		return lhs.base() > rhs.base();
};


template <typename T>
bool operator>= (const random_access_iterator<T> lhs,
			const random_access_iterator<T> rhs) {
		return lhs.base() >= rhs.base();
};

// const
template <typename T_L, typename T_R>
bool operator>= (const random_access_iterator<T_L> lhs,
			const random_access_iterator<T_R> rhs) {
		return lhs.base() >= rhs.base();
};


template <typename T>
random_access_iterator<T>
operator+(
	typename ft::random_access_iterator<T>::difference_type n,
	typename ft::random_access_iterator<T>& el) {
		return &(*el) + n;
};

template <typename T>
typename ft::random_access_iterator<T>::difference_type
operator- (const random_access_iterator<T> lhs,
			const random_access_iterator<T> rhs) {
		return lhs.base() - rhs.base();
};

// iterator - const iterator
template <typename T_L, typename T_R>
typename ft::random_access_iterator<T_L>::difference_type
operator- (const random_access_iterator<T_L> lhs,
			const random_access_iterator<T_R> rhs) {
		return lhs.base() - rhs.base();
};

}
#endif