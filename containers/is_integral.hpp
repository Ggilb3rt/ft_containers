#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

template<class T, T v>
struct	integral_constant {
	static constexpr T	value = v;
	typedef T	value_type;
	typedef integral_constant<T,v> type;
	constexpr operator	T() {return v;}
};

template <class T>
struct	is_integral : integral_constant {

};

#endif