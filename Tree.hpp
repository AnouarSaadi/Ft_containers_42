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
		T					data;
		struct node		*right;
		struct node		*left;
		struct node		*parent;
		enum COLOR			color;
	};
	// Template class tree
	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class tree
	{
	private:
		typedef T								value_type;
		typedef value_type*						pointer;
		typedef value_type&						reference;
		typedef struct node<value_type>					node;

		node* root;
		node* end;

	public:
		tree(): root(nullptr), end(nullptr)
		{
			end = newNode();
			end->left = root;
			std::cout << "Default: root: " << root << " end: " << end << std::endl;
		}

		~tree()
		{

		}
		// New node creation
		node* newNode(value_type data = value_type())
		{
			node* _new = new node();
			_new->data = data;
			_new->right = end;
			_new->left = end;
			_new->parent = end;
			_new->color = BLACK;
			return (_new);
		}
		// Search operation
		node* find(value_type data)
		{
			node* current = this->root;
			while (current != this->end) {
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
			node *n, *y, *tmp;
			if (this->root == nullptr)
			{
				this->root = newNode(data);
				return ;
			}
			if (find(data) == end)
				return ;
			n = newNode(data);
			y = this->end;
			tmp = this->root;
			while (tmp != this->end)
			{
				y = tmp;
				tmp = (n->data > y->data) ? tmp->left : tmp->right; // must be replaced by Compare
				n->parent = y;
			}
			if (y == this->end)
				this->root = n;
			else if (n->data < y->data) // must be replaced by Compare
				y->left = n;
			else
				y->right = n;
			n->color = RED;
		}
		
		// Inorder Travers
		void inorderHelp(node *x)
		{
			if (x != this->end)
			{
				inorderHelp(x->left);
				std::cout <<  "Node: Data: " <<x->data << " Add: " << x  << std::endl;
				(x->left != this->end) ? std::cout << "\tLeft Child: Data: " << x->left->data << " Add: " << x->left<< std::endl : std::cout <<  "\tLeft Child: "<< x->left << std::endl;
				(x->right != this->end) ? std::cout << "\t\tRight Child: Data: " <<x->right->data << " Add: " << x->right<< std::endl : std::cout<<  "\t\tRight Child: "<< x->right << std::endl;
				inorderHelp(x->right);
			}
		}

		void inorder()
		{
			this->inorderHelp(this->root);
		}

	};
}

#endif