#ifndef TREE_HPP
# define TREE_HPP
# include <memory>
# include <iostream>
# include "Iterator.hpp"
# include "Utility.hpp"


# define BLACK 1
# define RED 0
typedef enum 
{
	INORDER,
	PREORDER,
	POSTORDER
} traversType;

namespace ft {

	// Template struct node
	template <class T>
	struct node {
		T		_data;
		node	*_right;
		node	*_left;
		node	*_parent;
		bool	_color;
		node(T data, node *end) : _data(data), _right(end), _left(end), _parent(end), _color(true)
		{}
	};

	// tree iterator
	template <class Tree, class Iter, class T>
	class tree_iter : public iterator<std::bidirectional_iterator_tag,
							typename iterator_traits<T>::value_type>
	{
	public:
		typedef Tree tree;
		typedef Iter iterator_type;
		typedef typename iterator_traits<T>::pointer pointer;
		typedef typename iterator_traits<T>::reference reference;
		typedef std::bidirectional_iterator_tag 	iterator_category;
		typedef std::ptrdiff_t difference_type;

	private:
		iterator_type _current;
		tree _tree;

	public:
		tree_iter() : _current(), _tree()
		{
		}

		tree_iter(iterator_type _x, tree _tr) : _current(_x), _tree(_tr)
		{
		}
		template <class OthTree, class OthIter, class U>
		tree_iter(const tree_iter<OthTree, OthIter, U>& _other) : _current(_other.base()), _tree(_other.getTree())
		{
		}

		template <class OthTree, class OthIter, class U>
		tree_iter& operator=(const tree_iter<OthTree, OthIter, U>& _other)
		{
			this->_current = _other.base();
			this->_tree = _other.getTree();
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
			this->_current = _tree->successor(this->_current);
			return (*this);
		}

		tree_iter operator++(int)
		{
			tree_iter _tmp(*this);
			this->_current = _tree->successor(this->_current);
			return (_tmp);
		}

		tree_iter & operator--()
		{
			this->_current = _tree->predecessor(this->_current);
			return (*this);
		}

		tree_iter operator--(int)
		{
			tree_iter _tmp(*this);
			this->_current = _tree->predecessor(this->_current);
			return (_tmp);
		}

		iterator_type base() const
		{
			return (this->_current);
		}

		tree getTree() const
		{
			return (this->_tree);
		}
	};

	template <class Tree, class Iter, class T>
  	bool operator==(const tree_iter<Tree, Iter, T>& lhs, const tree_iter<Tree, Iter, T>& rhs)
	{
		return (lhs.base() == rhs.base() && lhs.getTree() == rhs.getTree());
	}
	template <class Tree, class Iter, class T>
	bool operator!=(const tree_iter<Tree, Iter, T>& lhs, const tree_iter<Tree, Iter, T>& rhs)
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
		typedef node*							nodePtr;
		typedef Compare							compare;
		typedef tree*							treePtr;
		typedef typename Alloc::template rebind<node>::other	allocate_type;
		typedef tree_iter<treePtr, nodePtr, pointer> iterator;
		typedef tree_iter<treePtr, nodePtr, const_pointer> const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

	private:
		nodePtr	_root;
		nodePtr	_end;

		allocate_type _alloc;
		compare _comp;

