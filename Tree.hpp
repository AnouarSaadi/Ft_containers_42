#ifndef TREE_HPP
# define TREE_HPP
#include <memory>
#include <iostream>

enum COLOR
{
	RED,
	BLACK
};

namespace ft {
	// Template struct node
	template <class T>
	struct node {
		T				data;
		struct node		*right;
		struct node		*left;
		struct node		*parent;
		enum COLOR		color;
	};
	// Template class tree
	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class tree
	{
	private:
		typedef T								value_type;
		typedef value_type*						pointer;
		typedef value_type&						reference;
		typedef struct node<value_type>			node;

		node* _root;
		node* _end;

	public:
		tree(): _root(nullptr), _end(nullptr)
		{
			_end = newNode();
			_end->left = _root;
			std::cout << "Default: _root: " << _root << " _end: " << _end << std::endl;
		}

		~tree()
		{

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
			node* tmp;

			if (this->_root == nullptr)
			{
				this->_root = newNode(data);
				std::cout << "|--- "<< _root <<" ---|" << std::endl;
				return ;
			}
			if (find(data) != _end)
				return ;
			node* _new = newNode(data);
			node* parentNode = this->_end;
			tmp = this->_root;
			while (tmp != this->_end) // find the _new parent
			{
				parentNode = tmp;
				tmp = (_new->data < tmp->data) ? tmp->left : tmp->right; // must be replaced by Compare
				_new->parent = parentNode;
			}
			std::cout << "|--- "<< parentNode <<" ---|" << std::endl;
			if (_new->data < parentNode->data) // must be replaced by Compare
				parentNode->left = _new;
			else
				parentNode->right = _new;
			_new->color = RED;
			this->insertFixup(_new);
		}
		
		// Inorder Travers
		void inorder()
		{
			this->inorderHelp(this->_root);
		}

		private:
		// New node creation
		node* newNode(value_type data = value_type())
		{
			node* _new = new node();
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
		void leftRotate(node *root)
		{
			std::cout << "---> Left Rotate: " << root << std::endl;
			node *pivot = root->right;
			root->right = pivot->left;
			if (pivot->left != this->_end)
				pivot->left->parent = root;
			pivot->parent = root->parent;
			if (root->parent == this->_end) // root is root
				this->_root = pivot;
			else if (root == root->parent->left) // root is left child
				root->parent->left = pivot;
			else // root is right child
				root->parent->right = pivot;
			pivot->left = root;
			root->parent = pivot;
		}

		void rightRotate(node *root)
		{
			std::cout << "---> Right Rotate: " << root << std::endl;
			node *pivot = root->left;
			root->left = pivot->right;
			if (pivot->right != this->_end)
				pivot->right->parent = root;
			pivot->parent = root->parent;
			if (root->parent == this->_end) // root is root
				this->_root = pivot;
			else if (root == root->parent->right) // root is right child
				root->parent->right = pivot;
			else // root is left child
				root->parent->left = pivot;
			pivot->right = root;
			root->parent = pivot; 
		}

		// Inorder Travers
		void inorderHelp(node *root)
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


	};
}

#endif