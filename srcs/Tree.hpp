#ifndef TREE_HPP
# define TREE_HPP
# include <memory>
# include <iostream>
# include "Utility.hpp" // ft::pair
# include "Iterator.hpp"

typedef enum 
{
	INORDER,
	PREORDER,
	POSTORDER
} TraversType;

typedef enum
{
	RED,
	BLACK
} Color;

namespace ft {

	// Template struct node
	template <class T>
	struct node {
		T		data;
		node	*right;
		node	*left;
		node	*parent;
		Color	color;
	};

	// tree iterator
	template <class Tree, class Iter, class T>
	class tree_iter : public iterator<std::bidirectional_iterator_tag,
								typename iterator_traits<Iter>::value_type
								>
	{
	public:
		typedef Iter iterator_type;
		// typedef typename ft::iterator_traits<iterator_type>::difference_type difference_type;
		typedef T* pointer;
		typedef T& reference;

	private:
		Tree tree;
		iterator_type current;

	public:
		tree_iter() : current()
		{
		}

		tree_iter(iterator_type x) : current(x)
		{
			tree = Tree(x);
		}

		template <class OthIter, class U>
		tree_iter(const tree_iter<OthIter, U>& other) : current(other.current)
		{
		}
		template <class OthIter, class U>
		tree_iter& operator=(const tree_iter<OthIter, U>& other)
		{
			this->current = other.base();
			return (*this);
		}

		~tree_iter()
		{
		}

		iterator_type base() const
		{
			return (this->current);
		}

		reference operator*() const
		{
			return current->data;
		}

		pointer operator->() const
		{
			return &(operator*());
		}

		tree_iter & operator++() // use successor
		{
			// ++(this->current);
			// if(current->right != +
			//  )
			return (*this);
		}

		tree_iter operator++(int) // use successor
		{
			tree_iter tmp = *this;
			// ++(this->current);
			return (tmp);
		}

		tree_iter & operator--() // use predecessor
		{
			// --this->current;
			return (*this);
		}

		tree_iter operator--(int) // use predecessor
		{
			tree_iter tmp = *this;
			// --this->current;
			return (tmp);
		}

	};
	// template <class Iter>
  	// bool operator==(const tree_iter<Iter>& lhs, const tree_iter<Iter>& rhs)
	// {
	// 	return (lhs.base() == rhs.base());
	// }
	// template <class Iter>
	// bool operator!=(const tree_iter<Iter>& lhs, const tree_iter<Iter>& rhs)
	// {
	// 	return !(lhs == rhs);
	// }