	public:
		tree(compare comp): _root(), _end(), _alloc(), _comp(comp)
		{
			_end = this->makenode();
			this->_root = this->_end;
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

		void swap(const tree& _x)
		{
			std::swap(this->_root, _x._root);
			std::swap(this->_end, _x._end);
			std::swap(this->_alloc , _x._alloc);
			std::swap(this->_comp, _x._comp);
		}

		void clear()
		{
			if (this->_root != this->_end)
				this->destroy(this->_root);
		}

		// Search operation
		nodePtr find(const value_type& data)
		{
			nodePtr _current = this->_root;
			while (_current != this->_end) {
				if (_current->_data.first == data.first)
					break;
				_current = _comp(_current->_data, data) ? _current->_right : _current->_left;
			}
			return (_current);
		}
		// Insertion operation
		void insert(value_type _data = value_type())
		{
			if (this->_root == this->_end)
			{
				this->_root = this->makenode(_data);
				_root->_parent = this->_end;
				this->_end->_left = this->_root;
				return ;
			}
			if (find(_data) != _end)
				return ;
			nodePtr _new = this->makenode(_data);
			nodePtr _parentNode = this->_end;
			nodePtr _y = this->_root;
			while (_y != this->_end) // find the _new _parent
			{
				_parentNode = _y;
				_y = (_comp(_new->_data, _y->_data)) ? _y->_left : _y->_right; // must be replaced by Compare
				_new->_parent = _parentNode;
			}
			if (_comp(_new->_data, _parentNode->_data)) // must be replaced by Compare
				_parentNode->_left = _new;
			else
				_parentNode->_right = _new;
			_new->_color = RED;
			this->treeBalanceAfterInsert(_new);
		}
		// Delete operation
		void remove(value_type _data = value_type())
		{
			nodePtr _del;
			nodePtr _x;
			if (!this->_root || (_del = this->find(_data)) == this->_end)
				return ;
			nodePtr _y = _del;
			bool _col = _y->_color; // store the original _color of node to be delete
			if (_del->_left == this->_end)
			{
				// std::cout << "case1: has a _right child or no child" << std::endl;
				_x = _del->_right;
				this->shift(_del, _del->_right);
				_alloc.destroy(_del);
				_alloc.deallocate(_del, 1);
			}
			else if (_del->_right == this->_end)
			{
				// std::cout << "case1: has a _left child" << std::endl;
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
				_col = _y->_color;
				_x = _y->_right;
				if (_y->_parent == _del) // _y is direct child of delete node
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
			if (_col == BLACK)
				this->treeBalanceAfterRemove(_x);
		}

		// Iterators
		iterator begin()
		{
			return (iterator(this->minimum(this->_root), this));
		}

		iterator end()
		{
			return (iterator(this->_end, this));
		}

		const_iterator begin() const
		{
			return (const_iterator(this->minimum(this->_root), this));
		}
		
		const_iterator end() const
		{
			return (const_iterator(this->_end, this));
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(this->end());
		}
		

		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(this->end()));
		}
		
