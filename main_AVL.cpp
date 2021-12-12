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

_Node * leftRotation(_Node * node)
{
	std::cout << std::endl;
	std::cout << "_____node : " << node << " # " << node->left << " # " << node->right << std::endl;
	_Node *pivot = node->right;
	_Node *tpnode = pivot->left;
	pivot->left = node;
	node->right = tpnode;
	std::cout << "_____node : " << node << " # " << node->left << " # " << node->right << std::endl;
	std::cout << std::endl;
	return pivot;
}

_Node * rightRotation(_Node* node)
{
	_Node *y = x->left;
	_Node *tmp = y->right;

	y->right = x;
	x->left = tmp;
	return (y);
}

int balanceFactor(_Node *node)
{
	int right = treeHeight(node->right);
	return (right - treeHeight(node->left));
}

_Node * insertNodeAVL(_Node * &root, _Node *&_new)
{
	if (searchIterative(root, _new->key))
		return root;
	if (!root)
	{
		root = _new;
		return root;
	}
	else if (_new->key < root->key)
		root->left = insertNodeAVL(root->left, _new);
	else if (_new->key > root->key)
		root->right = insertNodeAVL(root->right, _new);
	if (balanceFactor(root) > 1)
		root = leftRotation(root);
	else if (balanceFactor(root) < -1)
		root = rightRotation(root);
	return root;
	/*
	// _Node *parent = findParent(root, y);
	// std::cout << " " << parent->key << y->key << std::endl;
		// std::cout << "\t_____BF(Y) = " << _BF << std::endl;
		// if (_BF >= -1 && _BF <= 1)
		// 	std::cout << "\t_____Balanced" << std::endl;
		// 	// break ;
		// else // ? the balance factor has been out of the range [-1, 1]
		// {
		// 	if (_BF < 1)
		// 	{
		// 		// y = rightRotation(y);
		// 		std::cout << "\t_____rightRotation" << std::endl;
		// 	}
		// 	else
		// 	{
		// 		std::cout << "\t_____LeftRotation" << std::endl;
		// 		// _Node *yPar = findParent(root, y);
		// 		leftRotation(root, y);
		// 	}
		// }
	// }
	*/
}

int main()
{
	_Node *root = NULL;
	_Node *x[10];
	x[0] = newNode(10);
	x[1] = newNode(20);
	x[2] = newNode(30);
	x[3] = newNode(40);
	x[4] = newNode(50);
	x[5] = newNode(60);
	x[6] = newNode(95);
	x[7] = newNode(11);
	x[8] = newNode(101);
	x[9] = newNode(99);
	// for (int i = 0; i < 10; i++)
		// insertNodeAVL(root, x[i]);
	std::cout << "____x[0]: " << x[0] << std::endl;
	root = insertNodeAVL(root, x[0]);
	std::cout << "____x[1]: " << x[1] << std::endl;
	root = insertNodeAVL(root, x[1]);
	std::cout << "____x[6]: " << x[2] << std::endl;
	root = insertNodeAVL(root, x[2]);
	std::cout << "____x[9]: " << x[3] << std::endl;
	root = insertNodeAVL(root, x[3]);
	std::cout << "____x[8]: " << x[4] << std::endl;
	root = insertNodeAVL(root, x[4]);
	
	// for (int i = 0; i < 10; i++)
	// 	deleteNode(root, x[i]);
	// std::cout << "____Height____ " << treeHeight(root) << std::endl;
		 

	std::cout << "_____Root_____" << root->key << " | " << root->left << " | " << root->right << std::endl;
	_Node *srIter = searchIterative(root, x[3]->key);
	if (srIter)
		std::cout << " ____Search: " << srIter->key << " | " << srIter->left->key << " | " << srIter->right->key << std::endl;
}