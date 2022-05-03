#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

namespace ft {

//! ajouter remove const et remove volatile ??


template<class T, T v>
struct	integral_constant {
	static const T value = v;
	typedef T	value_type;
	typedef integral_constant<T,v> type;
	operator T() const {return v;}
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;


// Fundamental interal types
template<typename>
struct __is_integral_help : public false_type { };

template<>
struct __is_integral_help<bool> : public true_type { };

template<>
struct __is_integral_help<char> : public true_type { };

// template<>
// struct __is_integral_help<char16_t> : public true_type { };

// template<>
// struct __is_integral_help<char32_t> : public true_type { };

template<>
struct __is_integral_help<wchar_t> : public true_type { };

template<>
struct __is_integral_help<signed char> : public true_type { };

template<>
struct __is_integral_help<short int> : public true_type { };

template<>
struct __is_integral_help<int> : public true_type { };

template<>
struct __is_integral_help<long int> : public true_type { };

template<>
struct __is_integral_help<long long int> : public true_type { };

template<>
struct __is_integral_help<unsigned char> : public true_type { };

template<>
struct __is_integral_help<unsigned short int> : public true_type { };

template<>
struct __is_integral_help<unsigned int> : public true_type { };

template<>
struct __is_integral_help<unsigned long int> : public true_type { };

template<>
struct __is_integral_help<unsigned long long int> : public true_type { };


template <class T>
struct	is_integral : public __is_integral_help<T> { };

}

#endif