	// Template class tree
	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class tree
	{
	public:
		typedef T						value_type;
		typedef value_type*				pointer;
		typedef value_type&				reference;
		typedef struct node<value_type>	node;
		typedef node*					nodePtr;
		typedef Compare					compare;
		typedef tree*					treePtr;
		typedef typename Alloc::template rebind<node>::other	allocate_type;
		typedef tree_iter<treePtr, nodePtr, value_type> iterator;

	private:
		nodePtr	_root;
		nodePtr	_end;

		allocate_type allocator;
		compare comp;

	public:
		tree(): _root(nullptr), _end(nullptr)
		{
			_end = this->newNode();
			this->_root = this->_end;
			// std::cout << "Default: _root: " << _root <<" _end: " << _end << std::endl;
		}

		~tree()
		{
			allocator.destroy(this->_end);
			allocator.deallocate(this->_end, 1);
		}
		// Search operation
		nodePtr find(value_type data)
		{
			nodePtr current = this->_root;
			while (current != this->_end) {
				if (current->data == data) { // must be replaced by Compare
					break;
				}
				current = comp(current->data, data) ? current->right : current->left; // must be replaced by Compare
			}
			return (current);
		}
		// Insertion operation
		void insert(value_type data = value_type())
		{
			if (this->_root == this->_end)
			{
				this->_root = this->newNode(data);
				_root->parent = this->_end;
				this->_end->left = this->_root;
				// std::cout << "Default: _root: " << _root <<":" <<_root->parent<<" _end: " << _end << ":" << _end->left << std::endl;
				return ;
			}
			if (find(data) != _end)
				return ;
			nodePtr _new = this->newNode(data);
			nodePtr parentNode = this->_end;
			nodePtr y = this->_root;
			while (y != this->_end) // find the _new parent
			{
				parentNode = y;
				y = (comp(_new->data, y->data)) ? y->left : y->right; // must be replaced by Compare
				_new->parent = parentNode;
			}
			if (comp(_new->data, parentNode->data)) // must be replaced by Compare
				parentNode->left = _new;
			else
				parentNode->right = _new;
			_new->color = RED;
			this->insertFixup(_new);
		}
		// Deletion operation
		// case 1: has no child: delete the node
		// case 2: has one child: replace the node by his child
		// case 3: has two child: -find the smallest node in right subtree
								//   -replace the smallest node by his right child
								//   -replace the node by smallest node
		void remove(value_type data = value_type())
		{
			nodePtr del;
			nodePtr x;
			if (!this->_root || (del = this->find(data)) == this->_end)
				return ;
			nodePtr y = del;
			Color col = y->color; // store the original color of node to be delete
			if (del->left == this->_end)
			{
				// std::cout << "case1: has a right child or no child" << std::endl;
				x = del->right;
				this->transplant(del, del->right);
				allocator.destroy(del);
				allocator.deallocate(del, 1);
			}
			else if (del->right == this->_end)
			{
				// std::cout << "case1: has a left child" << std::endl;
				x = del->left;
				this->transplant(del, del->left);
				allocator.destroy(del);
				allocator.deallocate(del, 1);
			}
			else
			{
				// std::cout << "case2: has two child" << std::endl;
				y = successor(del);
				// std::cout << "minimum: " << y << std::endl;
				col = y->color;
				x = y->right;
				if (y->parent == del) // y is direct child of delete node
				{
					// std::cout << "y is direct child of delete node" << std::endl;
					x->parent = y;
				}
				else
				{
					// std::cout << "y is not direct child of delete node" << std::endl;
					this->transplant(y, y->right);
					y->right = del->right;
					y->right->parent = y;
				}
				this->transplant(del, y);
				y->left = del->left;
				y->left->parent = y;
				y->color = del->color;
				allocator.destroy(del);
				allocator.deallocate(del, 1);
			}
			if (col == BLACK)
			{
				// std::cout << "Black: Fixup" << std::endl;
				// std::cout << "Key: " << data << std::endl;
				this->deleteFixup(x);	
			}

		}

		// Iterators
		iterator begin()
		{
			return ((this->minimum(this->_root)));
		}

		iterator end()
		{
			return (iterator(this->_end));
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
		nodePtr newNode(value_type data = value_type())
		{
			nodePtr _new = allocator.allocate(1);
			_new->data = data;
			_new->right = this->_end;
			_new->left = this->_end;
			_new->parent = this->_end;
			_new->color = BLACK;
			return (_new);
		}
		// Insertion operation: rebalancing function
		void insertFixup(nodePtr _new)
		{
			while (_new->parent->color == RED)
			{
				if (_new->parent == _new->parent->parent->left) // _new parent is left child of grandparent
				{
					// std::cout << "The parent of new node is a left child" << std::endl;
					nodePtr sibling = _new->parent->parent->right; // sibling of _new
					if (sibling->color == RED) // case 1: sibling is also red  as parent and _new
					{
						// std::cout << "case1: The sibling of new node is also red  as parent and new node" << std::endl;
						_new->parent->color = BLACK;
						sibling->color = BLACK;
						_new->parent->parent->color = RED;
						_new = _new->parent->parent;
					}
					else // case 2: sibling is black and _new is the right child //case 3: sibling is black and _new is the left child
					{
						if (_new == _new->parent->right) // case 2
						{
							// std::cout << "case 2" << std::endl;
							_new = _new->parent;
							this->leftRotate(_new);
						}
						// case 3
						// std::cout << "case 3" << std::endl;
						_new->parent->color = BLACK;
						_new->parent->parent->color = RED;
							// std::cout << "node to be rotate: " << _new->parent->parent << std::endl;
						this->rightRotate(_new->parent->parent);
						break ;
					}
				}
				else // the parent of _new is right child of grandparent
				{
					// std::cout << "The parent of new node is a right child" << std::endl;
					nodePtr sibling = _new->parent->parent->left;
					if (sibling->color == RED)
					{
						_new->parent->color = BLACK;
						sibling->color = BLACK;
						_new->parent->parent->color = RED;
						_new = _new->parent->parent;
					}
					else
					{
						if (_new == _new->parent->left)
						{
							_new = _new->parent;
							this->rightRotate(_new);
						}
						_new->parent->color = BLACK;
						_new->parent->parent->color = RED;
						this->leftRotate(_new->parent->parent);
						break ;
					}
				}
			}
			this->_root->color = BLACK;
		}

		// Rotation functions
		void leftRotate(nodePtr x)
		{
			// std::cout << "---> Left Rotate: " << x << std::endl;
			nodePtr pivot = x->right;
			x->right = pivot->left;
			if (pivot->left != this->_end)
				pivot->left->parent = x;
			pivot->parent = x->parent;
			if (x->parent == this->_end) // x is root
				this->_root = pivot;
			else if (x == x->parent->left) // x is left child
				x->parent->left = pivot;
			else // x is right child
				x->parent->right = pivot;
			pivot->left = x;
			x->parent = pivot;
		}

		void rightRotate(nodePtr x)
		{
			// std::cout << "---> Right Rotate: " << x << std::endl;
			nodePtr pivot = x->left;
			x->left = pivot->right;
			if (pivot->right != this->_end)
				pivot->right->parent = x;
			pivot->parent = x->parent;
			if (x->parent == this->_end) // x is root
				this->_root = pivot;
			else if (x == x->parent->right) // x is right child
				x->parent->right = pivot;
			else // x is left child
				x->parent->left = pivot;
			pivot->right = x;
			x->parent = pivot; 
		}

		// Inorder Travers
		void traversalHelp(nodePtr root, TraversType type)
		{
			if (root != this->_end && type == INORDER)
			{
				traversalHelp(root->left, INORDER);
				std::cout << std::endl;
				std::cout <<  "Node: Data: " <<root->data << " Add: " << root  << " Color: " << root->color << std::endl;
				(root->left != this->_end) ? std::cout << "\tLeft Child: Data: " << root->left->data << " Add: " << root->left << " Color: " << root->left->color << std::endl : std::cout <<  "\tLeft Child: NIL"  << " Color: " << root->left->color << std::endl;
				(root->right != this->_end) ? std::cout << "\t\tRight Child: Data: " <<root->right->data << " Add: " << root->right << " Color: " << root->right->color << std::endl : std::cout<<  "\t\tRight Child: NIL"  << " Color: " << root->right->color << std::endl;
				traversalHelp(root->right, INORDER);
			}
			if (root != this->_end && type == PREORDER)
			{
				std::cout << std::endl;
				std::cout <<  "Node: Data: " <<root->data << " Add: " << root  << " Color: " << root->color << std::endl;
				(root->left != this->_end) ? std::cout << "\tLeft Child: Data: " << root->left->data << " Add: " << root->left << " Color: " << root->left->color << std::endl : std::cout <<  "\tLeft Child: NIL"  << " Color: " << root->left->color << std::endl;
				(root->right != this->_end) ? std::cout << "\t\tRight Child: Data: " <<root->right->data << " Add: " << root->right << " Color: " << root->right->color << std::endl : std::cout<<  "\t\tRight Child: NIL"  << " Color: " << root->right->color << std::endl;
				traversalHelp(root->left, PREORDER);
				traversalHelp(root->right, PREORDER);
			}
			if (root != this->_end && type == POSTORDER)
			{
				traversalHelp(root->left, POSTORDER);
				traversalHelp(root->right, POSTORDER);
				std::cout << std::endl;
				std::cout <<  "Node: Data: " <<root->data << " Add: " << root  << " Color: " << root->color << std::endl;
				(root->left != this->_end) ? std::cout << "\tLeft Child: Data: " << root->left->data << " Add: " << root->left << " Color: " << root->left->color << std::endl : std::cout <<  "\tLeft Child: NIL"  << " Color: " << root->left->color << std::endl;
				(root->right != this->_end) ? std::cout << "\t\tRight Child: Data: " <<root->right->data << " Add: " << root->right << " Color: " << root->right->color << std::endl : std::cout<<  "\t\tRight Child: NIL"  << " Color: " << root->right->color << std::endl;
			}
		}

		// Transplant function for shifting two nodes
		void transplant(nodePtr u, nodePtr v)
		{
			if (u->parent == this->_end) // u is root
				this->_root = v;
			else if (u == u->parent->left) // u is left child
				u->parent->left = v;
			else // u is right child
				u->parent->right = v;
			v->parent = u->parent;
		}

		// Minimum
		nodePtr minimum(nodePtr x)
		{
			while (x->left != this->_end)
				x = x->left;
			return (x);
		}
		// Maximum
		nodePtr maximum(nodePtr x)
		{
			while (x->right != this->_end)
				x = x->right;
			return (x);
		}

		nodePtr successor(nodePtr x)
		{
			if (x->right != this->_end)
				return (minimum(x->right));
			nodePtr y = x->parent;
			while (y != this->_end)
			{
				x = y;
				y = y->parent;
			}
			return (y);
		}

		nodePtr predecessor(nodePtr x)
		{
			if (x->left != this->_end)
				return (maximum(x->left));
			nodePtr y = x->parent;
			while (y != this->_end)
			{
				x = y;
				y = y->parent;
			}
			return (y);
		}

		// Deletion operation: rebalacing
		void deleteFixup(nodePtr x)
		{
			while (x != this->_root && x->color == BLACK)
			{
				if (x == x->parent->left) // the node is a left child
				{
					// std::cout << "case1: the node is a left child" << std::endl;
					nodePtr sibling = x->parent->right;
					if (sibling->color == RED) // case 1: sibling is Red.
					{
						sibling->color = BLACK;
						x->parent->color = RED;
						this->leftRotate(x->parent);
						sibling = x->parent->right;
					}
					if (sibling->color == BLACK // case 2: sibling is balck and both children are black too.
						&& sibling->left->color == BLACK
						&& sibling->right->color == BLACK)
					{
						sibling->color = RED;
						x = x->parent;
					}
					else // case 3, 4 handling
					{
						if (sibling->right->color == BLACK) // case 3
						{
							sibling->left->color = BLACK;
							sibling->color = RED;
							this->rightRotate(sibling);
							sibling = x->parent->right;
						}
						sibling->color = x->parent->color;
						x->parent->color = BLACK;
						sibling->right->color = BLACK;
						this->leftRotate(x->parent);
						x = this->_root;
					}
				}
				else // the node is a right child
				{
					// symmetric
					// std::cout << "case1: the node is a right child" << std::endl;
					nodePtr sibling = x->parent->left;
					if (sibling->color == RED)
					{
						sibling->color = BLACK;
						x->parent->color = RED;
						this->rightRotate(x->parent);
						sibling = x->parent->left;
					}
					if (sibling->color == BLACK
						&& sibling->right->color == BLACK
						&& sibling->left->color == BLACK)
					{
						sibling->color = RED;
						x = x->parent;
					}
					else
					{
						if (sibling->left->color == BLACK)
						{
							sibling->right->color = BLACK;
							sibling->color = RED;
							this->leftRotate(sibling);
							sibling = x->parent->left;
						}
						sibling->color = x->parent->color;
						x->parent->color = BLACK;
						sibling->left->color = BLACK;
						this->rightRotate(x->parent);
						x = this->_root;
					}
				}
			}
			x->color = BLACK;
		}
	};// end tree class

} //end of namespace ft

#endif