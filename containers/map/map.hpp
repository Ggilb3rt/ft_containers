#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <cstddef>
#include <iterator>

#include "pair.hpp"
#include "../utils/enable_if.hpp"
#include "../utils/is_integral.hpp"

#include <map>

namespace ft {

template < class Key, class T, class Compare = std::less<Key>,
			class Alloc = std::allocator<pair<const Key, T> > >
class	map
{
	public:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef pair<const Key, T>							value_type;
		typedef Compare										key_compare;
		// typedef value_comp()								value_compare;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename std::map<key_type, value_type>::iterator						iterator;
		typedef typename std::map<key_type, value_type>::iterator						const_iterator;
		typedef std::reverse_iterator<iterator>				reverse_iterator;
		typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;
		typedef typename std::ptrdiff_t						difference_type;
		typedef size_t										size_type;

		class value_compare : std::binary_function<value_type, value_type, bool>
		{	// in C++98, it is required to inherit binary_function<value_type,value_type,bool>
			friend class map<key_type, mapped_type, key_compare, Alloc>;

			protected:
				Compare comp;
				value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object

			public:
				typedef bool result_type;
				typedef value_type first_argument_type;
				typedef value_type second_argument_type;
				bool operator() (const value_type& x, const value_type& y) const
				{
					return comp(x.first, y.first);
				}
		};


		// Default
		explicit map (const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type())
						: _cpyAlloc(alloc)
					{ (void)comp; };
		// Range
		// template <class InputIterator>
		// map (InputIterator first, InputIterator last,
		// 		const key_compare& comp = key_compare(),
		// 		const allocator_type& alloc = allocator_type(),
		// 		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = NULL)
		// 		: _cpyAlloc(alloc), _cpyComp(comp)
		// 		{};
		// Copy
		map (const map& x) : _cpyAlloc(x.alloc) {};

		~map() {};




	private:
		allocator_type	_cpyAlloc;
		key_compare		_cpyComp;
		value_type*		_root;
};





}


#endif