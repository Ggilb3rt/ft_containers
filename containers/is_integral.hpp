#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

template<class T, T v>
struct	integral_constant {
	static const T value = v;
	typedef T	value_type;
	typedef integral_constant<T,v> type;
	operator T() const {return v;}
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

template <class T>
struct	is_integral : integral_constant{
	operator T() const {
		return true_type;
	}
};

#endif