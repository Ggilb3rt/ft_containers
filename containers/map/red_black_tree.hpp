#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <iostream>
#include <memory>
#include "map_iterator.hpp"
#include "../utils/reverse_iterator.hpp"

// Use for print tree
// #include <vector>

namespace ft {

#define	BLACK 1
#define	RED 0

template <class T>
struct	node {

	public:
		typedef T	value_type;

		value_type		data;
		bool			color : 1;
		node			*parent, *left, *right;
		
		node(void) : data(value_type()), color(RED), parent(NULL), right(NULL), left(NULL) {};
		node(value_type val) : data(val), color(RED), parent(NULL), left(NULL), right(NULL) {};
		node(value_type val, node *parent) : data(val), color(RED), parent(parent), left(NULL), right(NULL) {};
		node(value_type val, bool color, node *parent, node *left, node *right)
			: data(val), color(color), parent(parent), left(left), right(right) {};
		~node() {};

		value_type	get_data() {return this->data;};
};


template <class T, class Alloc, typename Compare = std::less<T> >
class red_black_tree
{
	public:
		typedef T											value_type;
		typedef node<value_type>							node_type;
		typedef map_iterator<value_type, node_type>			iterator;
		typedef map_iterator<const value_type, node_type>	const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		typedef typename Alloc::template rebind<node<value_type> >::other	alloc;
		typedef Compare										compare_type;
		typedef size_t										size_type;

		red_black_tree(alloc const &allocator = alloc(), compare_type const &compare = compare_type())
						: _CpyAlloc(allocator), _compare(compare) {
			_nil = _CpyAlloc.allocate(1);
			_CpyAlloc.construct(_nil, node_type(
				value_type(), BLACK, this->_nil, this->_nil, this->_nil));
			_root = _nil;
			_last_add = _nil;
		};
		~red_black_tree() {
			if (this->_root != this->_nil)
				this->clear(this->_root);
			this->delete_node(this->_nil);
		};

		// GETTER
		iterator		begin() {return iterator(this->minimum(_root), _root, _nil);}
		const_iterator	begin() const {return const_iterator(this->minimum(_root), _root, _nil);}
		iterator		end() {return iterator(_nil, _root, _nil);}
		const_iterator	end() const {return const_iterator(_nil, _root, _nil);}
		node_type		*get_root() const {return _root;};
		iterator		get_root_it() {return iterator(_root, _root, _nil);}
		node_type		*get_nil() const {return _nil;};
		iterator		get_nil_it() {return iterator(_nil, _root, _nil);}
		const_iterator	get_nil_it() const {return const_iterator(_nil, _root, _nil);}
		size_type		max_size() const {return this->_CpyAlloc.max_size();}

		node_type	*minimum(node_type *current) const {
			while (current->left != this->_nil)
				current = current->left;
			return current;
		}
		node_type	*maximum(node_type *current) const {
			while (current->right != this->_nil)
				current = current->right;
			return current;
		}
		// MODIFIER
		iterator	insert(value_type val, iterator hint) {
			rb_insert(newNode(val), hint);
			return iterator(this->_last_add, this->_root, this->_nil);
		};
		void		clear_all() {
			this->clear(this->_root);
			this->_root = this->_nil;
		}
		void		delete_el(node_type* val) {
			rb_delete(val);
		}
		void		delete_el(iterator &val) {
			rb_delete(val._current);
		}
		iterator		search(value_type const &val) {
			node_type	*find = search_in_tree(this->_root, val);
			return iterator(find, this->_root, this->_nil);
		}
		const_iterator	search(value_type const &val) const {
			node_type	*find = search_in_tree(this->_root, val);
			return const_iterator(find, this->_root, this->_nil);
		}
		void	swap(red_black_tree &x) {
			node_type		*tmp_root = _root;
			node_type		*tmp_nil = _nil;
			node_type		*tmp_last = _last_add;
			_root = x._root;
			_nil = x._nil;
			_last_add = x._last_add;
			x._root = tmp_root;
			x._nil = tmp_nil;
			x._last_add = tmp_last;
		}
		iterator	lower_bound(value_type key) {
			iterator	it	= this->begin();
			iterator	itend = this->end();
			while (it != itend) {
				if (_compare(*it, key) == false)
					break;
				++it;
			}
			return it;
		}
		const_iterator	lower_bound(value_type key) const {
			const_iterator	it	= this->begin();
			const_iterator	itend = this->end();
			while (it != itend) {
				if (_compare(*it, key) == false)
					break;
				++it;
			}
			return it;
		}
		iterator	upper_bound(value_type key) {
			iterator	it	= this->begin();
			iterator	itend = this->end();
			while (it != itend) {
				if (_compare(key, *it) == true)
					break;
				++it;
			}
			return it;
		}
		const_iterator	upper_bound(value_type key) const {
			const_iterator	it	= this->begin();
			const_iterator	itend = this->end();
			while (it != itend) {
				if (_compare(key, *it) == true)
					break;
				++it;
			}
			return it;
		}

	private:
		node_type 		*_nil;
		node_type		*_root;
		node_type		*_last_add;
		alloc			_CpyAlloc;
		compare_type	_compare;

