#ifndef STACK_HPP
#define STACK_HPP

#include "../vector/vector.hpp"

namespace ft {

template < class T, class Container = ft::vector<T> >
class stack {
	public :
		typedef	T			value_type;
		typedef	Container	container_type;
		typedef	size_t		size_type;

		template <class fT, class fContainer>
		friend bool ft::operator== (const stack<fT, fContainer>& lhs, const stack<fT, fContainer>& rhs);
		template <class fT, class fContainer>
		friend bool ft::operator< (const stack<fT, fContainer>& lhs, const stack<fT, fContainer>& rhs);

		explicit stack(const container_type& ctnr = container_type()) : array(ctnr) {};
		~stack() {};

		stack&	operator=(const stack& other) {array = other.array; return *this;};

		bool				empty() const {return this->array.empty();}
		size_type			size() const {return this->array.size();}
		value_type&			top() {return this->array.back();}
		const value_type&	top() const {return this->array.back();}
		void				push(const value_type& val) {this->array.push_back(val);}
		void				pop() {this->array.pop_back();}

	protected :
		container_type	array;
};


template <class T, class Container>
bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
	return lhs.array == rhs.array;
};

template <class T, class Container>
bool operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
	return lhs.array < rhs.array;
};

template <class T, class Container>
bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
	return !(lhs == rhs);
};

template <class T, class Container>
bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
	return (lhs < rhs || lhs == rhs);
};

template <class T, class Container>
bool operator> (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
	return rhs < lhs;
};

template <class T, class Container>
bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
	return (rhs < lhs || lhs == rhs);
};

}

#endif