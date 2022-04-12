#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <stdexcept>
#include <memory>
#include <cstddef>
#include <iterator>
#include "myIterator.hpp"

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
		// typedef typename std::random_access_iterator_tag		iterator;	// need to use mine
		typedef MyIterator<std::random_access_iterator_tag, T>	iterator;
		typedef typename std::random_access_iterator_tag		const_iterator;
		typedef typename std::reverse_iterator<iterator>		reverse_iterator;
		typedef typename std::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef typename std::ptrdiff_t							difference_type;
		typedef size_t											size_type;

	/****************************/
	/*	Constructors/Destructor	*/
	/****************************/
		// Default
		explicit vector(const allocator_type& alloc = allocator_type())
						: _size(0), _reserve(0)
		{
			_CpyAlloc = alloc;
			try {_array = _CpyAlloc.allocate(this->_reserve);}
			catch(const std::exception& e) {
				std::cerr << e.what() << std::endl;
				return ;
			}
			std::cout << "contstructeur par default, reserve : " << this->_reserve << std::endl;
		};
		//	Fill
		// use is_integral()
		explicit vector(size_type n,
						const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type())
						:  _size(n), _reserve(n)
		{
			_CpyAlloc = alloc;
			try {_array = _CpyAlloc.allocate(n);} //? n + 1 pour avoir un element vide a la fin ?
			catch(const std::bad_alloc& e) {
				std::cerr << e.what() << std::endl;
				return ;
			}
			for (size_type i = 0; i < n; i++) {
				_CpyAlloc.construct((_array + i), val);
			}
			//_array[n] = 0;
			std::cout << "addr _array : " << _array << std::endl;
		};
		// Range
		// use is_enable()
		// template <class InputIterator>
		// vector(InputIterator first,
		// 				InputIterator last,
		// 				const allocator_type& alloc = allocator_type())
		// 		{
		// 			(void)first; (void)last; (void)alloc;
		// 			std::cout << "Constuctor range" << std::endl;
		// 		};
		// Copy
		vector(const vector& cpy)
		{
			(void)cpy;
			std::cout << "Constructor copy" << std::endl;
		};
		~vector()
		{
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
			std::cout << "operator = used " << x.size()  << std::endl;
			// if this has content ==> destroy
			// assign x to this
		}

		value_type& operator[](const unsigned int index)
		{
			if (index >= this->_size || this->_size == 0)
				throw vector::BadIndexException();	// pas bon, devrait return une valeur par default cf std::vector
			return this->_array[index];
		}
	/****************************/
	/*			Iterators		*/
	/****************************/
		iterator	begin() {return iterator(&_array[0]);} // pas terminé, doit check si vide
		iterator	end() {return iterator(&_array[this->_size]);}

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


	/****************************/
	/*			Modifiers		*/
	/****************************/
		// si push depasse _reserve la realocation fait un *2 (cf exemple std::vector::reserve)
		void	push_back(const value_type& val) {
			//std::cout << ((_size <= 1) ? (_size + 1) : (_size * 2)) << std::endl;
			// std::cout << "\tIn push_back " << val << " | " << _size << " | " << _reserve << std::endl;
			if (_size >= _reserve)
				this->reserve((_size <= 1) ? (_size + 1) : (_size * 2));
			//std::cout << ((_size <= 1) ? (_size + 1) : (_size * 2)) << std::endl;
			//std::cout << "value : " << val << std::endl;
			_CpyAlloc.construct(&_array[_size], val); // j'aimerai utiliser this->end()
			this->_size++;
		}

	/****************************/
	/*			Allocator		*/
	/****************************/

	/****************************/
	/*			Non-member		*/
	/****************************/



	/****************************/
	/*			Exceptions		*/
	/****************************/
	class	BadIndexException : public std::exception {
			public:
				virtual const char * what() const throw() {
					return ("Invalid index");
					}
	};

	private:
		T*			_array;
		allocator_type	_CpyAlloc;
		size_type	_size;
		size_type	_reserve;
		// iterator 	_begin;
		// iterator 	_end;
		// iterator 	_end_reserve;
};

} // end namespace ft

#endif