		node_type *newNode(value_type val = value_type()) {
			node_type	*tmp;
			tmp = _CpyAlloc.allocate(1);
			_CpyAlloc.construct(tmp, node_type(
				val, RED, this->_nil, this->_nil, this->_nil
			));
			this->_last_add = tmp;
			return tmp;
		}
		node_type	*search_in_tree(node_type *current, value_type val) const {
			if (current == this->_nil)
				return this->_nil;
			while (current != _nil) {
				if (_compare(val, current->data))
					current = current->left;
				else if (_compare(current->data, val))
					current = current->right;
				else
					break;
			}
			return current;
		};
		// ADD
		void	rb_insert(node_type *z, iterator hint) {
			node_type	*y = this->_nil;
			node_type	*x;

			if (hint._current == _nil
				&& _compare(z->data, hint._current->right->data)
				&& _compare(hint._current->left->data, z->data)
				&& !(_compare(z->data, hint._current->data) == false
					&& _compare(hint._current->data, z->data) == false))
				x = hint._current;
			else
				x = this->_root;
			while (x != this->_nil) {
				y = x;
				if (_compare(z->data, x->data))
					x = x->left;
				else
					x = x->right;
			}
			z->parent = y;
			if (y == this->_nil)
				this->_root = z;
			else if (_compare(z->data, y->data))
				y->left = z;
			else
				y->right = z;
			z->left = this->_nil;
			z->right = this->_nil;
			z->color = RED;
			rb_insert_fixup(z);
		}
		void	rb_insert_fixup(node_type *z) {
			node_type	*y = this->_nil;

			while (z->parent->color == RED) {
				if (z->parent == z->parent->parent->left) {
					y = z->parent->parent->right;
					if (y->color == RED) {
						z->parent->color = BLACK;
						y->color = BLACK;
						z->parent->parent->color = RED;
						z = z->parent->parent;
					}
					else {
						if (z == z->parent->right) {
							z = z->parent;
							rotate_left(z);
						}
						z->parent->color = BLACK;
						z->parent->parent->color = RED;
						rotate_right(z->parent->parent);
					}
				}
				else {
					y = z->parent->parent->left;
					if (y->color == RED) {
						z->parent->color = BLACK;
						y->color = BLACK;
						z->parent->parent->color = RED;
						z = z->parent->parent;
					}
					else {
						if (z == z->parent->left) {
							z = z->parent;
							rotate_right(z);
						}
						z->parent->color = BLACK;
						z->parent->parent->color = RED;
						rotate_left(z->parent->parent);
					}
				}
			}
			this->_root->color = BLACK;
		}

		// REMOVE
		void	delete_node(node_type *el) {
			this->_CpyAlloc.destroy(el);
			this->_CpyAlloc.deallocate(el, 1);
		}
		void	clear(node_type *current) {
			if (current == this->_nil)
				return ;
			if (current->right != this->_nil)
				clear(current->right);
			if (current->left != this->_nil)
				clear(current->left);
			delete_node(current);
		};
		void	rb_transplant(node_type *to_replace, node_type *to_put) {
			if (to_replace->parent == this->_nil)
				this->_root = to_put;
			else if (to_replace == to_replace->parent->left)
				to_replace->parent->left = to_put;
			else
				to_replace->parent->right = to_put;
			to_put->parent = to_replace->parent;
		}
		void	rb_delete(node_type *z) {
			node_type	*x = this->_nil;
			node_type	*y = z;
			bool		y_original_color = y->color;
			if (z->left == this->_nil) {
				x = z->right;
				rb_transplant(z, z->right);
			}
			else if (z->right == this->_nil) {
				x = z->left;
				rb_transplant(z, z->left);
			}
			else {
				y = minimum(z->right);
				y_original_color = y->color;
				x = y->right;
				if (y->parent == z)
					x->parent = y;
				else {
					rb_transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				rb_transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			};
			if (z != this->_nil)
				delete_node(z);
			if (y_original_color == BLACK)
				rb_delete_fixup(x);
		}
		void	rb_delete_fixup(node_type *x) {
			node_type	*w = this->_nil;
			while (x != this->_root && x->color == BLACK) {
				if (x == x->parent->left) {										// case 1
					w = x->parent->right;
					if (w->color == RED) {
						w->color = BLACK;
						x->parent->color = RED;
						rotate_left(x->parent);
						w = x->parent->right;
					}
					if (w->left->color == BLACK && w->right->color == BLACK) {	// case 2
						w->color = RED;
						x = x->parent;
					}
					else {
						if (w->right->color == BLACK) {							// case 3
							w->left->color = BLACK;
							w->color = RED;
							rotate_right(w);
							w = x->parent->right;
						}
						w->color = x->parent->color;							// case 4
						x->parent->color = BLACK;
						w->right->color = BLACK;
						rotate_left(x->parent);
						x = this->_root;
					}
				}
				else {
					w = x->parent->left;
					if (w->color == RED) {
						w->color = BLACK;
						x->parent->color = RED;
						rotate_right(x->parent);
						w = x->parent->left;
					}
					if (w->right->color == BLACK && w->left->color == BLACK) {	// case 2
						w->color = RED;
						x = x->parent;
					}
					else {
						if (w->left->color == BLACK) {							// case 3
							w->right->color = BLACK;
							w->color = RED;
							rotate_left(w);
							w = x->parent->left;
						}
						w->color = x->parent->color;							// case 4
						x->parent->color = BLACK;
						w->left->color = BLACK;
						rotate_right(x->parent);
						x = this->_root;
					}
				}
			}
			x->color = BLACK;
		}
		// ROTATIONS
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
			x->right = y->left;
			if (y->left != this->_nil)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == this->_nil)
				this->_root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
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
			x->left = y->right;
			if (y->right != this->_nil)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == this->_nil)
				this->_root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}
		// Display Tree
		// #include "./map_display.hpp"
};

}
#endif