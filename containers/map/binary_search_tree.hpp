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
		typedef T						value_type;
		typedef Alloc					alloc;
		typedef node<value_type>		node_type;

	public:
		binary_search_tree() : _root(NULL) {};
		~binary_search_tree() {this->clear(_root);};

		node_type	*get_root() {return _root;};

		node_type *newNode(value_type val, node_type *parent) {
			node_type	*tmp;

			tmp = _CpyAlloc.allocate(1);
			_CpyAlloc.construct(tmp, val);
			tmp->parent = parent;
			return tmp;
		};

		void		insert(value_type val) {
			_root = insert_in_tree(this->get_root(), val, NULL);
			// this->balance();
		};

		void	print(node_type *current) {
			if (current->right)
				print(current->right);
			if (current->left)
				print(current->left);
			std::cout << current->get_data() << std::endl;
		};


	private:
		node_type	*_root;
		alloc				_CpyAlloc;

		node_type *insert_in_tree(node_type *current, value_type val, node_type *parent) {
			if (current == NULL)
				return (newNode(val, parent));
			if (val <= current->data) // = pas forcement necessaire si clef unique
				current->left = insert_in_tree(current->left, val, current);
			else if (val > current->data)
				current->right = insert_in_tree(current->right, val, current);
			return current;
		};

		void	clear(node_type *current) {
			if (current->right)
				clear(current->right);
			if (current->left)
				clear(current->left);
			this->_CpyAlloc.destroy(current);
			this->_CpyAlloc.deallocate(current, 1);
		};
};


}

#endif