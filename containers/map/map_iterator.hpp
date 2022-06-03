#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include <cstddef>
#include "../utils/iterators_traits.hpp"

namespace ft {

template <typename T, typename Node, class Distance = ptrdiff_t,
			class Pointer = T*, class Reference = T&>
class map_iterator {
	public :
		typedef T									value_type;
		typedef Distance							difference_type;
		typedef Pointer								pointer;
		typedef Reference							reference;
		typedef std::bidirectional_iterator_tag		iterator_category;	// use std to be compatible with real containers
		typedef Node *								node_ptr;

		map_iterator() : _current(NULL), _root(NULL), _nil(NULL) {}
		map_iterator(node_ptr current, node_ptr root, node_ptr nil) : _current(current), _root(root), _nil(nil) {}
		map_iterator(const map_iterator &rhs) : _current(rhs._current), _root(rhs._root), _nil(rhs._nil) {}
		virtual ~map_iterator() {}

		map_iterator operator= (const map_iterator& rhs) {
			if (this == &rhs)
				return *this;
			this->_current = rhs._current;
			this->_root = rhs._root;
			this->_nil = rhs._nil;
			return *this;
		}

		const pointer &base() const {return _minimum(this->_root);} //? private

		reference operator*() const {return this->_current->data;}
		pointer operator->() const {return &(this->operator*());}

		map_iterator& operator++() {
			this->_current = this->_next(this->_current);
			return *this;
		}
		map_iterator operator++(int) {
			map_iterator tmp = *this;
			this->_current = this->_next(this->_current);
			return tmp;
		}
		map_iterator& operator--() {
			if (this->_current == this->_nil)
				this->_current = this->_maximum(this->_root);
			else
				this->_current = this->_prev(this->_current);
			return *this;
		}
		map_iterator operator--(int) {
			map_iterator tmp = *this;
			if (this->_current == this->_nil)
				this->_current = this->_maximum(this->_root);
			else
				this->_current = this->_prev(this->_current);
			return tmp;
		}
		
		operator map_iterator<const value_type, Node>() const {
			return map_iterator<const value_type, Node>(this->_current, this->_root, this->_nil);
		}

		node_ptr _current;

	private:
		node_ptr _root;
		node_ptr _nil;

		node_ptr	_minimum(node_ptr current) {
			while (current->left != this->_nil)
				current = current->left;
			return current;
		}
		node_ptr	_maximum(node_ptr current) {
			while (current->right != this->_nil)
				current = current->right;
			return current;
		}
		node_ptr	_next(node_ptr current) {
			if (current->right != this->_nil)
				return _minimum(current->right);
			node_ptr	parent = current->parent;
			while (parent != this->_nil && current == current->parent->right) {
				current = parent;
				parent = parent->parent;
			}
			return parent;
		}
		node_ptr	_prev(node_ptr current) {
			if (current->left != this->_nil)
				return _maximum(current->left);
			node_ptr	parent = current->parent;
			while (parent != this->_nil && current == current->parent->left) {
				current = parent;
				parent = parent->parent;
			}
			return parent;
		}
};

template <typename T, typename Node>
bool operator== (const map_iterator<T, Node> lhs,
			const map_iterator<T, Node> rhs) {
		return lhs._current == rhs._current;
};

// const
template <typename T_L, typename T_R, typename Node>
bool operator== (const map_iterator<T_L, Node> lhs,
			const map_iterator<T_R, Node> rhs) {
		return lhs._current == rhs._current;
};


template <typename T, typename Node>
bool operator!= (const map_iterator<T, Node> lhs,
			const map_iterator<T, Node> rhs) {
		return lhs._current != rhs._current;
};

// const
template <typename T_L, typename T_R, typename Node>
bool operator!= (const map_iterator<T_L, Node> lhs,
			const map_iterator<T_R, Node> rhs) {
		return lhs._current != rhs._current;
};

}
#endif