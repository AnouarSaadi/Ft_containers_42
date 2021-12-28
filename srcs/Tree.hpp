#ifndef TREE_HPP
# define TREE_HPP

# include <memory>
# include <iostream>
# include "Iterator.hpp"
# include "Utility.hpp"
# include <functional> // 
# include <algorithm>

# define BLACK 1
# define RED 0

namespace ft {

	// Template struct node
	template <class T>
	struct node {
		T		_data;
		node	*_right;
		node	*_left;
		node	*_parent;
		bool	_color;
		node() : _data(), _right(nullptr), _left(nullptr), _parent(nullptr), _color(BLACK) {}
		node(T data) : _data(data), _right(nullptr), _left(nullptr), _parent(nullptr), _color(BLACK)
		{}
	};

	// tree iterator
	template <class Iter, class T>
	class tree_iter : public iterator<std::bidirectional_iterator_tag,
							typename iterator_traits<T>::value_type>
	{
	public:
		typedef Iter iterator_type;
		typedef typename iterator_traits<T>::pointer pointer;
		typedef typename iterator_traits<T>::reference reference;
		typedef std::bidirectional_iterator_tag 	iterator_category;
		typedef std::ptrdiff_t difference_type;

	private:
		iterator_type _current;


	public:
		tree_iter() : _current()
		{
		}

		tree_iter(iterator_type _x) : _current(_x)
		{
		}
		
		template <class OthIter, class U>
		tree_iter(const tree_iter<OthIter, U>& _other) : _current(_other.base())
		{
		}

		template <class OthIter, class U>
		tree_iter& operator=(const tree_iter<OthIter, U>& _other)
		{
			this->_current = _other.base();
			return (*this);
		}

		~tree_iter()
		{
		}

		reference operator*() const
		{
			return _current->_data;
		}

		pointer operator->() const
		{
			return &(operator*());
		}

		tree_iter & operator++()
		{
			this->_current = successor(this->_current);
			return (*this);
		}

		tree_iter operator++(int)
		{
			tree_iter _tmp(*this);
			this->_current = successor(this->_current);
			return (_tmp);
		}

		tree_iter & operator--()
		{
			this->_current = predecessor(this->_current);
			// this->_current
			return (*this);
		}

		tree_iter operator--(int)
		{
			tree_iter _tmp(*this);
			this->_current = predecessor(this->_current);
			return (_tmp);
		}

		iterator_type base() const
		{
			return (this->_current);
		}

	private:
		iterator_type minimum(iterator_type _x) const
		{
			while (_x->_left != nullptr)
				_x = _x->_left;
			return (_x);
		}
		// Maximum
		iterator_type maximum(iterator_type _x) const
		{
			while (_x->_right != nullptr)
				_x = _x->_right;
			return (_x);
		}
		// Successor
		iterator_type successor(iterator_type _x)
		{
			if (_x->_right != nullptr)
				return (minimum(_x->_right));
			iterator_type _y = _x->_parent;
			while (_y != nullptr && _x == _y->_right)
			{
				_x = _y;
				_y = _y->_parent;
			}
			return (_y);
		}
		// Predecessor
		iterator_type predecessor(iterator_type _x)
		{
			if (_x->_left != nullptr)
				return (maximum(_x->_left));
			iterator_type _y = _x->_parent;
			while (_y != nullptr && _x == _y->_left)
			{
				_x = _y;
				_y = _y->_parent;
			}
			return (_y);
		}

	};

