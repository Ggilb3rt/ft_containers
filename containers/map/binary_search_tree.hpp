#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <iostream>
#include <memory>

#include <vector>


// map se classe par rapport à data

namespace ft {

#define	BLACK 1
#define	RED 0

template <class T>
struct	node {

	public:
		typedef T	value_type;

		value_type		data;
		node			*parent, *left, *right;
		bool			color : 1;
		

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


		void		insert(value_type val) {
			_root = insert_in_tree(this->get_root(), val, NULL);
			this->rb_insert_fixup(this->search(val));
		};
		node_type	*search(value_type val) {
			return search_in_tree(this->_root, val);
		}


		void	print(node_type *current) {
			if (current->right)
				print(current->right);
			if (current->left)
				print(current->left);
			std::cout << current->data << " | color : " << current->color << std::endl;
		};

		void	print_node(node_type *node, char name) {
			std::cout << std::endl << "\tprint " << name << " " << &(*node) << std::endl
			<< "data : " << node->data << "\tparent : " << node->parent << std::endl
			<< "left : " << node->left << "\tright : " << node->right
			<< std::endl << std::endl;
		}


	private:
		node_type	*_root;
		node_type	*_last_add;
		alloc		_CpyAlloc;

		node_type *newNode(value_type val, node_type *parent) {
			node_type	*tmp;

			tmp = _CpyAlloc.allocate(1);
			_CpyAlloc.construct(tmp, val);
			tmp->parent = parent;
			tmp->left = NULL;
			tmp->right = NULL;
			// tmp->color = parent == NULL ? BLACK : RED;
			tmp->color = RED;
			this->_last_add = tmp;

			return tmp;
		};

		node_type	*search_in_tree(node_type *current, value_type val) {
			if (current == NULL)
				return NULL;
			if (val == current->data)
				return current;
			else if (val < current->data)
				return search_in_tree(current->left, val);
			else
				return search_in_tree(current->right, val);
		};

		node_type *insert_in_tree(node_type *current, value_type val, node_type *parent) {
			if (current == NULL)
				return (newNode(val, parent));
			if (val <= current->data) // = pas forcement necessaire si clef unique
				current->left = insert_in_tree(current->left, val, current);
			else if (val > current->data)
				current->right = insert_in_tree(current->right, val, current);
			return current;
		};

		void	rb_insert_fixup(node_type *z) {
			// std::cout << tree_depth(_root) << std::endl;

			//! need to add getter for parent, grand parent and uncle
			if (tree_depth(_root) >= 2) {
				while (z != this->_root && z->parent->color == RED) {
					if (z->parent == z->parent->parent->left) {
						node_type	*y = z->parent->parent->right;	// uncle
						
						if (y && y->color == RED) {						// case 1
							z->parent->color = BLACK;
							y->color = BLACK;
							z->parent->parent->color = RED;
							z = z->parent->parent;
						}
						else if (z == z->parent->right) {			// case 2
							z = z->parent;
							rotate_left(z);
						}
						//! cette condition empeche le segfault mais empeche aussi le fonctionnement normal
						if (z != this->_root && z != this->_root->left && z != this->_root->right) {
							z->parent->color = BLACK;					// case 3
							z->parent->parent->color = RED;
							rotate_right(z->parent->parent);
						}
					}
					else {											// same but switch left and right
						node_type	*y = z->parent->parent->left;	// uncle
						
						if (y && y->color == RED) {						// case 1
							z->parent->color = BLACK;
							y->color = BLACK;
							z->parent->parent->color = RED;
							z = z->parent->parent;
						}
						else if (z == z->parent->left) {			// case 2
							z = z->parent;
							rotate_right(z);
						}
						//! cette condition empeche le segfault mais empeche aussi le fonctionnement normal
						if (z != this->_root && z != this->_root->left && z != this->_root->right) {
							z->parent->color = BLACK;					// case 3
							z->parent->parent->color = RED;
							rotate_left(z->parent->parent);
						}
					}
				}
			}
			this->_root->color = BLACK;
		}

		void	clear(node_type *current) {
			if (current->right)
				clear(current->right);
			if (current->left)
				clear(current->left);
			this->_CpyAlloc.destroy(current);
			this->_CpyAlloc.deallocate(current, 1);
		};


	// public: //temporaire


		size_t	tree_depth(node_type *el, size_t depth = 0, size_t max_depth = 0) {
			// Do not works
			if (el != NULL && el->right)
				return tree_depth(el->right, depth + 1, (depth > max_depth ? depth : max_depth));
			if (el != NULL && el->left)
				return tree_depth(el->left, depth + 1, (depth > max_depth ? depth : max_depth));
			// std::cout << "depth " << depth << " | max " << max_depth << std::endl;
			return (depth > max_depth ? depth : max_depth);
		}

		// ROTATIONS

		bool	is_child_left(node_type *current) {
			if (current->parent->left == current)
				return true;
			return false;
		}

		/*
				p					p
				|					|
				X					Y
			   / \		==>		   / \
			  a	  Y				  X	  c
			  	 / \			 / \
				b   c			a	b
		*/
		void	rotate_left(node_type *x) {
			node_type	*y = x->right;

			if (y == NULL)
				return ;
			x->right = y->left;
			if (y->left) {
				y->left->parent = x;
				y->left = NULL;	// needed ?
			}
			y->parent = x->parent;
			if (x->parent == NULL)
				this->_root = y;
			else if (is_child_left(x))
				x->parent->left = y;
			else
				x->parent->right = y;
			x->parent = y;
			y->left = x;
		}

		/*
				p					p
				|					|
				X					Y
			   / \				   / \
			  Y   a				  b   X
			 / \					 / \
			b   c					c   a
		*/
		void	rotate_right(node_type *x) {
			node_type	*y = x->left;
			// node_type	*a, *b, *c, *p;

			if (y == NULL)
				return ;
			x->left = y->right;				//			p
			if (y->right) {					//			|
				y->right->parent = x;		//		Y	X
				// x->left = y->right;		//	   /   / \		//
				y->right = NULL;			//	  b	  c   a
			}
			y->parent = x->parent;
			if (x->parent == NULL)
				this->_root = y;
			else if (is_child_left(x))
				x->parent->left = y;
			else 
				x->parent->right = y;
			x->parent = y;
			y->right = x;
		}

		void	rotate_left_right(node_type *z) {
			this->rotate_left(z->left);
			this->rotate_right(z);
		}

		void	rotate_right_left(node_type *z) {
			this->rotate_right(z->right);
			this->rotate_left(z);
		}


		// Display Tree
		#include "./map_display.hpp"

};


}

#endif