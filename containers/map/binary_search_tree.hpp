#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <iostream>
#include <memory>


// map se class par rapport à key
// fait ft::pair<> avant

namespace ft {

template <class T>
struct	s_node {
		T		_key;
		struct	s_node *_left, *_right;
};

// struct s_node	*createNode();

// }


#endif