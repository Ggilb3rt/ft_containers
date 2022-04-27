#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <cstddef>
#include <iterator>
#include "myIterator.hpp"
#include "is_integral.hpp"
#include "enable_if.hpp"
#include "lexicographical_compare.hpp"


// to remove
// #include <algorithm>

namespace ft {

template < class T, class Allocator = std::allocator<T> >
class	vector {
	public :
		typedef T								value_type;
		typedef Allocator						allocator_type;
		// typedef value_type&			reference;
		// typedef value_type& const	const_reference;
		// typedef value_type*			pointer;
		// typedef value_type* const	const_pointer;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef MyIterator<ft::random_access_iterator_tag, T>	iterator;
		typedef MyIterator<ft::random_access_iterator_tag, T>	const_iterator;
		typedef typename std::reverse_iterator<iterator>		reverse_iterator;
		typedef typename std::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef typename std::ptrdiff_t							difference_type;
		typedef size_t											size_type;


	/****************************/
	/*	Constructors/Destructor	*/
	/****************************/
		// Default
		explicit vector(const allocator_type& alloc = allocator_type())
						: _CpyAlloc(alloc), _size(0), _reserve(0)
		{
			try {_array = _CpyAlloc.allocate(this->_reserve);}
			catch(const std::exception& e) {
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
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = NULL)
				: _CpyAlloc(alloc), _size(last - first), _reserve(last - first)
		{
			try {_array = _CpyAlloc.allocate(this->_size);}
			catch(const std::bad_alloc& e) {
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
		{
			// pas bon cette histoire
			*this = cpy;
		};
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
			for (iterator it = x.begin(); it != x.end(); it++)
				this->push_back(*it);
			return *this;
		}

		value_type& operator[](const unsigned int index){return this->_array[index];}


	/****************************/
	/*			Iterators		*/
	/****************************/
		iterator		begin() {return this->empty() ? iterator() : iterator(&_array[0]);}
		const_iterator	begin() const {return this->empty() ? iterator() : iterator(&_array[0]);}
		iterator		end() {return this->empty() ? iterator() : iterator(&_array[this->_size]);}
		const_iterator	end() const {return this->empty() ? iterator() : iterator(&_array[this->_size]);}
		// need reverse_iterators


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
			if (n > _size && n > _reserve) {
				this->reserve(n);
			}
			if (n > _size) {
				for (size_type i = _size; i < n; i++) {
					_CpyAlloc.construct((_array + i), val);
				}
			}
			_size = n;
		}
		size_type	capacity() const {return this->_reserve;}
		bool		empty() const {return this->_size == 0 ? true : false;}
		void		reserve(size_type n) {
			// std::cout << n <<  "| reserve start : " << this->capacity() << std::endl;
			if (n > this->max_size())
				throw std::length_error("vector::reserve");
			// n > capacity
			allocator_type	tmpAlloc;
			T*				tmpArray;
			if (n >= this->capacity()) {
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
			// std::cout << "reserve at the end " << this->_reserve << std::endl;
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
	typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type
		assign(InputIterator first, InputIterator last) {
		difference_type	newSize = last - first;

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
			this->reserve((_size <= 1) ? (_size + 1) : (_size * 2));
		_CpyAlloc.construct(&_array[_size], val); // j'aimerai utiliser this->end()
		this->_size++;
	}
	void	pop_back() {
		if (this->_size > 0) {
			_CpyAlloc.destroy((_array + _size - 1));
			this->_size--;
		}
	}
	iterator insert(iterator position, const value_type& val) {
		// iterators are wasted after reserve. need to get position before reserve()
		size_type	start_pos = &(*position) - &(*this->begin());
		value_type	tmp[] = {this->_array[start_pos], 0};
		this->_array[start_pos] = val;

		if (this->size() == this->capacity()){
			try {this->reserve(this->capacity() * 2);}
			catch(const std::exception& e) {std::cerr << e.what() << std::endl;}
		}
		this->_size++;

		short		btn = 0;
		size_type	end_pos = this->end() - this->begin();
		for (size_type i = start_pos + 1; i < end_pos; i++) {
			tmp[!btn] = this->_array[i];
			this->_array[i] = tmp[btn];
			if (i + 1 < end_pos)
				tmp[btn] = this->_array[i + 1];
			btn = !btn;
		}
		return position;
	}
	void insert(iterator position, size_type n, const value_type& val) {
		// need to put all data after position] to a new vector
		// get position in size_type
		// change capacity if size + n > current capacity ==> capacity = capacity + n
		// add val n times starting at position
		// copy all elements from new vector to old one
		size_type	start_pos = &(*position) - &(*this->begin());

		ft::vector<value_type>	save(position, this->end());
		if (this->size() + n >= this->capacity()) {
			try {this->reserve(this->capacity() + n);}
			catch(const std::exception& e) {std::cerr << e.what() << std::endl;}
		}
		this->_size += n;

		iterator	position_new((this->_array + start_pos));
		iterator	position_end((this->_array + start_pos + n));
		while (position_new != position_end) {
			*position_new = val;
			position_new++;
		}
		for (iterator saveIt = save.begin(); saveIt < save.end(); saveIt++) {
			*position_new = *saveIt;
			position_new++;
		}
	}
	template <class InputIterator>
	typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type
		insert(iterator position, InputIterator first, InputIterator last) {
			size_type	start_pos = &(*position) - &(*this->begin());
			size_type	n = &(*last) - &(*first);

			ft::vector<value_type>	save(position, this->end());
			if (this->size() + n >= this->capacity()) {
				try {this->reserve(this->capacity() + n);}
				catch(const std::exception& e) {std::cerr << e.what() << std::endl;}
			}
			this->_size += n;

			iterator	position_new((this->_array + start_pos));
			while (first < last) {
				*position_new = *first;
				position_new++;
				first++;
			}
			for (iterator saveIt = save.begin(); saveIt < save.end(); saveIt++) {
				std::cout << "position new : " << &(*position_new)
					<< " saveIt : " << &(*saveIt) << std::endl;
				*position_new = *saveIt;
				std::cout << "\tposition new : " << &(*position_new)
					<< " saveIt : " << &(*saveIt) << std::endl;
				position_new++;
			}
	}
	iterator	erase(iterator position) {
		_CpyAlloc.destroy((_array + (position - this->begin())));
		for (iterator i = position; i != this->end(); i++)
			*i = *(i + 1);
		this->_size--;
		return position;
	}
	iterator	erase(iterator first, iterator last) {
		iterator		firstCpy = first;
		iterator		end = this->end();

		while (first != last) {
			_CpyAlloc.destroy((_array + (first - this->begin())));
			first++;
			this->_size--;
		}
		first = firstCpy;
		while (last != end) {
			*first = *last;
			last++;
			first++;
		}
		return firstCpy;
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
		while (first != last) {
			if (*first != *last)
				return false;
			first++;
		}
		return true;
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
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