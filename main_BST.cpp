#include <cstdlib>
#include <iostream>

typedef struct node {
	int key;
	struct node *right;
	struct node *left;
} _Node;

_Node * newNode(int key)
{
	_Node * _new = new _Node();
	_new->key = key;
	_new->right = NULL;
	_new->left = NULL;
	return (_new);
}

/* Height function use for determining the height of the given node */
size_t treeHeight(_Node *&x)
{
	if (!x)
		return (0);
	size_t leftHeight = treeHeight(x->left);
	size_t rightHeight = treeHeight(x->right);
	return (std::max(rightHeight, leftHeight) + 1);
}

// Searching
_Node* searchRecursicve(_Node* &root, int key)
{
	if (root->key == key || !root)
		return root;
	if (key < root->key)
		return (searchRecursicve(root->left, key));
	else
		return (searchRecursicve(root->right, key));
}

_Node* searchIterative(_Node* root, int key)
{
	_Node * x = root;
	while (x && x->key != key)
	{
		if (key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	return (x);
}

/* Insertion of the given node _new into the BST tree roo t*/
void insertNode(_Node * &root, _Node *&_new)
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
		root = _new;
	else if (_new->key < y->key)
		y->left = _new;
	else
		y->right = _new;
}

/* Getting the Maximun of the given node */
_Node *treeMax(_Node *x)
{
	while(x->right)
		x = x->right;
	return (x);
}

/* Getting the minimun of the given node */
_Node *treeMin(_Node *x)
{
	while(x->left)
		x = x->left;
	return (x);
}

/* The findParent function used to find the parent of the given node */
_Node*  findParent(_Node * &root, _Node * &_node)
{
	_Node * parent = NULL;
	if (!searchIterative(root, _node->key) || root == _node)
		return (root);
	parent = root;
	if (parent->left == _node || parent->right == _node)
		return (parent);
	if (parent->key > _node->key)
		parent = findParent(parent->left, _node);
	if (parent->key < _node->key)
		parent = findParent(parent->right, _node);
	return (parent);
}

/* treeSuccessor used to determine the successor of given node (The smallest node in node in Right subtree) */
_Node * treeSuccessor(_Node *root,_Node * x)
{
	if (x->right)
		return (treeMin(x->right));
	_Node * xparent = findParent(root, x);
	_Node *y = xparent;
	_Node *yparent = findParent(root, y);
	while(y != NULL && x == y->right)
	{
		x = y;
		y = yparent;
	}
	std::cout << " @@@ ^HERE^ @@@" << std::endl;
	return (y);
}

/* Replacing the node1 with the node2 */
void replaceNodes(_Node * &root, _Node * &_node1, _Node * &_node2)
{
	_Node *parent1 = findParent(root, _node1);
	if (parent1 == NULL)
		root = _node2;
	else if (_node1 == parent1->left)
		parent1->left = _node2;
	else
		parent1->right = _node2;
}

void deleteNode(_Node* &root, _Node *&_node)
{
	if (!searchIterative(root, _node->key) || (!root))
		return ;
	if (!(_node->left))
		replaceNodes(root, _node, _node->right);
	else if (!(_node->right))
		replaceNodes(root, _node, _node->left);
	else
	{
		_Node * successor = treeSuccessor(root, _node);
		_Node * succPar = findParent(root, successor);
		if (succPar != _node)
		{
			replaceNodes(root, successor, successor->right);
			successor->right = _node->right;
			_Node *succRP = findParent(root, successor->right);
			succRP = successor;
		}
		replaceNodes(root, _node, successor);
		successor->left = _node->left;
		_Node *succLP = findParent(root, successor->left);
		succLP = successor;
	}
	delete _node;
}

// int main()
// {
// 	_Node *root = NULL;
// 	_Node *x[10];
// 	x[0] = newNode(49);
// 	x[1] = newNode(51);
// 	x[2] = newNode(29);
// 	x[3] = newNode(42);
// 	x[4] = newNode(5);
// 	x[5] = newNode(37);
// 	x[6] = newNode(95);
// 	x[7] = newNode(11);
// 	x[8] = newNode(72);
// 	x[9] = newNode(99);

// 	for (size_t i = 0; i < 10; i++)
// 		insertNode(root, x[i]);
// 	for (size_t i = 0; i < 10; i++)
// 		deleteNode(root, x[i]);
// 	// std::cout << "____Height____ " << treeHeight(root) << std::endl;
// 	std::cout << "_____Root_____" << root << std::endl;
// 	_Node *srIter = searchIterative(root, x[0]->key);
// 	if (srIter)
// 		std::cout << " ____Search___ " << srIter->key << " | " << srIter->left << " | " << srIter->right << std::endl;
// 	else
// 		std::cout << " ____Node not found ____" << std::endl;
// }