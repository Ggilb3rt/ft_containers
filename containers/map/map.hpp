#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <cstddef>
#include <iterator>

#include "./red_black_tree.hpp"
#include "../utils/enable_if.hpp"
#include "../utils/is_integral.hpp"
#include "../utils/pair.hpp"

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
						: _cpyAlloc(alloc), _cpyComp(comp), _size(0)
					{ (void)comp; };
		// Range
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = NULL)
				: _cpyAlloc(alloc), _cpyComp(comp)
				{
					(void)first;
					(void)last;
				};
		// Copy
		map (const map& x) : _cpyAlloc(x.alloc) {};

		~map() {};

		map&	operator= (const map& x) {
			// clear(this)
			// insert(copy from x)
			this->_size = x.size();

			return *this;
		};

	/****************************/
	/*			Iterators		*/
	/****************************/
		iterator		begin() {return this->_rb_tree->get_first();}
		const_iterator	begin() const {return this->_rb_tree->get_first();}
		iterator		end() {return this->_rb_tree->get_last();}
		const_iterator	end() const {return this->_rb_tree->get_last();}

		reverse_iterator		rbegin() {return this->end();}
		const_reverse_iterator	rbegin() const {return this->end();}
		reverse_iterator		rend() {return this->begin();}
		const_reverse_iterator	rend() const {return this->begin();}

	/****************************/
	/*			Capacity		*/
	/****************************/
		bool		empty() const {return this->_size;}
		size_type	size() const {return this->_size;}
		size_type	max_size() const {return this->_cpyAlloc.max_size();}


	/****************************/
	/*		Element access		*/
	/****************************/
		mapped_type&	operator[] (const key_type& k) {
			(void)k;
			// if search(k)
				// return k.value
			// else
				// return (*((this->insert(make_pair(k,mapped_type()))).first)).second;
			return ;
		}

	/****************************/
	/*			Modifiers		*/
	/****************************/
		void	erase(iterator position) {
			(void)position;
			this->_size--;
		}
		size_type	erase(const key_type& k) {
			this->_rb_tree->rb_delete(k);
			this->_size--;
			
			return 1;							//? ", the function returns the number of elements erased.", always 1 ?
		}
		void		erase(iterator first, iterator last) {
			size_type	diff = std::distance(first, last);
			
			while (first < last) {
				this->_rb_tree->rb_delete(first);
				first++;
			}
			this->_size -= diff;
		}

		void	swap(map& x) {
			value_type*	tmp_rb_tree = this->_rb_tree;
			size_type	tmp_size = this->size();

			this->_rb_tree = x._rb_tree;
			this->_size = x.size();
			x._rb_tree = tmp_rb_tree;
			x._size = tmp_size;
		}

		void	clear() {
			this->_rb_tree->clear();
			this->_size = 0;
		}

	/****************************/
	/*			Observers		*/
	/****************************/
		key_compare		key_comp() const {return key_compare();}		//???
		value_compare	value_comp() const {return value_compare();}	//???

	/****************************/
	/*			Operations		*/
	/****************************/
		size_type	count(const key_type& k) const {
			if (this->_rb_tree->search(k))
				return 1;
			else
				return 0;
		}

	/****************************/
	/*			Allocator		*/
	/****************************/
		allocator_type	get_allocator() const {return this->_cpyAlloc;}

	private:
		allocator_type	_cpyAlloc;
		key_compare		_cpyComp;
		value_type*		_rb_tree;
		size_type		_size;
};





}


#endif