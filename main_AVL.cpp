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

void leftRotation(_Node *&root,_Node* &x)
{
// ! Let Q be P's right child.
// ! Set P's right child to be Q's left child.
// ! [Set Q's left-child's parent to P]
// ! Set Q's left child to be P.
// ! [Set P's parent to Q]
	(void) root;
	_Node *tmp = x->right;
	x->right = tmp->left;
	_Node *parent = findParent(root, tmp);
	if (!parent)
		parent = root;
	parent->left = x;
	std::cout << "_____parent: " << parent << std::endl;
	_Node *xparent = findParent(root, x);
	xparent = tmp;
	

}

void insertNodeAVL(_Node * &root, _Node *&_new)
{
	if (searchIterative(root, _new->key))
		return ;
	_Node *y = NULL;
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
		y = _new;
		root = y;
	}
	else if (_new->key < y->key)
		y->left = _new;
	else
		y->right = _new;
	// ! Calculing the Height
	_Node *yParent = findParent(root, y);
	if (!yParent)
		yParent = root;
	int _BF = treeHeight(yParent->right) - treeHeight(yParent->left);
	std::cout << "_____BF(Y) = " << _BF << std::endl;
	if (_BF > 1 || _BF < -1) // ? the balance factor has been out of the range [-1, 1]
	{
		std::cout << "_____Unbalanced" << std::endl;
		if (_BF < 1)
			std::cout << "_____Rotation to right" << std::endl;
		else
		{
			std::cout << "_____LeftRotation" << std::endl;
			std::cout << "_____Address: " << yParent << " | " << y << std::endl;
			leftRotation(root, yParent);
			std::cout << "_____Address: " << yParent << " | " << y << std::endl;
		}
		// ! Add the rotation functions
	}
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
	
	// for (int i = 0; i < 10; i++)
	// 	deleteNode(root, x[i]);
	// std::cout << "____Height____ " << treeHeight(root) << std::endl;
		 

	std::cout << "_____Root_____" << root << std::endl;
	_Node *srIter = searchIterative(root, x[0]->key);
	if (srIter)
		std::cout << " ____Search: " << srIter->key << " | " << srIter->left << " | " << srIter->right << std::endl;
	else
		std::cout << " ____Search: Node not found" << std::endl;
}