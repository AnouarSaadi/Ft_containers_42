#ifndef TREE_HPP
# define TREE_HPP

# include <memory>
# include "Iterator.hpp"
# include "Utility.hpp"

# define BLACK 1
# define RED 0

namespace ft {
	// Template struct node
	template <class T>
	struct node {
		typedef T value_type;

		bool		_color;
		value_type	_data;
		node		*_right;
		node		*_left;
		node		*_parent;

		node() :_color(BLACK), _data(), _right(nullptr), _left(nullptr), _parent(nullptr) {}
		node(value_type data) :_color(BLACK), _data(data), _right(nullptr), _left(nullptr), _parent(nullptr) {}
	};

	// tree iterator class
	template <class Iter, class T>
	class tree_iterator : public iterator<std::bidirectional_iterator_tag,
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
		tree_iterator() : _current()
		{
		}

		tree_iterator(iterator_type _x) : _current(_x)
		{
		}
		
		template <class OthIter, class U>
		tree_iterator(const tree_iterator<OthIter, U>& _other) : _current(_other.base())
		{
		}

		template <class OthIter, class U>
		tree_iterator& operator=(const tree_iterator<OthIter, U>& _other)
		{
			this->_current = _other.base();
			return (*this);
		}

		~tree_iterator()
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

		tree_iterator & operator++()
		{
			this->_current = successor(this->_current);
			return (*this);
		}

		tree_iterator operator++(int)
		{
			tree_iterator _tmp(*this);
			this->_current = successor(this->_current);
			return (_tmp);
		}

		tree_iterator & operator--()
		{
			this->_current = predecessor(this->_current);
			return (*this);
		}

		tree_iterator operator--(int)
		{
			tree_iterator _tmp(*this);
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
		
		iterator_type maximum(iterator_type _x) const
		{
			while (_x->_right != nullptr)
				_x = _x->_right;
			return (_x);
		}
		
		iterator_type successor(iterator_type _x)
		{
			if (_x->_right != nullptr)
				return (minimum(_x->_right));
			iterator_type _node_y = _x->_parent;
			while (_node_y != nullptr && _x == _node_y->_right)
			{
				_x = _node_y;
				_node_y = _node_y->_parent;
			}
			return (_node_y);
		}
		
		iterator_type predecessor(iterator_type _x)
		{
			if (_x->_left != nullptr)
				return (maximum(_x->_left));
			iterator_type _node_y = _x->_parent;
			while (_node_y != nullptr && _x == _node_y->_left)
			{
				_x = _node_y;
				_node_y = _node_y->_parent;
			}
			return (_node_y);
		}
	public:
		template <class Iter1, class T1>
  		bool operator==(const tree_iterator<T1, Iter1>& _iter)
		{
			return this->_current == _iter.base();
		}
		template <class Iter1, class T1>
  		bool operator!=(const tree_iterator<T1, Iter1>& _iter)
		{
			return this->_current != _iter.base();
		}

	};

	// Template class tree
	template <class T, class Compare = std::less<T> , class Alloc = std::allocator<T> >
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
		typedef Compare							value_compare;
		typedef tree_iterator<node_pointer, pointer> iterator;
		typedef tree_iterator<node_pointer, const_pointer> const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename Alloc::template rebind<node>::other	allocator_type;
		typedef size_t	size_type;

	private:
		node_pointer	_root;
		node_pointer	_end;

		allocator_type _alloc;
		value_compare _comp;
		size_type _size;

	public:
		tree(value_compare _comp, allocator_type _alloc): _root(nullptr), _end(), _alloc(_alloc), _comp(_comp), _size(0)
		{
			_end = this->makenode();
		}

		tree(const tree& _tr) : _root(nullptr), _end(), _alloc(_tr._alloc), _comp(), _size(0)
		{
			*this = _tr;
		}

