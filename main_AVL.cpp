#include <cstdlib>
#include <iostream>

typedef struct node {
	int key;
	struct node *right;
	struct node *left;
} _Node;

_Node * newNode(int key);

int treeHeight(_Node * x);

_Node* searchIterative(_Node* root, int key);

// _Node *treeMax(_Node *x);

_Node* findParent(_Node * &root, _Node * &_node);

/* LeftRotation */
/*

 ? Pivot = Root.OS
 ? Root.OS = Pivot.RS
 ? Pivot.RS = Root
 ? Root = Pivot

*/

void leftRotation(_Node * &root, _Node * &pivot)
{
	std::cout << "_____root of pivot: " << root << " # " << root->left << " # " << root->right << std::endl;
	std::cout << "_____pivot: " << pivot << " # " << pivot->left << " # " << pivot->right << std::endl;
	pivot = root->right;
	root->right = pivot->left;
	pivot->left = root;
	root = pivot;
	std::cout << "_____root of pivot: " << root << " # " << root->left << " # " << root->right << std::endl;
	std::cout << "_____pivot: " << pivot << " # " << pivot->left << " # " << pivot->right << std::endl;
}

_Node * rightRotation(_Node* &x)
{
	_Node *y = x->left;
	_Node *tmp = y->right;

	y->right = x;
	x->left = tmp;
	return (y);
}

void insertNodeAVL(_Node * &root, _Node *&_new)
{
	if (searchIterative(root, _new->key))
		return ;
	_Node *y = root;
	_Node *x = root;
	while (x != NULL)
	{
		y = x;
		if (_new->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	if (!y)
	{
		root = _new;
		y = root;
	}
	else if (_new->key < y->key)
		y->left = _new;
	else
		y->right = _new;
	// for(;;)
	// {
	// _Node *parent = findParent(root, y);
	// std::cout << " " << parent->key << y->key << std::endl;
		int _BF = treeHeight(root->right) - treeHeight(root->left);
		std::cout << "\t_____BF(Y) = " << _BF << std::endl;
		if (_BF >= -1 && _BF <= 1)
			std::cout << "\t_____Balanced" << std::endl;
			// break ;
		else // ? the balance factor has been out of the range [-1, 1]
		{
			if (_BF < 1)
			{
				// y = rightRotation(y);
				std::cout << "\t_____rightRotation" << std::endl;
			}
			else
			{
				std::cout << "\t_____LeftRotation" << std::endl;
				// _Node *yPar = findParent(root, y);
				leftRotation(root, y);
			}
		}
	// }
}

int main()
{
	_Node *root = NULL;
	_Node *x[10];
	x[0] = newNode(49);
	x[1] = newNode(51);
	x[2] = newNode(29);
	x[3] = newNode(42);
	x[4] = newNode(5);
	x[5] = newNode(37);
	x[6] = newNode(95);
	x[7] = newNode(11);
	x[8] = newNode(101);
	x[9] = newNode(99);
	// for (int i = 0; i < 10; i++)
		// insertNodeAVL(root, x[i]);
	std::cout << "____x[0]: " << x[0] << std::endl;
	insertNodeAVL(root, x[0]);
	std::cout << "____x[1]: " << x[1] << std::endl;
	insertNodeAVL(root, x[1]);
	std::cout << "____x[6]: " << x[6] << std::endl;
	insertNodeAVL(root, x[6]);
	// std::cout << "____x[9]: " << x[9] << std::endl;
	// insertNodeAVL(root, x[9]);
	// std::cout << "____x[8]: " << x[8] << std::endl;
	// insertNodeAVL(root, x[8]);
	
	// for (int i = 0; i < 10; i++)
	// 	deleteNode(root, x[i]);
	// std::cout << "____Height____ " << treeHeight(root) << std::endl;
		 

	std::cout << "_____Root_____" << root << " | " << root->left << " | " << root->right << std::endl;
	_Node *srIter = searchIterative(root, x[1]->key);
	if (srIter)
		std::cout << " ____Search: " << srIter->key << " | " << srIter->left << " | " << srIter->right << std::endl;
	else
		std::cout << "_____Search: Node not found" << std::endl;
}