#ifndef TREE_HPP
# define TREE_HPP
#include <memory>
#include <iostream>

typedef enum
{
	RED,
	BLACK
} Color;

namespace ft {
	// Template struct node
	template <class T>
	struct node {
		T				data;
		struct node		*right;
		struct node		*left;
		struct node		*parent;
		Color		color;
	};
	// Template class tree
	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class tree
	{
	private:
		typedef T						value_type;
		typedef value_type*				pointer;
		typedef value_type&				reference;
		typedef struct node<value_type>	node;
		typedef Compare					compare;
		typedef typename Alloc::template rebind<node>::other	allocate_type;

		node*	_root;
		node*	_end;

		allocate_type allocator;
		compare comp;

	public:
		tree(): _root(nullptr), _end(nullptr)
		{
			// _end = allocator.allocate(1);
			_end = newNode();
			std::cout << "Default: _root: " << _root <<" _end: " << _end << std::endl;
		}

		~tree()
		{
			delete this->_end;
		}
		// Search operation
		node* find(value_type data)
		{
			node* current = this->_root;
			while (current != this->_end) {
				if (current->data == data) { // must be replaced by Compare
					break;
				}
				current = current->data < data ? current->right : current->left; // must be replaced by Compare
			}
			return (current);
		}
		// Insertion operation
		void insert(value_type data = value_type())
		{
			if (this->_root == nullptr)
			{
				this->_root = newNode(data);
				_root->parent = this->_end;
				this->_end->left = this->_root;
				return ;
			}
			if (find(data) != _end)
				return ;
			node* _new = newNode(data);
			node* parentNode = this->_end;
			node* y = this->_root;
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
			// deletion code
			node* del;
			node* x;
			if (!this->_root || (del = this->find(data)) == this->_end)
				return ;
			node *y = del;
			Color col = y->color; // store the original color of node to be delete
			std::cout << "here" << col << std::endl;
			if (del->left == this->_end)
			{
				std::cout << "case1: has a right child or no child" << std::endl;
				x = del->right;
				this->transplant(del, del->right);
				delete del;
			}
			else if (del->right == this->_end)
			{
				std::cout << "case1: has a left child" << std::endl;
				x = del->left;
				this->transplant(del, del->left);
				delete del;
			}
			else
			{
				std::cout << "case2: has two child" << std::endl;
				y = treeSuccessor(del);
				std::cout << "minimum: " << y << std::endl;
				col = y->color;
				x = y->right;
				if (y->parent == del) // y is direct child of delete node
				{
					std::cout << "y is direct child of delete node" << std::endl;
					x->parent = y;
				}
				else
				{
					std::cout << "y is not direct child of delete node" << std::endl;
					this->transplant(y, y->right);
					y->right = del->right;
					y->right->parent = y;
				}
				this->transplant(del, y);
				y->left = del->left;
				y->left->parent = y;
				y->color = del->color;
				delete del;
			}
			std::cout << "here" << col << std::endl;
			if (col == BLACK)
			{
				std::cout << "Black: Fixup" << std::endl;
				this->deleteFixup(child);	
			}

		}

		// Inorder Travers
		void inorder()
		{
			if (this->_root)
				this->inorderHelp(this->_root);
		}

		private:
		// New node creation
		node* newNode(value_type data = value_type())
		{
			node* _new = allocator.allocate(1);
			_new->data = data;
			_new->right = _end;
			_new->left = _end;
			_new->parent = _end;
			_new->color = BLACK;
			return (_new);
		}
		// Insertion operation: rebalancing function
		void insertFixup(node* _new)
		{
			while (_new->parent->color == RED)
			{
				if (_new->parent == _new->parent->parent->left) // _new parent is left child of grandparent
				{
					std::cout << "The parent of new node is a left child" << std::endl;
					node* uncle = _new->parent->parent->right; // uncle of _new
					if (uncle->color == RED) // case 1: uncle is also red  as parent and _new
					{
						std::cout << "case1: The uncle of new node is also red  as parent and new node" << std::endl;
						_new->parent->color = BLACK;
						uncle->color = BLACK;
						_new->parent->parent->color = RED;
						_new = _new->parent->parent;
					}
					else // case 2: uncle is black and _new is the right child //case 3: uncle is black and _new is the left child
					{
						if (_new == _new->parent->right) // case 2
						{
							std::cout << "case 2" << std::endl;
							_new = _new->parent;
							this->leftRotate(_new);
						}
						// case 3
						std::cout << "case 3" << std::endl;
						_new->parent->color = BLACK;
						_new->parent->parent->color = RED;
							std::cout << "node to be rotate: " << _new->parent->parent << std::endl;
						this->rightRotate(_new->parent->parent);
						// break ;
					}
				}
				else // the parent of _new is right child of grandparent
				{
					std::cout << "The parent of new node is a right child" << std::endl;
					node* uncle = _new->parent->parent->left;
					if (uncle->color == RED)
					{
						_new->parent->color = BLACK;
						uncle->color = BLACK;
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
						// break ;
					}
				}
			}
			this->_root->color = BLACK;
		}

		// Rotation functions
		void leftRotate(node* x)
		{
			std::cout << "---> Left Rotate: " << x << std::endl;
			node *pivot = x->right;
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

		void rightRotate(node* x)
		{
			std::cout << "---> Right Rotate: " << x << std::endl;
			node *pivot = x->left;
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
		void inorderHelp(node* root)
		{
			if (root != this->_end)
			{
				inorderHelp(root->left);
				std::cout << std::endl;
				std::cout <<  "Node: Data: " <<root->data << " Add: " << root  << " Color: " << root->color << std::endl;
				(root->left != this->_end) ? std::cout << "\tLeft Child: Data: " << root->left->data << " Add: " << root->left << " Color: " << root->left->color << std::endl : std::cout <<  "\tLeft Child: NIL"  << " Color: " << root->left->color << std::endl;
				(root->right != this->_end) ? std::cout << "\t\tRight Child: Data: " <<root->right->data << " Add: " << root->right << " Color: " << root->right->color << std::endl : std::cout<<  "\t\tRight Child: NIL"  << " Color: " << root->right->color << std::endl;
				inorderHelp(root->right);
			}
		}

		// Transplant function for shifting two nodes
		void transplant(node* u, node* v)
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
		node* minimum(node* x)
		{
			while (x->left != this->_end)
				x = x->left;
			return (x);
		}

		node* treeSuccessor(node* x)
		{
			if (x->right != this->_end)
				return (minimum(x->right));
			node *y = x->parent;
			while (y != this->_end)
			{
				x = y;
				y = y->parent;
			}
			return (y);
		}

		// Deletion operation: rebalacing
		void deleteFixup(node* x)
		{
			while (x != this->_root && x->color == BLACK)
			{
				if (x == x->parent->left)
				{
					node *uncle = x->parent->right;
					if (uncle->color == RED) // case 1: uncle is Red.
					{
						uncle->color = BLACK;
						uncle->parent->color = RED;
						this->leftRotate(x->parent);
						uncle = uncle->parent->right;
					}
					if (uncle->color == BLACK // case 2: uncle is balck and both children are black too.
						&& uncle->left->color == BLACK
						&& uncle->right->color == RED)
					{
						uncle->color = RED;
						x = x->parent;
					}
					else  // Add the case 3, 4 handling
					{ break ;}
				}
			}
		}
	};
}

#endif