#ifndef reverse_iterator_HPP
#define reverse_iterator_HPP

#include <cstddef>
#include "iterators_traits.hpp"
#include "vector_iterator.hpp"

namespace ft {

template <typename Iter>
class reverse_iterator {
	public :
		typedef Iter													iterator_type;
		typedef typename ft::iterator_traits<Iter>::value_type			value_type;
		typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iter>::pointer				pointer;
		typedef typename ft::iterator_traits<Iter>::reference			reference;
		typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;

		reverse_iterator() : current() {}
		reverse_iterator(iterator_type x) : current(x) {} // must be explicit
		template <class U>
		reverse_iterator(const reverse_iterator<U>& other) : current(other.base()) {}

		virtual ~reverse_iterator() {}

		iterator_type base() const {return current;}

		reference	operator*() const {iterator_type tmp = current; return *(--tmp);}
		pointer		operator->() const {return &(operator*());}

		reverse_iterator&	operator++() {--current; return *this;} 
		reverse_iterator	operator++(int) {
			reverse_iterator tmp = *this;
			++(*this);
			return tmp;
		} 
		reverse_iterator&	operator--() {++current; return *this;} 
		reverse_iterator	operator--(int) {
			reverse_iterator tmp = *this;
			--(*this);
			return tmp;
		}

		reverse_iterator& operator+=(difference_type const & rhs) {current -= rhs; return *this;}
		reverse_iterator& operator-=(difference_type const & rhs) {current += rhs; return *this;}
		reverse_iterator operator+(difference_type n) const { return reverse_iterator(this->base()-n);}
		reverse_iterator operator-(difference_type n) const { return reverse_iterator(this->base()+n);}

		reference operator[](difference_type n) const {return this->base()[-n-1];}

	protected :
		iterator_type    current;
};

template <class Iter>
reverse_iterator<Iter>
operator+(typename reverse_iterator<Iter>::difference_type n,
			const reverse_iterator<Iter>& it) {
				return (it - n);
};

template< class Iter>
typename reverse_iterator<Iter>::difference_type
operator-(const reverse_iterator<Iter>& lhs,
			const reverse_iterator<Iter>& rhs) {
				return (rhs.base() - lhs->base());
};

template< class Iter_L, class Iter_R>
typename reverse_iterator<Iter_L>::difference_typ
operator-(const reverse_iterator<Iter_L>& lhs,
			const reverse_iterator<Iter_R>& rhs) {
				return (rhs.base() - lhs->base());
};

template< class Iterator1, class Iterator2 >
bool operator==( const ft::reverse_iterator<Iterator1>& lhs,
				const ft::reverse_iterator<Iterator2>& rhs ) {
					return (lhs.base() == rhs.base());
};

template< class Iterator1, class Iterator2 >
bool operator!=( const ft::reverse_iterator<Iterator1>& lhs,
				const ft::reverse_iterator<Iterator2>& rhs ) {
					return (lhs.base() != rhs.base());
};

template< class Iterator1, class Iterator2 >
bool operator>( const ft::reverse_iterator<Iterator1>& lhs,
				const ft::reverse_iterator<Iterator2>& rhs ) {
					return (lhs.base() > rhs.base());
};

template< class Iterator1, class Iterator2 >
bool operator>=( const ft::reverse_iterator<Iterator1>& lhs,
				const ft::reverse_iterator<Iterator2>& rhs ) {
					return (lhs.base() >= rhs.base());
};

template< class Iterator1, class Iterator2 >
bool operator<( const ft::reverse_iterator<Iterator1>& lhs,
				const ft::reverse_iterator<Iterator2>& rhs ) {
					return (lhs.base() < rhs.base());
};

template< class Iterator1, class Iterator2 >
bool operator<=( const ft::reverse_iterator<Iterator1>& lhs,
				const ft::reverse_iterator<Iterator2>& rhs ) {
					return (lhs.base() <= rhs.base());
};

}
#endif