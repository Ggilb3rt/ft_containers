#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <cstddef>
#include <iterator>
#include "vector_iterator.hpp"
#include "reverse_iterator.hpp"
#include "is_integral.hpp"
#include "enable_if.hpp"
#include "lexicographical_compare.hpp"
#include "equal.hpp"


// to remove
// #include <algorithm>

namespace ft {

template < class T, class Allocator = std::allocator<T> >
class	vector {
	public :
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef ft::random_access_iterator<value_type>				iterator;
		typedef ft::random_access_iterator<const value_type>		const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		typedef typename std::ptrdiff_t						difference_type;
		typedef size_t										size_type;


	/****************************/
	/*	Constructors/Destructor	*/
	/****************************/
		// Default
		explicit vector(const allocator_type& alloc = allocator_type())
						: _CpyAlloc(alloc), _size(0), _reserve(0)
		{
			try {_array = _CpyAlloc.allocate(this->_reserve);}
			catch(const std::bad_alloc& e) {
				std::cerr << e.what() << std::endl;
				return ;
			}
		};
		//	Fill
		explicit vector(size_type n,
						const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type())
						: _CpyAlloc(alloc), _size(n), _reserve(n)
		{
			try {_array = _CpyAlloc.allocate(n);}
			catch(const std::bad_alloc& e) {
				std::cerr << e.what() << std::endl;
				return ;
			}
			for (size_type i = 0; i < n; i++) {
				_CpyAlloc.construct((_array + i), val);
			}
		};
		// Range
		template <class InputIterator>
		vector(InputIterator first,
				InputIterator last,
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
				: _CpyAlloc(alloc)
		{
			try {
				_size = std::distance(first, last);
				_reserve = _size;
				_array = _CpyAlloc.allocate(this->_size);}
			catch(const std::bad_alloc& e) {
				std::cerr << e.what() << std::endl;
				return ;
			}
			catch(const std::exception& e) {
				std::cerr << e.what() << std::endl;
				return ;
			}
			InputIterator	firstCpy = first;
			size_type		i = 0;
			while (firstCpy != last) {
				_CpyAlloc.construct((_array + i), *firstCpy);
				firstCpy++;
				i++;
			}
		};
		// Copy
		vector(const vector& cpy)
			: _CpyAlloc(cpy.get_allocator()), _size(0), _reserve(0)
		{
			try {_array = _CpyAlloc.allocate(this->_size);}
			catch(const std::bad_alloc& e) {
				std::cerr << e.what() << std::endl;
				return ;
			}
			this->assign(cpy.begin(), cpy.end());
		};
		// Destructor
		~vector()
		{
			//use .clear() ?
			if (_array) {
				for (size_type i = 0; i < _size; i++) {
					_CpyAlloc.destroy((_array + i));
				}
					_CpyAlloc.deallocate(_array, _reserve);
			}
		};


	/****************************/
	/*	Operator overcharge		*/
	/****************************/
		vector& operator=(const vector& x)
		{

			this->clear();
			this->insert(this->begin(), x.begin(), x.end());
			return *this;
		}

		value_type& operator[](const unsigned int index){return this->_array[index];}


	/****************************/
	/*			Iterators		*/
	/****************************/
		// iterator			begin() {return this->empty() ? iterator() : iterator(&_array[0]);}
		// const_iterator	begin() const {return this->empty() ? const_iterator() : const_iterator(&_array[0]);}
		// iterator			end() {return this->empty() ? iterator() : iterator(&_array[this->_size]);}
		// const_iterator	end() const {return this->empty() ? const_iterator() : const_iterator(&_array[this->_size]);}
		iterator			begin() {return _array;}
		const_iterator		begin() const {return _array;}
		iterator			end() {return this->empty() ? this->begin() : &_array[this->_size];}
		const_iterator		end() const {return this->empty() ? this->begin() : &_array[this->_size];}
		
		reverse_iterator	rbegin() {return reverse_iterator(this->end());}
		reverse_iterator	rend() {return reverse_iterator(this->begin());}


	/****************************/
	/*			Capacity		*/
	/****************************/
		size_type	size() const {return this->_size;}
		size_type	max_size() const {return this->_CpyAlloc.max_size();} //? throw() dans la definition, pourquoi ? 
		void		resize(size_type n, value_type val = value_type()) {
			if (n < _size) {
				for (size_type i = n; i < _size; i++) {
					_CpyAlloc.destroy((_array + i));
				}
			}
			if (n > _reserve * 2) {
				this->reserve(n);
			}
			if (n > _size) {
				for (size_type i = _size; i < n; i++) {
					push_back(val);
					// _CpyAlloc.construct((_array + i), val);
				}
			}
			_size = n;
		}
		size_type	capacity() const {return this->_reserve;}
		bool		empty() const {return this->_size == 0 ? true : false;}
		void		reserve(size_type n) {
			if (n > this->max_size())
				throw std::length_error("vector::reserve");
			else if (n > this->capacity()) {
				allocator_type	tmpAlloc;
				T*				tmpArray;
				try {
					tmpArray = tmpAlloc.allocate(n);
					for (size_type i = 0; i < _size; i++) {
						tmpAlloc.construct((tmpArray + i), _array[i]);
						_CpyAlloc.destroy((_array + i));
					}
					this->_CpyAlloc.deallocate(this->_array, this->_reserve);
					this->_CpyAlloc = tmpAlloc;
					this->_array = tmpArray;
					this->_reserve = n;
				}
				catch(const std::exception& e) {std::cerr << e.what() << std::endl;}
			}
			// n < capacity ==> nothing
		}



	/****************************/
	/*			El access		*/
	/****************************/
		reference	at(size_type n) {
			if (n >= this->_size)
			{
				std::stringstream ss;
				ss << "vector::_M_range_check: __n (which is " << n
					<< ") >= this->size() (which is " << this->size()
					<< ")";
				throw std::out_of_range(ss.str());
			}
			return this->_array[n];
		}
		const_reference	at(size_type n) const{
			if (n >= this->_size)
			{
				std::stringstream ss;
				ss << "vector::_M_range_check: __n (which is " << n
					<< ") >= this->size() (which is " << this->size()
					<< ")";
				throw std::out_of_range(ss.str());
			}
			return this->_array[n];
		}
		reference	front() {return (this->_array[0]);}
		const_reference	front() const{return (this->_array[0]);}
		reference	back() { return (this->_array[this->_size - 1]);}
		const_reference	back() const{ return (this->_array[this->_size - 1]);}



	/****************************/
	/*			Modifiers		*/
	/****************************/
		template <class InputIterator>
		void	assign(InputIterator first, InputIterator last, 
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL) {
			difference_type newSize = std::distance(first, last);

			this->clear();
			if (this->capacity() < (size_type)newSize)
				this->reserve(newSize);
			while (first != last) {
				this->push_back(*first);
				first++;
			}
		}
		void	assign(size_type n, const value_type& val) {
			this->clear();
			if (this->capacity() < n)
				this->reserve(n);
			while (n > 0) {
				this->push_back(val);
				n--;
			}
		}
		void	push_back(const value_type& val) {
			if (_size >= _reserve)
				this->reserve((_size == 0) ? (1) : (_size * 2));
			_CpyAlloc.construct(&_array[_size], val);
			this->_size++;
		}
		void	pop_back() {
			if (this->_size > 0) {
				_CpyAlloc.destroy((_array + _size - 1));
				this->_size--;
			}
		}
		iterator insert(iterator position, const value_type& val) {
			size_type		start_pos = std::distance(this->begin(), position);

			this->insert(position, 1, val);
			return this->begin() + start_pos;
		}

		void insert(iterator position, size_type n, const value_type& val) {
			if (n == 0)
				return ;
			ft::vector<value_type>	tmp(*this);
			size_type				start_pos = std::distance(this->begin(), position);
			iterator				tmp_position = tmp.begin() + start_pos;

			if (_size + n >= _reserve * 2)
				this->reserve(_size + n);
			else if (_size + n >= _reserve)
				this->reserve(_size * 2);

			this->assign(tmp.begin(), tmp_position);
			while (n-- > 0) {
				this->push_back(val);
			}
			for (iterator it = tmp_position; it < tmp.end(); it++)
				this->push_back(*it);
		}

		template <class InputIterator>
		typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type
			insert(iterator position, InputIterator first, InputIterator last) {
					size_type				n = std::distance(first, last);
					if (n == 0)
						return ;
					ft::vector<value_type>	tmp(*this);
					size_type				start_pos = std::distance(this->begin(), position);
					iterator				tmp_position = tmp.begin() + start_pos;
					
					if (_size + n >= _reserve * 2)
						this->reserve(_size + n);
					else if (_size + n >= _reserve)
						this->reserve(_size * 2);

					this->assign(tmp.begin(), tmp_position);
					while (first < last) {
						this->push_back(*first);
						first++;
					}
					for (iterator it = tmp_position; it < tmp.end(); it++)
						this->push_back(*it);
		}
		iterator	erase(iterator position) {
			erase(position, position + 1);
			return position;
		}
		iterator	erase(iterator first, iterator last) {
			// iterator		firstCpy = first;
			// size_type	start = std::distance(this->begin(), first);
			// size_type	end = std::distance(this->begin(), last);
			// size_type	itsDist = std::distance(first, last);

			// while (start < end) {
			// 	this->_CpyAlloc.destroy(this->_array + start);
			// 	if ((last != this->end()) && ((start + itsDist) < this->size()))
			// 		this->_CpyAlloc.construct(this->_array + start, *(first + start + itsDist));
			// 	start++;
			// }
			// while (last != this->end()) {
			// 	this->_CpyAlloc.destroy(this->_array + start);
			// 	start++;
			// 	last++;
			// }
			// this->_size -= itsDist;
			
			iterator		firstBase = first;
			size_type		n = std::distance(first, last);

			if (n == 0)
				return firstBase;
			while (last < this->end()) {
				*first = *last;
				first++;
				last++;
			}
			while (n > 0) {
				this->_CpyAlloc.destroy(this->_array + _size - n);
				n--;
			}
			this->_size -= std::distance(first, last);



			// iterator		firstBase = first;
			// iterator		end = this->end();

			// while (first != last) {
			// 	_CpyAlloc.destroy((_array + (first - this->begin())));
			// 	first++;
			// 	this->_size--;
			// }
			// // first = firstBase;
			// difference_type n = std::distance(this->begin(), firstBase);
			// while (last != end) {
			// 	_CpyAlloc.construct((this->_array + n), *last);
			// 	// *first = *last;
			// 	last++;
			// 	// first++;
			// 	n++;
			// }
			return firstBase;
		}
		void	swap(vector& x) {
			// cf iterator validity : l'iterator pointe vers la meme adrss apres le swap
			// cf complexity : constant ==> must only swap pointer to data and size
			T*			tmpArray = this->_array;
			size_type	tmpSize = this->_size;
			size_type	tmpReserve = this->_reserve;

			this->_array = x._array;
			this->_size = x._size;
			this->_reserve = x._reserve;
			x._array = tmpArray;
			x._size = tmpSize;
			x._reserve = tmpReserve;
		}
		void	clear() {
			for (size_type i = 0; i < this->_size; i++)
				_CpyAlloc.destroy((_array + i));
			this->_size = 0;
		}


	/****************************/
	/*			Allocator		*/
	/****************************/
		allocator_type	get_allocator() const {return this->_CpyAlloc;}


		void	_print(void) {
			std::cout << "[ ";
			for (iterator it = this->begin(); it < this->end(); it++)
				std::cout << *it << ", ";
			std::cout << "]" << std::endl;
		}
	private:
		value_type*			_array;
		allocator_type	_CpyAlloc;
		size_type	_size;
		size_type	_reserve;

};

	/****************************/
	/*			Non-member		*/
	/****************************/
	template <class T, class Alloc>
	bool operator==(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		typename ft::vector<T>::const_iterator	first = lhs.begin();
		typename ft::vector<T>::const_iterator	last = lhs.end();
		if (!(ft::equal(lhs.begin(), lhs.end(), rhs.begin()))) {
			return false;
		}
		return true;
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return rhs < lhs;
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	void	swap(vector<T,Alloc>&x, vector<T,Alloc>& y) {
		x.swap(y);
	}

} // end namespace ft

#endif