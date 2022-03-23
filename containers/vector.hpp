#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include <iterator>

template < class T, class Allocator = std::allocator<T> >
class	vector {
	public :
		typedef T								value_type;
		typedef Allocator						allocator_type;
		// typedef typename value_type&			reference;
		// typedef typename value_type& const	const_reference;
		// typedef typename value_type*			pointer;
		// typedef typename value_type* const	const_pointer;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename std::random_access_iterator_tag		iterator;	// need to use mine
		typedef typename std::random_access_iterator_tag		const_iterator;
		typedef typename std::reverse_iterator<iterator>		reverse_iterator;
		typedef typename std::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef typename std::ptrdiff_t							difference_type;
		typedef  size_t									size_type;


	/****************************/
	/*	Constructors/Destructor	*/
	/****************************/
		// Default
		explicit vector(const allocator_type& alloc = allocator_type())
						: _reserve(0)
		{
			(void)alloc;
			_array = 0;
			std::cout << "contstructeur par default " << this->_reserve << std::endl;
		};
		//	Fill
		explicit vector(size_type n,
						const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type())
						:  _size(n), _reserve(n)
		{
			_CpyAlloc = alloc; //! solution temporaire je pense
			try {_array = _CpyAlloc.allocate(n + 1);}
			catch(const std::bad_alloc& e) {
				std::cerr << e.what() << '\n';
				return ;
			}
			for (size_type i = 0; i < n; i++) {
				_CpyAlloc.construct((_array + i), val);
			}
			_array[n] = 0;
			std::cout << "addr _array : " << _array << std::endl;
		};
		// Range
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
	/*			Overcharge		*/
	/****************************/
		vector& operator=(const vector& x)
		{
			std::cout << "operator = used " << x.size()  << std::endl;
			// if this has content ==> destroy
			// assign x to this
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
		size_type	capacity() const {return this->_reserve;}

	/****************************/
	/*			El access		*/
	/****************************/


	/****************************/
	/*			Modifiers		*/
	/****************************/


	/****************************/
	/*			Allocator		*/
	/****************************/

	/****************************/
	/*			Non-member		*/
	/****************************/


		T*			_array;
	private:
		allocator_type	_CpyAlloc;
		size_type	_size;
		size_type	_reserve;
		// iterator 	_begin;
		// iterator 	_end;
		// iterator 	_end_reserve;
};


#endif