		tree& operator=(tree& _tr)
		{
			if (this != &_tr)
			{
				this->clear();
				value_comp() = _tr.value_comp();
				this->_alloc = _tr._alloc;
				iterator _tb = _tr.begin();
				while (_tb != _tr.end())
					insert(*_tb++);
			}
		}

		~tree()
		{
			this->clear();
			_alloc.destroy(this->_end);
			_alloc.deallocate(this->_end, 1);
		}

		void swap(tree& _tr)
		{
			std::swap(this->_root, _tr._root);
			std::swap(this->_end, _tr._end);
			std::swap(this->_alloc , _tr._alloc);
			std::swap(this->_comp, _tr._comp);
			std::swap(this->_size, _tr._size);
		}

		void clear()
		{
			this->destroy(this->_root);
			this->_root = nullptr;
			this->_size = 0;
		}

		size_type size() const
		{
			return this->_size;
		}

		size_type max_size() const
		{
			return _alloc.max_size();
		}

		iterator begin()
		{
			if (this->_root != nullptr)
				return iterator(this->minimum(this->_root));
			return iterator(this->_end);
		}
		
		const_iterator begin() const
		{
			if (this->_root != nullptr)
				return const_iterator(this->minimum(this->_root));
			return const_iterator(this->_end);
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

		value_compare value_comp() const
		{
			return this->_comp;
		}

		iterator lower_bound (const value_type& _value)
		{
			node_pointer _result = _end;
			node_pointer _node_r = this->_root;
			while (_node_r != nullptr)
			{
				if (!_comp(_node_r->_data, _value))
				{
					_result = _node_r;
					_node_r = _node_r->_left;
				}
				else
					_node_r = _node_r->_right;
			}
			return iterator(_result);
		}

		const_iterator lower_bound (const value_type& _value) const
		{
			node_pointer _result = _end;
			node_pointer _node_r = this->_root;
			while (_node_r != nullptr)
			{
				if (!_comp(_node_r->_data, _value))
				{
					_result = _node_r;
					_node_r = _node_r->_left;
				}
				else
					_node_r = _node_r->_right;
			}
			return const_iterator(_result);
		}

		iterator upper_bound (const value_type& _value)
		{
			node_pointer _result = _end;
			node_pointer _node_r = this->_root;
			while (_node_r != nullptr)
			{
				if (_comp(_value, _node_r->_data))
				{
					_result = _node_r;
					_node_r = _node_r->_left;
				}
				else
					_node_r = _node_r->_right;
			}
			return iterator(_result);
		}

		const_iterator upper_bound (const value_type& _value) const
		{
			node_pointer _result = _end;
			node_pointer _node_r = this->_root;
			while (_node_r != nullptr)
			{
				if (_comp(_value, _node_r->_data))
				{
					_result = _node_r;
					_node_r = _node_r->_left;
				}
				else
					_node_r = _node_r->_right;
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
				this->_size++;
				return ;
			}
			if (find(_data) != nullptr)
				return ;
			this->_end->_left = nullptr;
			_root->_parent = nullptr;
			node_pointer _new_node = this->makenode(_data);
			node_pointer _parent_ = nullptr;
			node_pointer _node_r = this->_root;
			while (_node_r != nullptr)
			{
				_parent_ = _node_r;
				_node_r = (_comp(_new_node->_data, _node_r->_data)) ? _node_r->_left : _node_r->_right;
				_new_node->_parent = _parent_;
			}
			if (_comp(_new_node->_data, _parent_->_data))
				_parent_->_left = _new_node;
			else
				_parent_->_right = _new_node;
			_new_node->_color = RED;
			this->treeFixAfterInsert(_new_node);
			this->_end->_left = this->_root;
			this->_root->_parent = this->_end;
			this->_size++;
		}

		// Delete operation
		void erase(value_type _data = value_type())
		{
			node_pointer _del_node;
			node_pointer _node_x;
			if (!this->_root || (_del_node = this->find(_data)) == nullptr)
				return ;
			this->_end->_left = nullptr;
			this->_root->_parent = nullptr;
			node_pointer _node_y = _del_node;
			bool _deleted_col = _node_y->_color;
			if (_del_node->_left == nullptr)
			{
				_node_x = _del_node->_right;
				this->shift(_del_node, _del_node->_right);
				_alloc.destroy(_del_node);
				_alloc.deallocate(_del_node, 1);
			}
			else if (_del_node->_right == nullptr)
			{

				_node_x = _del_node->_left;
				this->shift(_del_node, _del_node->_left);
				_alloc.destroy(_del_node);
				_alloc.deallocate(_del_node, 1);
			}
			else
			{
				_node_y = minimum(_del_node->_right);
				_deleted_col = _node_y->_color;
				_node_x = _node_y->_right;
				if (_node_y->_parent != nullptr && _node_y->_parent != _del_node)
				{
					this->shift(_node_y, _node_y->_right);
					_node_y->_right = _del_node->_right;
					_node_y->_right->_parent = _node_y;
				}
				this->shift(_del_node, _node_y);
				_node_y->_left = _del_node->_left;
				_node_y->_left->_parent = _node_y;
				_node_y->_color = _del_node->_color;
				_alloc.destroy(_del_node);
				_alloc.deallocate(_del_node, 1);
			}
			if (_deleted_col == BLACK && _node_x != nullptr)
				this->treeFixAfterRemove(_node_x);
			if (this->_root != nullptr)
			{
				this->_end->_left = this->_root;
				this->_root->_parent = this->_end;
			}
			this->_size--;
		}

		node_pointer minimum(node_pointer _node_x) const
		{
			while (_node_x->_left != nullptr)
				_node_x = _node_x->_left;
			return (_node_x);
		}

		node_pointer maximum(node_pointer _node_x) const
		{
			while (_node_x->_right != nullptr)
				_node_x = _node_x->_right;
			return (_node_x);
		}

		node_pointer successor(node_pointer _node_x)
		{
			if (_node_x->_right != nullptr)
				return (minimum(_node_x->_right));
			node_pointer _node_y = _node_x->_parent;
			while (_node_y !=  nullptr && _node_x == _node_y->_right)
			{
				_node_x = _node_y;
				_node_y = _node_y->_parent;
			}
			return (_node_y);
		}

		node_pointer predecessor(node_pointer _node_x)
		{
			if (_node_x->_left != nullptr)
				return (maximum(_node_x->_left));
			node_pointer _node_y = _node_x->_parent;
			while (_node_y != nullptr && _node_x == _node_y->_left)
			{
				_node_x = _node_y;
				_node_y = _node_y->_parent;
			}
			return (_node_y);
		}

		private:
		node_pointer makenode(value_type _data = value_type())
		{
			node_pointer _new_node = _alloc.allocate(1);
			_alloc.construct(_new_node, _data);
			return (_new_node);
		}

		void treeFixAfterInsert(node_pointer _fix_node)
		{
			while (_fix_node->_parent != nullptr && _fix_node->_parent->_color == RED)
			{
				if (_fix_node->_parent == _fix_node->_parent->_parent->_left)
				{
					node_pointer _sibling = _fix_node->_parent->_parent->_right;
					if (_sibling != nullptr && _sibling->_color == RED)
					{
						_fix_node->_parent->_color = BLACK;
						_sibling->_color = BLACK;
						_fix_node->_parent->_parent->_color = RED;
						_fix_node = _fix_node->_parent->_parent;
					}
					else
					{
						if (_fix_node == _fix_node->_parent->_right)
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
				else
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

		void leftRotate(node_pointer _node_x)
		{
			node_pointer _node_y = _node_x->_right;
			_node_x->_right = _node_y->_left;
			if (_node_y->_left != nullptr)
				_node_y->_left->_parent = _node_x;
			_node_y->_parent = _node_x->_parent;
			if (_node_x->_parent == nullptr)
				this->_root = _node_y;
			else if (_node_x == _node_x->_parent->_left)
				_node_x->_parent->_left = _node_y;
			else
				_node_x->_parent->_right = _node_y;
			_node_y->_left = _node_x;
			_node_x->_parent = _node_y;
		}

		void rightRotate(node_pointer _node_x)
		{
			node_pointer _node_y = _node_x->_left;
			_node_x->_left = _node_y->_right;
			if (_node_y->_right != nullptr)
				_node_y->_right->_parent = _node_x;
			_node_y->_parent = _node_x->_parent;
			if (_node_x->_parent == nullptr)
				this->_root = _node_y;
			else if (_node_x == _node_x->_parent->_right)
				_node_x->_parent->_right = _node_y;
			else
				_node_x->_parent->_left = _node_y;
			_node_y->_right = _node_x;
			_node_x->_parent = _node_y; 
		}

		void destroy(node_pointer _node_x)
		{
			if (_node_x != nullptr)
			{
				destroy(_node_x->_left);
				destroy(_node_x->_right);
				this->_alloc.destroy(_node_x);
				this->_alloc.deallocate(_node_x, 1);
			}
		}

		void shift(node_pointer _node_u, node_pointer _node_v)
		{
			if (_node_u->_parent == nullptr)
				this->_root = _node_v;
			else if (_node_u == _node_u->_parent->_left)
				_node_u->_parent->_left = _node_v;
			else
				_node_u->_parent->_right = _node_v;
			if (_node_v != nullptr)
				_node_v->_parent = _node_u->_parent;
		}

		void treeFixAfterRemove(node_pointer _node_x)
		{
			while (_node_x != this->_root && _node_x->_color == BLACK)
			{
				if (_node_x != nullptr && _node_x == _node_x->_parent->_left)
				{
					node_pointer _sibling = _node_x->_parent->_right;
					if (_sibling != nullptr && _sibling->_color == RED)
					{
						_sibling->_color = BLACK;
						_node_x->_parent->_color = RED;
						this->leftRotate(_node_x->_parent);
						_sibling = _node_x->_parent->_right;
					}
					if (_sibling != nullptr && _sibling->_color == BLACK
						&& _sibling->_left->_color == BLACK
						&& _sibling->_right->_color == BLACK)
					{
						_sibling->_color = RED;
						_node_x = _node_x->_parent;
					}
					else
					{
						if (_sibling->_right->_color == BLACK)
						{
							_sibling->_left->_color = BLACK;
							_sibling->_color = RED;
							this->rightRotate(_sibling);
						}
						_sibling->_color = _node_x->_parent->_color;
						_node_x->_parent->_color = BLACK;
						_sibling->_right->_color = BLACK;
						this->leftRotate(_node_x->_parent);
						_node_x = this->_root;
					}
				}
				else
				{
					node_pointer _sibling = _node_x->_parent->_left;
					if (_sibling != nullptr && _sibling->_color == RED)
					{
						_sibling->_color = BLACK;
						_node_x->_parent->_color = RED;
						this->rightRotate(_node_x->_parent);
						_sibling = _node_x->_parent->_left;
					}
					if (_sibling != nullptr && _sibling->_color == BLACK
						&& _sibling->_right->_color == BLACK
						&& _sibling->_left->_color == BLACK)
					{
						_sibling->_color = RED;
						_node_x = _node_x->_parent;
					}
					else
					{
						if (_sibling->_left->_color == BLACK)
						{
							_sibling->_right->_color = BLACK;
							_sibling->_color = RED;
							this->leftRotate(_sibling);
						}
						_sibling->_color = _node_x->_parent->_color;
						_node_x->_parent->_color = BLACK;
						_sibling->_left->_color = BLACK;
						this->rightRotate(_node_x->_parent);
						_node_x = this->_root;
					}
				}
			}
			_node_x->_color = BLACK;
		}
	};


}

#endif