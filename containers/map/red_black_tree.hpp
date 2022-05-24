#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

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
class red_black_tree
{

	public:
		typedef T						value_type;
		typedef Alloc					alloc;
		typedef node<value_type>		node_type;

	public:
		red_black_tree() : _root(NULL) {};
		~red_black_tree() {this->clear(_root);};

		node_type	*get_root() {return _root;};


		void		insert(value_type val) {
			_root = rb_insert_in_tree(this->get_root(), val, NULL);
			this->rb_insert_fixup(this->_last_add);
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
			tmp->color = parent == NULL ? BLACK : RED;
			// tmp->color = RED;
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

		node_type	*get_parent(node_type *current) {
			if (current->parent)
				return current->parent;
			// std::cout << "get parent " << current->data << std::endl;
			return NULL;
		}

		node_type	*get_grandParent(node_type *current) {
			return this->get_parent(this->get_parent(current));
		}

		node_type	*get_uncle(node_type *current) {
			if (this->get_parent(current) && this->get_parent(current) == this->get_grandParent(current)->left)
				return this->get_grandParent(current)->right;
			else if (this->get_parent(current) && this->get_parent(current) == this->get_grandParent(current)->right)
				return this->get_grandParent(current)->left;
			return NULL;
		}

		bool	is_left_grand_parent(node_type *current) {
			if (this->get_parent(current) == this->get_grandParent(current)->left)
				return true;
			return false;
		}

		bool	is_left_parent(node_type *current) {
			if (current == this->get_parent(current)->left)
				return true;
			return false;
		}



		// ADD

		node_type *rb_insert_in_tree(node_type *current, value_type val, node_type *parent) {
			if (current == NULL)
				return (newNode(val, parent));
			if (val <= current->data) // = pas forcement necessaire si clef unique
				current->left = rb_insert_in_tree(current->left, val, current);
			else if (val > current->data)
				current->right = rb_insert_in_tree(current->right, val, current);
			return current;
		};

		void	rb_insert_fixup(node_type *z) {
			while (z && z->color == RED && this->get_parent(z)->color == RED) {
				if (this->is_left_grand_parent(z)) {
					node_type	*y = get_uncle(z);					// uncle right
					
					if (y && y->color == RED) {						// case 1
						this->get_parent(z)->color = BLACK;
						y->color = BLACK;
						this->get_grandParent(z)->color = RED;
						z = this->get_grandParent(z);
						// std::cout << "Uncle is red (case 1)" << std::endl;
					}
					else {
						if (!is_left_parent(z)) {			// case 2
							z = this->get_parent(z);
							rotate_left(z);
						// std::cout << "Case 2" << std::endl;
						}
						this->get_parent(z)->color = BLACK;					// case 3
						this->get_grandParent(z)->color = RED;
						rotate_right(this->get_grandParent(z));
						// std::cout << "Case 3" << std::endl;
					}
				}
				else {											// same but switch left and right
					node_type	*y = get_uncle(z);	// uncle left
					if (y && y->color == RED) {						// case 1
						this->get_parent(z)->color = BLACK;
						y->color = BLACK;
						this->get_grandParent(z)->color = RED;
						z = this->get_grandParent(z);
						// std::cout << "new z " << z->data << std::endl;
					}
					else {
						if (is_left_parent(z)) {			// case 2
							z = this->get_parent(z);
							rotate_right(z);
						}
						this->get_parent(z)->color = BLACK;					// case 3
						this->get_grandParent(z)->color = RED;
						rotate_left(this->get_grandParent(z));
					}
				}
				this->_root->color = BLACK;
			}
		}




		// REMOVE

		void	clear(node_type *current) {
			if (current->right)
				clear(current->right);
			if (current->left)
				clear(current->left);
			this->_CpyAlloc.destroy(current);
			this->_CpyAlloc.deallocate(current, 1);
		};

		void	rb_transplant(node_type *to_replace, node_type *to_put) {
			if (this->get_parent(to_replace) == NULL)
				this->_root = to_put;
			else if (is_left_parent(to_replace))
				to_replace->parent->left = to_put;
			else
				get_parent(to_replace)->right = to_put;
			if (to_put)
				to_put->parent = to_replace->parent;
		}

		public:
		node_type	*tree_minimum(node_type *current) {
			if (current->left)
				return tree_minimum(current->left);
			return current;
		}

		void	rb_delete(node_type *z) {
			node_type	*x = NULL;
			node_type	*y = z;
			bool		y_original_color = y->color;

			if (z->left == NULL) {
				x = z->right;
				rb_transplant(z, z->right);
			}
			else if (z->right == NULL) {
				x = z->left;
				rb_transplant(z, z->left);
			}
			else {
				y = tree_minimum(z->right);
				y_original_color = y->color;
				x = y->right;
				if (this->get_parent(y) == z)
					x->parent = y;
				else {
					rb_transplant(y, y->right);
					y->right = z->right;
					y->parent->right = y;
				}
				rb_transplant(z, y);
				y->left = z->left;
				y->parent->left = y;
				y->color = z->color;
			}
			if (y_original_color == BLACK)
				rb_delete_fixup(x);
		}

		void	rb_delete_fixup(node_type *x) {
			std::cout << "delete fixup with " << x->data << std::endl; 
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