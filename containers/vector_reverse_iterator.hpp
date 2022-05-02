#ifndef VECTOR_REVERSE_ITERATOR_HPP
#define VECTOR_REVERSE_ITERATOR_HPP

#include <cstddef>
#include "iterators_traits.hpp"
#include "vector_iterator.hpp"

namespace ft {

template <typename Iter>
class VectorReverseIterator {
	public :
		typedef Iter													iterator_type;
		typedef typename ft::iterator_traits<Iter>::value_type			value_type;
		typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iter>::pointer				pointer;
		typedef typename ft::iterator_traits<Iter>::reference			reference;
		typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;

		VectorReverseIterator() : current() {}
		VectorReverseIterator(iterator_type x) : current(x) {} // must be explicit
		template <class U>
		VectorReverseIterator(const VectorReverseIterator<U>& other) : current(other.base()) {}

		virtual ~VectorReverseIterator() {}

		iterator_type base() const {return current;}

		reference	operator*() const {iterator_type tmp = current; return *(--tmp);}
		pointer		operator->() const {return &(operator*());}

		VectorReverseIterator&	operator++() {--current; return *this;} 
		VectorReverseIterator	operator++(int) {
			VectorReverseIterator tmp = *this;
			++(*this);
			return tmp;
		} 
		VectorReverseIterator&	operator--() {++current; return *this;} 
		VectorReverseIterator	operator--(int) {
			VectorReverseIterator tmp = *this;
			--(*this);
			return tmp;
		}

		VectorReverseIterator& operator+=(difference_type const & rhs) {current -= rhs; return *this;}
		VectorReverseIterator& operator-=(difference_type const & rhs) {current += rhs; return *this;}
		VectorReverseIterator operator+(difference_type n) const { return (this->base()-n);}
		VectorReverseIterator operator-(difference_type n) const { return (this->base()+n);}

		reference operator[](difference_type n) const {return this->base()[-n-1];}

	protected :
		iterator_type    current;
};

template <class Iter>
VectorReverseIterator<Iter>
operator+(typename VectorReverseIterator<Iter>::difference_type n,
			const VectorReverseIterator<Iter>& it) {
				return (it.base() - n);
};

template< class Iter>
typename VectorReverseIterator<Iter>::difference_type
operator-(const ft::VectorReverseIterator<Iter>& lhs,
			const ft::VectorReverseIterator<Iter>& rhs) {
				return (rhs.base() - lhs->base());
};

template< class Iterator1, class Iterator2 >
bool operator==( const ft::VectorReverseIterator<Iterator1>& lhs,
				const ft::VectorReverseIterator<Iterator2>& rhs ) {
					return (lhs.base() == rhs.base());
};

template< class Iterator1, class Iterator2 >
bool operator!=( const ft::VectorReverseIterator<Iterator1>& lhs,
				const ft::VectorReverseIterator<Iterator2>& rhs ) {
					return (lhs.base() != rhs.base());
};

template< class Iterator1, class Iterator2 >
bool operator>( const ft::VectorReverseIterator<Iterator1>& lhs,
				const ft::VectorReverseIterator<Iterator2>& rhs ) {
					return (lhs.base() > rhs.base());
};

template< class Iterator1, class Iterator2 >
bool operator>=( const ft::VectorReverseIterator<Iterator1>& lhs,
				const ft::VectorReverseIterator<Iterator2>& rhs ) {
					return (lhs.base() >= rhs.base());
};

template< class Iterator1, class Iterator2 >
bool operator<( const ft::VectorReverseIterator<Iterator1>& lhs,
				const ft::VectorReverseIterator<Iterator2>& rhs ) {
					return (lhs.base() < rhs.base());
};

template< class Iterator1, class Iterator2 >
bool operator<=( const ft::VectorReverseIterator<Iterator1>& lhs,
				const ft::VectorReverseIterator<Iterator2>& rhs ) {
					return (lhs.base() <= rhs.base());
};

}
#endif