#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <iostream>
#include <memory>


// map se classe par rapport à data

namespace ft {

template <class T>
struct	node {
	public:
		typedef T	value_type;

		value_type		data;
		node			*parent, *left, *right;

		node(value_type val) : data(val), parent(NULL), left(NULL), right(NULL) {};
		node(value_type val, node *parent) : data(val), parent(parent), left(NULL), right(NULL) {};
		~node() {};

		value_type	get_data() {return this->data;};

};


template <class T, class Alloc = std::allocator<node<T> > >
class binary_search_tree
{
	public:
		typedef T		value_type;
		typedef Alloc	alloc;

	private:
		node<value_type>	*_root;
		alloc				_CpyAlloc;

	public:
		binary_search_tree() : _root(NULL) {};
		~binary_search_tree() {_CpyAlloc.destroy(_root); _CpyAlloc.deallocate(_root, 1);};

		node<value_type> *newNode(value_type val) {
			_root = _CpyAlloc.allocate(1);
			_CpyAlloc.construct(_root, val);

			return _root;
		};

		node<value_type> *insert(node<value_type> *current, value_type val) {
			if (current == NULL)
				return (newNode(val));
			if (val <= current->data)
				current->left = insert(current->left, val);
			else if (val > current->data)
				current->right = insert(current->right, val);
			return current;
		};

		void	print() {
			std::cout << _root->get_data() << std::endl;
		};

		node<value_type>	*get_root() {return _root;};
};


}

#endif