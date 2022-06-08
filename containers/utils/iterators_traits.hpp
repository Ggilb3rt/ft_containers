#ifndef ITERATORS_TRAITS_HPP
#define ITERATORS_TRAITS_HPP

namespace ft {

template<typename _Iterator>
struct iterator_traits {
	typedef typename _Iterator::iterator_category iterator_category;
	typedef typename _Iterator::value_type        value_type;
	typedef typename _Iterator::difference_type   difference_type;
	typedef typename _Iterator::pointer           pointer;
	typedef typename _Iterator::reference         reference;
};

template <class T>
struct iterator_traits<T*> {
	typedef T								value_type;
	typedef std::ptrdiff_t					difference_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef std::random_access_iterator_tag	iterator_category;
};

template <class T>
struct iterator_traits<const T*> {
	typedef T								value_type;
	typedef std::ptrdiff_t					difference_type;
	typedef const T*						pointer;
	typedef const T&						reference;
	typedef std::random_access_iterator_tag	iterator_category;
};

}
#endif