		reverse_iterator rend()
		{
			return (reverse_iterator(this->begin()));
		}

		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(this->begin()));
		}

		nodePtr& getEndNode()
		{
			return this->_end;
		} 


		// Minimum
		nodePtr minimum(nodePtr _x)
		{
			while (_x->_left != this->_end)
				_x = _x->_left;
			return (_x);
		}
		// Maximum
		nodePtr maximum(nodePtr _x)
		{
			while (_x->_right != this->_end)
				_x = _x->_right;
			return (_x);
		}
		// Successor
		nodePtr successor(nodePtr _x)
		{
			if (_x->_right != this->_end)
				return (minimum(_x->_right));
			nodePtr _y = _x->_parent;
			while (_y != this->_end && _x == _y->_right)
			{
				_x = _y;
				_y = _y->_parent;
			}
			return (_y);
		}
		// Predecessor
		nodePtr predecessor(nodePtr _x)
		{
			if (_x->_left != this->_end)
				return (maximum(_x->_left));
			nodePtr _y = _x->_parent;
			while (_y != this->_end && _x == _y->_left)
			{
				_x = _y;
				_y = _y->_parent;
			}
			return (_y);
		}

		// Inorder Traversal
		void inorder()
		{
			if (this->_root != this->_end)
				this->traversalHelp(this->_root, INORDER);
		}

		// Preorder Traversal
		void preorder()
		{
			if (this->_root != this->_end)
				this->traversalHelp(this->_root, PREORDER);
		}

		// Postorder Traversal
		void postorder()
		{
			if (this->_root != this->_end)
				this->traversalHelp(this->_root, POSTORDER);
		}

		private:
		// New node creation
		nodePtr makenode(value_type _data = value_type())
		{
			nodePtr _new = _alloc.allocate(1);
			_alloc.construct(_new, _data, _end);
			std::cout << _new->_data.first << std::endl;
			return (_new);
		}

		// Insertion operation: rebalancing function
		void treeBalanceAfterInsert(nodePtr _new)
		{
			while (_new->_parent->_color == RED)
			{
				if (_new->_parent == _new->_parent->_parent->_left) // _new _parent is _left child of grand_parent
				{
					// std::cout << "The _parent of new node is a _left child" << std::endl;
					nodePtr _sibling = _new->_parent->_parent->_right; // _sibling of _new
					if (_sibling->_color == RED) // case 1: _sibling is also red  as _parent and _new
					{
						_new->_parent->_color = BLACK;
						_sibling->_color = BLACK;
						_new->_parent->_parent->_color = RED;
						_new = _new->_parent->_parent;
					}
					else // case 2: _sibling is black and _new is the _right child //case 3: _sibling is black and _new is the _left child
					{
						if (_new == _new->_parent->_right) // case 2
						{
							// std::cout << "case 2" << std::endl;
							_new = _new->_parent;
							this->leftRotate(_new);
						}
						// case 3
						// std::cout << "case 3" << std::endl;
						_new->_parent->_color = BLACK;
						_new->_parent->_parent->_color = RED;
							// std::cout << "node to be rotate: " << _new->_parent->_parent << std::endl;
						this->rightRotate(_new->_parent->_parent);
						break ;
					}
				}
				else // the _parent of _new is _right child of grand_parent
				{
					// std::cout << "The _parent of new node is a _right child" << std::endl;
					nodePtr _sibling = _new->_parent->_parent->_left;
					if (_sibling->_color == RED)
					{
						_new->_parent->_color = BLACK;
						_sibling->_color = BLACK;
						_new->_parent->_parent->_color = RED;
						_new = _new->_parent->_parent;
					}
					else
					{
						if (_new == _new->_parent->_left)
						{
							_new = _new->_parent;
							this->rightRotate(_new);
						}
						_new->_parent->_color = BLACK;
						_new->_parent->_parent->_color = RED;
						this->leftRotate(_new->_parent->_parent);
						break ;
					}
				}
			}
			this->_root->_color = BLACK;
		}

		// Rotation functions
		void leftRotate(nodePtr _x)
		{
			// std::cout << "---> _Left Rotate: " << _x << std::endl;
			nodePtr _y = _x->_right;
			_x->_right = _y->_left;
			if (_y->_left != this->_end)
				_y->_left->_parent = _x;
			_y->_parent = _x->_parent;
			if (_x->_parent == this->_end) // _x is _x
				this->_root = _y;
			else if (_x == _x->_parent->_left) // _x is _left child
				_x->_parent->_left = _y;
			else // _x is _right child
				_x->_parent->_right = _y;
			_y->_left = _x;
			_x->_parent = _y;
		}

		void rightRotate(nodePtr _x)
		{
			// std::cout << "---> _Right Rotate: " << _x << std::endl;
			nodePtr _y = _x->_left;
			_x->_left = _y->_right;
			if (_y->_right != this->_end)
				_y->_right->_parent = _x;
			_y->_parent = _x->_parent;
			if (_x->_parent == this->_end) // _x is _x
				this->_root = _y;
			else if (_x == _x->_parent->_right) // _x is _right child
				_x->_parent->_right = _y;
			else // _x is _left child
				_x->_parent->_left = _y;
			_y->_right = _x;
			_x->_parent = _y; 
		}

		// Inorder Travers
		void traversalHelp(nodePtr _x, traversType _type)
		{
			if (_x != this->_end && _type == INORDER)
			{
				traversalHelp(_x->_left, INORDER);
				std::cout << std::endl;
				std::cout <<  "Node: " <<_x << " Color: " << _x->_color << std::endl;
				(_x->_left != this->_end) ? std::cout << "\tLeft Child: " << _x->_left << " Color: " << _x->_left->_color << std::endl : std::cout <<  "\tLeft Child: NIL"  << " Color: " << _x->_left->_color << std::endl;
				(_x->_right != this->_end) ? std::cout << "\t\tRight Child: "  << _x->_right << " Color: " << _x->_right->_color << std::endl : std::cout<<  "\t\tRight Child: NIL"  << " Color: " << _x->_right->_color << std::endl;
				traversalHelp(_x->_right, INORDER);
			}
			if (_x != this->_end && _type == PREORDER)
			{
				std::cout << std::endl;
				std::cout <<  "Node: " <<_x << " Color: " << _x->_color << std::endl;
				(_x->_left != this->_end) ? std::cout << "\tLeft Child: " << _x->_left << " Color: " << _x->_left->_color << std::endl : std::cout <<  "\tLeft Child: NIL"  << " Color: " << _x->_left->_color << std::endl;
				(_x->_right != this->_end) ? std::cout << "\t\tRight Child: " <<_x->_right << " Color: " << _x->_right->_color << std::endl : std::cout<<  "\t\tRight Child: NIL"  << " Color: " << _x->_right->_color << std::endl;
				traversalHelp(_x->_left, PREORDER);
				traversalHelp(_x->_right, PREORDER);
			}
			if (_x != this->_end && _type == POSTORDER)
			{
				traversalHelp(_x->_left, POSTORDER);
				traversalHelp(_x->_right, POSTORDER);
				std::cout << std::endl;
				std::cout <<  "Node: " << _x  << " Color: " << _x->_color << std::endl;
				(_x->_left != this->_end) ? std::cout << "\tLeft Child: " << _x->_left << " Color: " << _x->_left->_color << std::endl : std::cout <<  "\tLeft Child: NIL"  << " Color: " << _x->_left->_color << std::endl;
				(_x->_right != this->_end) ? std::cout << "\t\tRight Child: " << _x->_right << " Color: " << _x->_right->_color << std::endl : std::cout<<  "\t\tRight Child: NIL"  << " Color: " << _x->_right->_color << std::endl;
			}
		}

		void destroy(nodePtr _x)
		{
			if (_x != this->_end)
			{
				destroy(_x->_left);
				destroy(_x->_right);
				this->_alloc.destroy(_x);
				this->_alloc.deallocate(_x, 1);
			}
		}

		// shift function for shifting two nodes
		void shift(nodePtr _u, nodePtr _v)
		{
			if (_u->_parent == this->_end) // _u is root
				this->_root = _v;
			else if (_u == _u->_parent->_left) // _u is _left child
				_u->_parent->_left = _v;
			else // _u is _right child
				_u->_parent->_right = _v;
			_v->_parent = _u->_parent;
		}

		// Deletion operation: rebalacing
		void treeBalanceAfterRemove(nodePtr _x)
		{
			while (_x != this->_root && _x->_color == BLACK)
			{
				if (_x == _x->_parent->_left) // the node is a _left child
				{
					// std::cout << "case1: the node is a _left child" << std::endl;
					nodePtr _sibling = _x->_parent->_right;
					if (_sibling->_color == RED) // case 1: _sibling is Red.
					{
						_sibling->_color = BLACK;
						_x->_parent->_color = RED;
						this->leftRotate(_x->_parent);
						_sibling = _x->_parent->_right;
					}
					if (_sibling->_color == BLACK // case 2: _sibling is balck and both children are black too.
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
					nodePtr _sibling = _x->_parent->_left;
					if (_sibling->_color == RED)
					{
						_sibling->_color = BLACK;
						_x->_parent->_color = RED;
						this->rightRotate(_x->_parent);
						_sibling = _x->_parent->_left;
					}
					if (_sibling->_color == BLACK
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