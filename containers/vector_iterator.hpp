#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <cstddef>
#include "iterators_traits.hpp"

namespace ft {

template <class T, class Distance = ptrdiff_t,
			class Pointer = T*, class Reference = T&>
class VectorIterator {
	public :
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef ft::random_access_iterator_tag	iterator_category;

		VectorIterator() : _arr_ptr() {}
		VectorIterator(pointer ptr) : _arr_ptr(ptr) {}
		VectorIterator(const VectorIterator &rhs) : _arr_ptr(rhs._arr_ptr) {}
		virtual ~VectorIterator() {}

		VectorIterator operator= (const VectorIterator& rhs) {
			if (this == &rhs)
				return *this;
			this->_arr_ptr = rhs._arr_ptr;
			return *this;
		}

		pointer	base() const {return this->_arr_ptr;}

		reference operator*() const {return *_arr_ptr;}
		pointer operator->() const {return _arr_ptr;}
		// const_reference operator*() const {std::cout << "Const hello"; return *_arr_ptr;}

		// bool operator== (const VectorIterator& rhs) {return this->_arr_ptr == rhs._arr_ptr;};
		// bool operator!= (const VectorIterator& rhs) {return !(*this == rhs);};
		bool operator>(VectorIterator const & rhs) const { return this->_arr_ptr > rhs._arr_ptr;}
		bool operator>=(VectorIterator const & rhs) const { return this->_arr_ptr >= rhs._arr_ptr;}
		bool operator<(VectorIterator const & rhs) const { return this->_arr_ptr < rhs._arr_ptr;}
		bool operator<=(VectorIterator const & rhs) const { return this->_arr_ptr <= rhs._arr_ptr;}

		VectorIterator& operator++() {_arr_ptr++; return *this;}
		VectorIterator operator++(int) {VectorIterator tmp = *this; ++(*this); return tmp;}
		VectorIterator& operator--() {_arr_ptr--; return *this;}
		VectorIterator operator--(int) {VectorIterator tmp = *this; --(*this); return tmp;}

		//! fonctionne avec a +/- n MAIS ne fonctionne pas avec n +/- a
		VectorIterator operator+(const difference_type& rhs) const {return VectorIterator(this->_arr_ptr + rhs);}
		VectorIterator operator-(const difference_type& rhs) const {return VectorIterator(this->_arr_ptr - rhs);}
		difference_type operator+(const VectorIterator& rhs) const {return rhs._arr_ptr + _arr_ptr;} // real doesn't works
		difference_type operator-(const VectorIterator& rhs) const {return _arr_ptr - rhs._arr_ptr;}
		// VectorIterator operator+(int const & rhs) {return this->_arr_ptr + rhs;}
		// VectorIterator operator-(int const & rhs) {return this->_arr_ptr - rhs;}
		// friend VectorIterator operator+(VectorIterator lhs, const difference_type& rhs) {lhs += rhs; return lhs;}


		VectorIterator& operator+=(difference_type const & rhs) {this->_arr_ptr += rhs; return *this;}
		VectorIterator& operator-=(difference_type const & rhs) {this->_arr_ptr -= rhs; return *this;}

		reference operator[](difference_type n) const {return *(operator+(n));};

	private:
		pointer _arr_ptr;
};

template <typename T>
//typename ft::VectorIterator<T>::diffrence_type
bool operator== (const ft::VectorIterator<T> lhs,
			const ft::VectorIterator<T> rhs) {
		return lhs.base() == rhs.base();
};

// const
template <typename T_L, typename T_R>
// typename ft::VectorIterator<T_L>::diffrence_type
bool operator== (const ft::VectorIterator<T_L> lhs,
			const ft::VectorIterator<T_R> rhs) {
		return lhs.base() == rhs.base();
};


template <typename T>
//typename ft::VectorIterator<T>::diffrence_type
bool operator!= (const ft::VectorIterator<T> lhs,
			const ft::VectorIterator<T> rhs) {
		return lhs.base() != rhs.base();
};

// const
template <typename T_L, typename T_R>
//typename ft::VectorIterator<T_L>::diffrence_type
bool operator!= (const ft::VectorIterator<T_L> lhs,
			const ft::VectorIterator<T_R> rhs) {
		return lhs.base() != rhs.base();
};


template <typename T>
typename ft::VectorIterator<T>::diffrence_type
operator< (const ft::VectorIterator<T> lhs,
			const ft::VectorIterator<T> rhs) {
		return lhs.base() < rhs.base();
};

// const
template <typename T_L, typename T_R>
typename ft::VectorIterator<T_L>::diffrence_type
operator< (const ft::VectorIterator<T_L> lhs,
			const ft::VectorIterator<T_R> rhs) {
		return lhs.base() < rhs.base();
};


template <typename T>
typename ft::VectorIterator<T>::diffrence_type
operator<= (const ft::VectorIterator<T> lhs,
			const ft::VectorIterator<T> rhs) {
		return lhs.base() <= rhs.base();
};

// const
template <typename T_L, typename T_R>
typename ft::VectorIterator<T_L>::diffrence_type
operator<= (const ft::VectorIterator<T_L> lhs,
			const ft::VectorIterator<T_R> rhs) {
		return lhs.base() <= rhs.base();
};


template <typename T>
typename ft::VectorIterator<T>::diffrence_type
operator> (const ft::VectorIterator<T> lhs,
			const ft::VectorIterator<T> rhs) {
		return lhs.base() > rhs.base();
};

// const
template <typename T_L, typename T_R>
typename ft::VectorIterator<T_L>::diffrence_type
operator> (const ft::VectorIterator<T_L> lhs,
			const ft::VectorIterator<T_R> rhs) {
		return lhs.base() > rhs.base();
};


template <typename T>
typename ft::VectorIterator<T>::diffrence_type
operator>= (const ft::VectorIterator<T> lhs,
			const ft::VectorIterator<T> rhs) {
		return lhs.base() >= rhs.base();
};

// const
template <typename T_L, typename T_R>
typename ft::VectorIterator<T_L>::diffrence_type
operator>= (const ft::VectorIterator<T_L> lhs,
			const ft::VectorIterator<T_R> rhs) {
		return lhs.base() >= rhs.base();
};

}
#endif