	template <class Iter, class T>
  	bool operator==(const tree_iter<Iter, T>& lhs, const tree_iter<Iter, T>& rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class Iter, class T>
	bool operator!=(const tree_iter<Iter, T>& lhs, const tree_iter<Iter, T>& rhs)
	{
		return !(lhs == rhs);
	}

	// Template class tree
	template <class T, class Compare, class Alloc>
	class tree
	{
	public:
		typedef T								value_type;
		typedef typename Alloc::pointer			pointer;
		typedef typename Alloc::const_pointer	const_pointer;
		typedef typename Alloc::reference		reference;
		typedef typename Alloc::const_reference	const_reference;
		typedef struct node<value_type>			node;
		typedef node*							node_pointer;
		typedef Compare							compare;
		typedef tree_iter<node_pointer, pointer> iterator;
		typedef tree_iter<node_pointer, const_pointer> const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename Alloc::template rebind<node>::other	allocate_type;

	private:
		node_pointer	_root;
		node_pointer	_end;

		allocate_type _alloc;
		compare _comp;

	public:
		tree(compare comp): _root(nullptr), _end(), _alloc(), _comp(comp)
		{
			_end = this->makenode();
		}

		tree(const tree& _oth) : _root(), _end(), _alloc(), _comp()
		{
			*this = _oth;
		}

		~tree()
		{
			this->clear();
			_alloc.destroy(this->_end);
			_alloc.deallocate(this->_end, 1);
		}

		void swap(tree& _x)
		{

			std::swap(this->_root, _x._root);
			std::swap(this->_end, _x._end);
			std::swap(this->_alloc , _x._alloc);
			std::swap(this->_comp, _x._comp);
		}

		void clear()
		{
			if (this->_root != nullptr)
				this->destroy(this->_root);
			this->_root = nullptr;
		}

		iterator begin()
		{
			return iterator(this->minimum(this->_root));
		}
		
		const_iterator begin() const
		{
			return const_iterator(this->minimum(this->_root));
		}

		iterator end()
		{
			return iterator(this->_end);
		}

		const_iterator end() const
		{
			return const_iterator(this->_end);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(this->end());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(this->end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(this->begin());
		}
		
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(this->begin());
		}

		// Search operation
		node_pointer find(const value_type& data) const
		{
			node_pointer _current = this->_root;
			while (_current != nullptr) {
				if (!_comp(_current->_data, data) && !_comp(data, _current->_data))
					break;
				_current = _comp(_current->_data, data) ? _current->_right : _current->_left;
			}
			return _current;
		}

		iterator lower_bound (const value_type& _value)
		{
			node_pointer _result = _end;
			node_pointer _r = this->_root;
			while (_r != nullptr)
			{
				if (!_comp(_r->_data, _value))
				{
					_result = _r;
					_r = _r->_left;
				}
				else
					_r = _r->_right;
			}
			return iterator(_result);
		}

		const_iterator lower_bound (const value_type& _value) const
		{
			node_pointer _result = _end;
			node_pointer _r = this->_root;
			while (_r != nullptr)
			{
				if (!_comp(_r->_data, _value))
				{
					_result = _r;
					_r = _r->_left;
				}
				else
					_r = _r->_right;
			}
			return const_iterator(_result);
		}

		iterator upper_bound (const value_type& _value)
		{
			node_pointer _result = _end;
			node_pointer _r = this->_root;
			while (_r != nullptr)
			{
				if (_comp(_value, _r->_data))
				{
					_result = _r;
					_r = _r->_left;
				}
				else
					_r = _r->_right;
			}
			return iterator(_result);
		}

		const_iterator upper_bound (const value_type& _value) const
		{
			node_pointer _result = _end;
			node_pointer _r = this->_root;
			while (_r != nullptr)
			{
				if (_comp(_value, _r->_data))
				{
					_result = _r;
					_r = _r->_left;
				}
				else
					_r = _r->_right;
			}
			return iterator(_result);
		}
	
		// Insertion operation
		void insert(value_type _data = value_type())
		{
			if (this->_root == nullptr)
			{
				this->_root = this->makenode(_data);
				_root->_parent = this->_end;
				this->_end->_left = this->_root;
				return ;
			}
			this->_end->_left = nullptr;
			_root->_parent = nullptr;
			if (find(_data) != nullptr)
				return ;
			node_pointer _new = this->makenode(_data);
			node_pointer _parent_ = nullptr;
			node_pointer _y = this->_root;
			while (_y != nullptr)
			{
				_parent_ = _y;
				_y = (_comp(_new->_data, _y->_data)) ? _y->_left : _y->_right;
				_new->_parent = _parent_;
			}
			if (_comp(_new->_data, _parent_->_data))
				_parent_->_left = _new;
			else
				_parent_->_right = _new;
			_new->_color = RED;
			this->treeBalanceAfterInsert(_new);
			this->_end->_left = this->_root;
			this->_root->_parent = this->_end;
		}
		// Delete operation
		void erase(value_type _data = value_type())
		{
			node_pointer _del;
			node_pointer _x;
			this->_end->_left = nullptr;
			this->_root->_parent = nullptr;
			if (!this->_root || (_del = this->find(_data)) == nullptr)
				return ;
			node_pointer _y = _del;
			bool _removed_col = _y->_color;
			if (_del->_left == nullptr)
			{
				_x = _del->_right;
				this->shift(_del, _del->_right);
				_alloc.destroy(_del);
				_alloc.deallocate(_del, 1);
			}
			else if (_del->_right == nullptr)
			{

				_x = _del->_left;
				this->shift(_del, _del->_left);
				_alloc.destroy(_del);
				_alloc.deallocate(_del, 1);
			}
			else
			{
				// std::cout << "case2: has two child" << std::endl;
				_y = successor(_del);
				// std::cout << "minimum: " << _y << std::endl;
				_removed_col = _y->_color;
				_x = _y->_right;
				if (_y->_parent != nullptr && _y->_parent == _del) // _y is direct child of delete node
				{
					// std::cout << "_y is direct child of delete node" << std::endl;
					_x->_parent = _y;
				}
				else
				{
					// std::cout << "_y is not direct child of delete node" << std::endl;
					this->shift(_y, _y->_right);
					_y->_right = _del->_right;
					_y->_right->_parent = _y;
				}
				this->shift(_del, _y);
				_y->_left = _del->_left;
				_y->_left->_parent = _y;
				_y->_color = _del->_color;
				_alloc.destroy(_del);
				_alloc.deallocate(_del, 1);
			}
			if (_removed_col == BLACK && _x != nullptr)
				this->treeBalanceAfterRemove(_x);
			if (this->_root != nullptr)
			{
				this->_end->_left = this->_root;
				this->_root->_parent = this->_end;
			}
		}

		// Minimum
		node_pointer minimum(node_pointer _x) const
		{
			while (_x->_left != nullptr)
				_x = _x->_left;
			return (_x);
		}
		// Maximum
		node_pointer maximum(node_pointer _x) const
		{
			while (_x->_right != nullptr)
				_x = _x->_right;
			return (_x);
		}
		// Successor
		node_pointer successor(node_pointer _x)
		{
			if (_x->_right != nullptr)
				return (minimum(_x->_right));
			node_pointer _y = _x->_parent;
			while (_y !=  nullptr && _x == _y->_right)
			{
				_x = _y;
				_y = _y->_parent;
			}
			return (_y);
		}
		// Predecessor
		node_pointer predecessor(node_pointer _x)
		{
			if (_x->_left != nullptr)
				return (maximum(_x->_left));
			node_pointer _y = _x->_parent;
			while (_y != nullptr && _x == _y->_left)
			{
				_x = _y;
				_y = _y->_parent;
			}
			return (_y);
		}

		private:
		// New node construction
		node_pointer makenode(value_type _data = value_type())
		{
			node_pointer _new = _alloc.allocate(1);
			_alloc.construct(_new, _data);
			return (_new);
		}

		// Insertion operation: rebalancing function
		void treeBalanceAfterInsert(node_pointer _fix_node)
		{
			while (_fix_node->_parent && _fix_node->_parent->_color == RED)
			{
				if (_fix_node->_parent == _fix_node->_parent->_parent->_left) // _fix_node _parent is _left child of grand_parent
				{
					// std::cout << "The _parent of new node is a _left child" << std::endl;
					node_pointer _sibling = _fix_node->_parent->_parent->_right; // _sibling of _fix_node
					if (_sibling != nullptr && _sibling->_color == RED) // case 1: _sibling is also red  as _parent and _fix_node
					{
						_fix_node->_parent->_color = BLACK;
						_sibling->_color = BLACK;
						_fix_node->_parent->_parent->_color = RED;
						_fix_node = _fix_node->_parent->_parent;
					}
					else // case 2: _sibling is black and _fix_node is the _right child //case 3: _sibling is black and _fix_node is the _left child
					{
						if (_fix_node == _fix_node->_parent->_right) // case 2
						{
							_fix_node = _fix_node->_parent;
							this->leftRotate(_fix_node);
						}
						_fix_node->_parent->_color = BLACK;
						_fix_node->_parent->_parent->_color = RED;
						this->rightRotate(_fix_node->_parent->_parent);
						break ;
					}
				}
				else // the _parent of _fix_node is _right child of grand_parent
				{
					node_pointer _sibling = _fix_node->_parent->_parent->_left;
					if (_sibling != nullptr && _sibling->_color == RED)
					{
						_fix_node->_parent->_color = BLACK;
						_sibling->_color = BLACK;
						_fix_node->_parent->_parent->_color = RED;
						_fix_node = _fix_node->_parent->_parent;
					}
					else
					{
						if (_fix_node == _fix_node->_parent->_left)
						{
							_fix_node = _fix_node->_parent;
							this->rightRotate(_fix_node);
						}
						_fix_node->_parent->_color = BLACK;
						_fix_node->_parent->_parent->_color = RED;
						this->leftRotate(_fix_node->_parent->_parent);
						break ;
					}
				}
			}
			this->_root->_color = BLACK;
		}

		// Rotation functions
		void leftRotate(node_pointer _x)
		{
			// std::cout << "---> _Left Rotate: " << _x << std::endl;
			node_pointer _y = _x->_right;
			_x->_right = _y->_left;
			if (_y->_left != nullptr)
				_y->_left->_parent = _x;
			_y->_parent = _x->_parent;
			if (_x->_parent == nullptr) // _x is _x
				this->_root = _y;
			else if (_x == _x->_parent->_left) // _x is _left child
				_x->_parent->_left = _y;
			else // _x is _right child
				_x->_parent->_right = _y;
			_y->_left = _x;
			_x->_parent = _y;
		}

		void rightRotate(node_pointer _x)
		{
			// std::cout << "---> _Right Rotate: " << _x << std::endl;
			node_pointer _y = _x->_left;
			_x->_left = _y->_right;
			if (_y->_right != nullptr)
				_y->_right->_parent = _x;
			_y->_parent = _x->_parent;
			if (_x->_parent == nullptr) // _x is _x
				this->_root = _y;
			else if (_x == _x->_parent->_right) // _x is _right child
				_x->_parent->_right = _y;
			else // _x is _left child
				_x->_parent->_left = _y;
			_y->_right = _x;
			_x->_parent = _y; 
		}

		void destroy(node_pointer _x)
		{
			if (_x != nullptr)
			{
				destroy(_x->_left);
				destroy(_x->_right);
				this->_alloc.destroy(_x);
				this->_alloc.deallocate(_x, 1);
			}
		}

		// shift function for shifting two nodes
		void shift(node_pointer _u, node_pointer _v)
		{
			if (_u->_parent == nullptr) // _u is root
				this->_root = _v;
			else if (_u == _u->_parent->_left) // _u is _left child
				_u->_parent->_left = _v;
			else // _u is _right child
				_u->_parent->_right = _v;
			if (_v != nullptr)
				_v->_parent = _u->_parent;
		}

		// Deletion operation: rebalacing
		void treeBalanceAfterRemove(node_pointer _x)
		{
			while (_x != this->_root && _x->_color == BLACK)
			{
				std::cout << "Rebalancing" << std::endl;
				if (_x && _x == _x->_parent->_left) // the node is a _left child
				{
					// std::cout << "case1: the node is a _left child" << std::endl;
					node_pointer _sibling = _x->_parent->_right;
					if (_sibling != nullptr && _sibling->_color == RED) // case 1: _sibling is Red.
					{
						_sibling->_color = BLACK;
						_x->_parent->_color = RED;
						this->leftRotate(_x->_parent);
						_sibling = _x->_parent->_right;
					}
					if (_sibling != nullptr && _sibling->_color == BLACK // case 2: _sibling is balck and both children are black too.
						&& _sibling->_left->_color == BLACK
						&& _sibling->_right->_color == BLACK)
					{
						_sibling->_color = RED;
						_x = _x->_parent;
					}
					else // case 3, 4 handling
					{
						if (_sibling->_right->_color == BLACK) // case 3
						{
							_sibling->_left->_color = BLACK;
							_sibling->_color = RED;
							this->rightRotate(_sibling);
							_sibling = _x->_parent->_right;
						}
						_sibling->_color = _x->_parent->_color;
						_x->_parent->_color = BLACK;
						_sibling->_right->_color = BLACK;
						this->leftRotate(_x->_parent);
						_x = this->_root;
					}
				}
				else // the node is a _right child
				{
					// symmetric
					// std::cout << "case1: the node is a _right child" << std::endl;
					node_pointer _sibling = _x->_parent->_left;
					if (_sibling != nullptr && _sibling->_color == RED)
					{
						_sibling->_color = BLACK;
						_x->_parent->_color = RED;
						this->rightRotate(_x->_parent);
						_sibling = _x->_parent->_left;
					}
					if (_sibling != nullptr && _sibling->_color == BLACK
						&& _sibling->_right->_color == BLACK
						&& _sibling->_left->_color == BLACK)
					{
						_sibling->_color = RED;
						_x = _x->_parent;
					}
					else
					{
						if (_sibling->_left->_color == BLACK)
						{
							_sibling->_right->_color = BLACK;
							_sibling->_color = RED;
							this->leftRotate(_sibling);
							_sibling = _x->_parent->_left;
						}
						_sibling->_color = _x->_parent->_color;
						_x->_parent->_color = BLACK;
						_sibling->_left->_color = BLACK;
						this->rightRotate(_x->_parent);
						_x = this->_root;
					}
				}
			}
			_x->_color = BLACK;
		}
	};// end tree class

} //end of namespace ft

#endif