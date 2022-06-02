#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <cstddef>
#include <iterator>

#include "./red_black_tree.hpp"
#include "./enable_if.hpp"
#include "./is_integral.hpp"
#include "./pair.hpp"
#include "./equal.hpp"
#include "./lexicographical_compare.hpp"

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
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
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

	private:
		typedef red_black_tree<value_type, allocator_type, value_compare>	rb_tree_type;
		typedef typename rb_tree_type::node_type							node_type;

	public:
		typedef typename rb_tree_type::iterator						iterator;
		typedef typename rb_tree_type::const_iterator				const_iterator;
		typedef typename rb_tree_type::reverse_iterator				reverse_iterator;
		typedef typename rb_tree_type::const_reverse_iterator		const_reverse_iterator;

	private:
		allocator_type		_cpyAlloc;
		key_compare			_cpyComp;
		value_compare		_cpyValueComp;
		rb_tree_type		_rb_tree;
		size_type			_size;

	public:
		// Default
		explicit map (const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type())
						: _cpyAlloc(alloc), _cpyComp(comp), _cpyValueComp(comp), _rb_tree(_cpyAlloc, _cpyComp), _size(0)
					{};
		// Range
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
				: _cpyAlloc(alloc), _cpyComp(comp), _cpyValueComp(comp), _rb_tree(_cpyAlloc, _cpyComp), _size(0)
				{
					this->insert(first, last);
				};
		// Copy
		map (const map& x) : _cpyAlloc(x._cpyAlloc), _cpyComp(x._cpyComp), _cpyValueComp(x._cpyValueComp), _rb_tree(_cpyAlloc, _cpyComp), _size(0) {
			if (this != &x) {
				this->insert(x.begin(), x.end());
			}
		};

		~map() {};

		map&	operator= (const map& x) {
			if (this != &x) {
				this->clear();
				this->insert(x.begin(), x.end());
				this->_size = x.size();
			}
			return *this;
		};

	/****************************/
	/*			Iterators		*/
	/****************************/
		iterator				begin() {return _rb_tree.begin();}
		const_iterator			begin() const {return _rb_tree.begin();}
		iterator				end() {return _rb_tree.end();}
		const_iterator			end() const {return _rb_tree.end();}

		//TODO tester que le reverse_it ne permette pas l'utilisation de random_access
		reverse_iterator		rbegin() {return reverse_iterator(this->end());}
		const_reverse_iterator	rbegin() const {return reverse_iterator(this->end());}
		reverse_iterator		rend() {return reverse_iterator(this->begin());}
		const_reverse_iterator	rend() const {return reverse_iterator(this->begin());}

	/****************************/
	/*			Capacity		*/
	/****************************/
		bool		empty() const {return !this->_size;}
		size_type	size() const {return this->_size;}
		size_type	max_size() const {return this->_rb_tree.max_size();}


	/****************************/
	/*		Element access		*/
	/****************************/
		mapped_type&	operator[] (const key_type& k) {
			return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
		}

	/****************************/
	/*			Modifiers		*/
	/****************************/
		pair<iterator, bool>	insert(const value_type& val) {
			iterator	exist = this->_rb_tree.search(val);
			if (exist != this->_rb_tree.get_nil_it())
				return ft::make_pair<iterator, bool> (exist, false);
			this->_size++;
			exist = _rb_tree.insert(val);
			return ft::make_pair<iterator, bool> (exist, true);
		}
		//! need to use position
		iterator	insert(iterator position, const value_type& val) {
			(void)position;

			iterator	exist = this->_rb_tree.search(val);
			if (exist != this->_rb_tree.get_nil_it())
				return exist;
			this->_size++;
			return _rb_tree.insert(val);
		}
		template <class InputIterator>
		void	insert (InputIterator first, InputIterator last){
			while (first != last) {
				this->insert(*first);
				++first;
			}
		}

		void	erase(iterator position) {
			if (position != this->end()) {
				_rb_tree.delete_el(position);
				this->_size--;
			}
		}
		size_type	erase(const key_type& k) {
			iterator	finding = this->find(k);
			if (finding == this->end())
				return 0;
			this->erase(this->find(k));
			return 1;
		}
		void		erase(iterator first, iterator last) {
			iterator	tmp;
			while (first != last) {
				tmp = first;
				++first;
				this->erase(tmp);
			}
		}


		//! need to test leaks on linux
		void	swap(map& x) {
			size_type		tmp_size = this->size();
			this->_rb_tree.swap(x._rb_tree);
			this->_size = x.size();
			x._size = tmp_size;
		}

		void	clear() {
			_rb_tree.clear_all();
			this->_size = 0;
		}

	/****************************/
	/*			Observers		*/
	/****************************/
		key_compare		key_comp() const {return _cpyComp;}
		value_compare	value_comp() const {return _cpyValueComp;}

	/****************************/
	/*			Operations		*/
	/****************************/
		iterator	find(const key_type& k) {
			value_type	p = ft::make_pair(k, mapped_type());
			return this->_rb_tree.search(p);
		}
		const_iterator	find(const key_type& k) const {
			value_type	p = ft::make_pair(k, mapped_type());
			return this->_rb_tree.search(p);
		}

		size_type	count(const key_type& k) const {return (this->find(k) != this->_rb_tree.get_nil_it());}

		//! Need valgrind check on linux
		iterator	lower_bound(const key_type& k) {
			return _rb_tree.lower_bound(ft::make_pair(k, mapped_type()));
		}
		const_iterator	lower_bound(const key_type& k) const {
			return _rb_tree.lower_bound(ft::make_pair(k, mapped_type()));
		}

		iterator	upper_bound(const key_type& k) {
			return _rb_tree.upper_bound(ft::make_pair(k, mapped_type()));
		}
		const_iterator	upper_bound(const key_type& k) const {
			return _rb_tree.upper_bound(ft::make_pair(k, mapped_type()));
		}

		ft::pair<iterator, iterator>	equal_range(const key_type& k) {
			return	ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
		}
		ft::pair<const_iterator, const_iterator>	equal_range(const key_type& k) const {
			return	ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
		}

	/****************************/
	/*			Allocator		*/
	/****************************/
		allocator_type	get_allocator() const {return this->_cpyAlloc;}
};

	/****************************/
	/*			Non-member		*/
	/****************************/
template <class Key, class T, class Compare, class Alloc>
bool operator==(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) {
	if (lhs.size() != rhs.size())
		return false;
	typename ft::map<Key, T, Compare, Alloc>::const_iterator	first = lhs.begin();
	typename ft::map<Key, T, Compare, Alloc>::const_iterator	last = lhs.end();
	if (!(ft::equal(lhs.begin(), lhs.end(), rhs.begin()))) {
		return false;
	}
	return true;
}

template <class Key, class T, class Compare, class Alloc>
bool operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
	return !(lhs == rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class Key, class T, class Compare, class Alloc>
bool operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
	return !(rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
	return rhs < lhs;
}

template <class Key, class T, class Compare, class Alloc>
bool operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
	return !(lhs < rhs);
}

template <class Key, class T, class Compare, class Alloc>
void	swap(map<Key, T, Compare, Alloc>&x, map<Key, T, Compare, Alloc>& y) {
	x.swap(y);
}

}
#endif