#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

#include "is_integral.hpp"

template <bool Cond, class T = void>
struct	enable_if {};

template <class T>
struct enable_if<true, T> {
		typedef T	type;
};


// 1. the return type (bool) is only valid if T is an integral type:
template <class T>
typename enable_if<ft::is_integral<T>::value,bool>::type
  is_odd (T i) {return bool(i%2);}

// 2. the second template argument is only valid if T is an integral type:
template < class T,
           class = typename enable_if<ft::is_integral<T>::value>::type>
bool is_even (T i) {return !bool(i%2);}


#endif