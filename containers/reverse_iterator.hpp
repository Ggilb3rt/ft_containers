#ifndef reverse_iterator_HPP
#define reverse_iterator_HPP

#include <cstddef>
#include "iterators_traits.hpp"
#include "vector_iterator.hpp"

namespace ft {

template <typename Iter>
class my_reverse_iterator {
	public :
		typedef Iter													iterator_type;
		typedef typename ft::iterator_traits<Iter>::value_type			value_type;
		typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iter>::pointer				pointer;
		typedef typename ft::iterator_traits<Iter>::reference			reference;
		typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;

		my_reverse_iterator() : current() {}
		my_reverse_iterator(iterator_type x) : current(x) {} // must be explicit
		template <class U>
		my_reverse_iterator(const my_reverse_iterator<U>& other) : current(other.base()) {}

		virtual ~my_reverse_iterator() {}

		iterator_type base() const {return current;}

		reference	operator*() const {iterator_type tmp = current; return *(--tmp);}
		pointer		operator->() const {return &(operator*());}

		my_reverse_iterator&	operator++() {--current; return *this;} 
		my_reverse_iterator	operator++(int) {
			my_reverse_iterator tmp = *this;
			++(*this);
			return tmp;
		} 
		my_reverse_iterator&	operator--() {++current; return *this;} 
		my_reverse_iterator	operator--(int) {
			my_reverse_iterator tmp = *this;
			--(*this);
			return tmp;
		}

		my_reverse_iterator& operator+=(difference_type const & rhs) {current -= rhs; return *this;}
		my_reverse_iterator& operator-=(difference_type const & rhs) {current += rhs; return *this;}
		my_reverse_iterator operator+(difference_type n) const { return (this->base()-n);}
		my_reverse_iterator operator-(difference_type n) const { return (this->base()+n);}

		reference operator[](difference_type n) const {return this->base()[-n-1];}

	protected :
		iterator_type    current;
};

template <class Iter>
my_reverse_iterator<Iter>
operator+(typename my_reverse_iterator<Iter>::difference_type n,
			const my_reverse_iterator<Iter>& it) {
				return (it.base() - n);
};

template< class Iter>
typename my_reverse_iterator<Iter>::difference_type
operator-(const ft::my_reverse_iterator<Iter>& lhs,
			const ft::my_reverse_iterator<Iter>& rhs) {
				return (rhs.base() - lhs->base());
};

template< class Iterator1, class Iterator2 >
bool operator==( const ft::my_reverse_iterator<Iterator1>& lhs,
				const ft::my_reverse_iterator<Iterator2>& rhs ) {
					return (lhs.base() == rhs.base());
};

template< class Iterator1, class Iterator2 >
bool operator!=( const ft::my_reverse_iterator<Iterator1>& lhs,
				const ft::my_reverse_iterator<Iterator2>& rhs ) {
					return (lhs.base() != rhs.base());
};

template< class Iterator1, class Iterator2 >
bool operator>( const ft::my_reverse_iterator<Iterator1>& lhs,
				const ft::my_reverse_iterator<Iterator2>& rhs ) {
					return (lhs.base() > rhs.base());
};

template< class Iterator1, class Iterator2 >
bool operator>=( const ft::my_reverse_iterator<Iterator1>& lhs,
				const ft::my_reverse_iterator<Iterator2>& rhs ) {
					return (lhs.base() >= rhs.base());
};

template< class Iterator1, class Iterator2 >
bool operator<( const ft::my_reverse_iterator<Iterator1>& lhs,
				const ft::my_reverse_iterator<Iterator2>& rhs ) {
					return (lhs.base() < rhs.base());
};

template< class Iterator1, class Iterator2 >
bool operator<=( const ft::my_reverse_iterator<Iterator1>& lhs,
				const ft::my_reverse_iterator<Iterator2>& rhs ) {
					return (lhs.base() <= rhs.base());
};

}
#endif