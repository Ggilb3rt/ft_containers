#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <iostream>
#include <memory>


// map se classe par rapport à key

namespace ft {

template <class T>
struct	BST_node {
	public:
		typedef T	value_type;

		value_types	key;
		BST_node	*parent, *left, *right;

		BST_node() {};
};


}

#endif