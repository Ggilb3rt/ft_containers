#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <iostream>
#include <memory>


// map se class par rapport à key
// fait ft::pair<> avant

namespace ft {

template <class T>
struct	BST_node {
	public:
		typedef T	value_type;

		value_types	key;
		BST_node	*parent, *left, *right;
};

// struct s_node	*createNode();

// }

}

#endif