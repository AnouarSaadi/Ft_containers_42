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

void leftRotation(_Node * &root, _Node * &x)
{
	_Node *y = x->right;
	std::cout << "_____x: " << x << " | " << x->right << " | " << x->left << std::endl;
	std::cout << "_____y: " << y << " | " << y->right << " | " << y->left << std::endl;
	x->right = y->left;
	if (!(y->left))
	{
	std::cout << "_____Debug00: " << y->left <<std::endl;
		_Node *yleftPar = findParent(root, y->left);
		yleftPar = x;
	}
	// _Node *yPar = findParent(root, y);
	// _Node *xPar = findParent(root, x);
	// xPar = yPar;
	// if (!xPar)
	// 	root = y;
	// else if (x == xPar->left)
	// 	xPar->left = y;
	// else
	// 	xPar->right = y;
	// y->left = x;
	// xPar = y;
	// (void)root;
	// _Node *y = x->right;
	// _Node *tmp = y->left;
	// std::cout << "_____x: " << x << " | " << x->right << " | " << x->left << std::endl;
	// std::cout << "_____y: " << y << " | " << y->right << " | " << y->left << std::endl;
	// std::cout << "_____tmp: " << tmp << std::endl;//<< " | " << tmp->right << " | " << tmp->left << std::endl;
	// y->left = x;
	// x->right = tmp;
	// std::cout << "_____x: " << x << " | " << x->right << " | " << x->left << std::endl;
	// std::cout << "_____y: " << y << " | " << y->right << " | " << y->left << std::endl;
	// std::cout << "_____tmp: " << tmp << std::endl;

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
	// std::cout << "_____Here: " << y->key << std::endl;
	// for(;;)
	// {
	// _Node *parent = findParent(root, y);
	// std::cout << " " << parent->key << y->key << std::endl;
		int _BF = treeHeight(root->right) - treeHeight(root->left);
		std::cout << "_____BF(Y) = " << _BF << std::endl;
		if (_BF >= -1 && _BF <= 1)
			std::cout << "____Balanced" << std::endl;
			// break ;
		else // ? the balance factor has been out of the range [-1, 1]
		{
			if (_BF < 1)
			{
				// y = rightRotation(y);
				std::cout << "_____rightRotation" << std::endl;
			}
			else
			{
				std::cout << "_____LeftRotation" << std::endl;
				// std::cout << "_____Address: " << " | " << y << std::endl;
				leftRotation(root, y);
				// std::cout << "_____Address: " << " | " << y << std::endl;
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
	x[8] = newNode(72);
	x[9] = newNode(99);
	// for (int i = 0; i < 10; i++)
		// insertNodeAVL(root, x[i]);
	insertNodeAVL(root, x[0]);
	insertNodeAVL(root, x[1]);
	insertNodeAVL(root, x[6]);
	// insertNodeAVL(root, x[9]);
	// insertNodeAVL(root, x[9]);
	
	// for (int i = 0; i < 10; i++)
	// 	deleteNode(root, x[i]);
	// std::cout << "____Height____ " << treeHeight(root) << std::endl;
		 

	std::cout << "_____Root_____" << root << std::endl;
	_Node *srIter = searchIterative(root, x[1]->key);
	if (srIter)
		std::cout << " ____Search: " << srIter->key << " | " << srIter->left << " | " << srIter->right << std::endl;
	else
		std::cout << "_____Search: Node not found" << std::endl;
}