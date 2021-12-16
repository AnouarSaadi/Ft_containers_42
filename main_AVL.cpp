#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <map>

typedef struct node {
	int			data;
	struct node	*right;
	struct node	*left;
	struct node	*parent;
	size_t		height;
} _Node;

_Node * newNode(int data);

size_t nodeHeight(_Node *x);

_Node* searchIterative(_Node* root, int data);

_Node* findParent(_Node * &root, _Node * &_node);

/* Rotations algorithm */
/*

 ? Pivot = Root.OS
 ? Root.OS = Pivot.RS
 ? Pivot.RS = Root
 ? Root = Pivot

*/

_Node * leftRotation(_Node * root)
{
	std::cout << "---> Left Rotation" << std::endl;
	_Node *pivot;
	_Node *tmp;

	pivot = root->right;
	tmp = pivot->left;
	pivot->left = root;
	root->right = tmp;
    root->height = std::max(nodeHeight(root->right), nodeHeight(root->left)) + 1;
    pivot->height = std::max(nodeHeight(pivot->right), nodeHeight(pivot->left)) + 1;
	return (pivot); // new root of the rotated subtree
}

// Let Q be P's right child.
// Set P's right child to be Q's left child.
// [Set Q's left-child's parent to P]
// Set Q's left child to be P.
// [Set P's parent to Q]
_Node* leftRotate(_Node *x)
{
	std::cout << "---> Left Rotate" << std::endl;

	_Node *y = x->right;
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;
	y->left = x;
	x->parent = y;
	if (y != NULL)
		y->height = std::max(nodeHeight(y->right), nodeHeight(y->left));
	if (x != NULL)
		x->height = std::max(nodeHeight(x->right), nodeHeight(x->left));
	return (y);
}

// Let P be Q's left child.
// Set Q's left child to be P's right child.
// [Set P's right-child's parent to Q]
// Set P's right child to be Q.
// [Set Q's parent to P]
_Node* rightRotate(_Node *x)
{
	std::cout << "---> Right Rotate" << std::endl;
	_Node *y = x->left;
	x->left = y->right;
	if (y->right != NULL)
		y->right->parent = x;
	y->right = x;
	x->parent = y;
	if (y != NULL)
		y->height = std::max(nodeHeight(y->right), nodeHeight(y->left));
	if (x != NULL)
		x->height = std::max(nodeHeight(x->right), nodeHeight(x->left));
	return (y);
}

_Node * rightRotation(_Node* root)
{
	std::cout << "---> Right Rotation" << std::endl;
	_Node *pivot;
	_Node *tmp;

	pivot = root->left;
	tmp = pivot->right;
	pivot->right = root;
	root->left = tmp;
	root->height = std::max(nodeHeight(root->right), nodeHeight(root->left)) + 1;
    pivot->height = std::max(nodeHeight(pivot->right), nodeHeight(pivot->left)) + 1;
	return (pivot); // new root of the rotated subtree
}

int balanceFactor(_Node *node)
{
	if (!node)
		return (0);
	if (node->right && node->left)
		return (node->right->height - node->left->height);
	else if (node->right && node->left == NULL)
		return (node->right->height);
	else if (node->left && node->right == NULL)
		return (-node->left->height);
	return (0);
}

_Node * insertNodeAVL(_Node * &root, int data)
{
	// RECURSION
	if (searchIterative(root, data))
		return (root);
	if (!root)
	{
		root = newNode(data);
		return (root);
	}
	else if (data < root->data)
	{
		root->left = insertNodeAVL(root->left, data);
		root->left->parent = root;
	}
	else if (data > root->data)
	{
		root->right = insertNodeAVL(root->right, data);
		root->right->parent = root;
	}
	root->height = 1 + std::max(nodeHeight(root->right), nodeHeight(root->left));
	int bf = balanceFactor(root);
	std::cout << "Insertion bf = [ " << std::setw(2) << bf << " ] " << std::endl;
	// Left
	if (bf < -1 && data < root->left->data)
		root = rightRotate(root);
	// Right
	else if (bf > 1 && data > root->right->data)
		root = leftRotate(root);
	// Left Right
	else if (bf < -1 && data > root->left->data)
	{
		// the node added into the right of root
		root->left = leftRotate(root->left);
		root = rightRotate(root);
	}
	// Right Left
	else if (bf > 1 && data < root->right->data)
	{
		// the node added into the left of root
		root->right = rightRotate(root->right);
		root = leftRotate(root);
	}
	return (root);
	// ITERATIVE
	/*
	if (searchIterative(root, data))
		return root;
	_Node *y = NULL;
	_Node *x = root;
	while (x != NULL)
	{
		y = x;
		if (data < x->data)
			x = x->left;
		else
			x = x->right;
	}
	if (!y)
	{
		root = newNode(data);
		y = root;
	}
	else if (data < y->data)
	{
		y->left = newNode(data);
		y->left->parent = y;
	}
	else
	{
		y->right = newNode(data);
		y->right->parent = y;
	}
	y->height = std::max(nodeHeight(y->right), nodeHeight(y->left)) + 1;
	int bf = balanceFactor(y->parent);
	std::cout << "balance factor = " << std::setw(2) << bf << std::endl;
	return (root);
	*/
}


// Deletion
_Node * treeSuc(_Node * x)
{
	while (x->right)
		x = x->right;
	return (x);
}

_Node * treePre(_Node * x)
{
	_Node *y = x;
	while (y->left)
		y = y->left;
	return (y);
}

_Node * deleteNodeAVL(_Node * root, int data)
{
	_Node *tmp = NULL;
	_Node *_node = NULL;
	if (!root || !(_node = searchIterative(root, data)))
		return (root);
	if (_node->data < root->data)
		root->left = deleteNodeAVL(root->left, _node->data);
	else if (_node->data >root->data)
		root->right = deleteNodeAVL(root->right, _node->data);
	else
	{
		if (root->left == NULL || root->right == NULL)
		{
			tmp = (root->right) ? root->right : root->left;
			if (tmp == NULL)
			{
				std::cout << "_Content of root1: " << root <<" : "/*<< root->data << " : "<< root->left << " : " << root->right */<< std::endl;
				tmp = root;
				root = NULL;
				std::cout << "_Content of root1: " << root <<" : "/*<< root->data << " : "<< root->left << " : " << root->right */<< std::endl;
			}
			else
			{
				std::cout << "_Content of root: " << root <<" : "<< root->data << " : "<< root->left << " : " << root->right << std::endl;
				*root = *tmp;
				std::cout << "_Content of root: " << root <<" : "<< root->data << " : "<< root->left << " : " << root->right << std::endl;
			}
			free(tmp);
		}
		else
		{
			tmp = treePre(root->right);
			root->data = tmp->data;
			root->right = deleteNodeAVL(root->right, tmp->data);
		}
	}
	if (!root)
		return (root);
	root->height = std::max(nodeHeight(root->right), nodeHeight(root->left)) + 1;
	int bf = balanceFactor(root);
	std::cout << "^^^Deletion bf = [ " << std::setw(2) << bf << " ] " << std::endl;

	return root;
}

void inorder(_Node *x)
{
	if (x != NULL)
	{
		inorder(x->left);
		std::cout << x->data << " ";
		inorder(x->right);
	}
}

void preorder(_Node *x)
{
	if (x != NULL)
	{
		std::cout << x->data << " ";
		preorder(x->left);
		preorder(x->right);
	}
}

void postorder(_Node *x)
{
	if (x != NULL)
	{
		postorder(x->left);
		postorder(x->right);
		std::cout << x->data << " ";
	}
}

int main()
{
	_Node *root = NULL;
	int x[10];
	x[0] = 10;
	x[1] = 20;
	x[2] = 30;
	x[3] = 40;
	x[4] = 50;
	x[5] = 60;
	x[6] = 95;
	x[7] = 11;
	x[8] = 99;
	x[9] = 97;
	for (int i = 0; i < 10; i++)
		root = insertNodeAVL(root, x[i]);
	inorder(root);
	std::cout << std::endl;
	// for (int i = 0; i < 10; i++)
	// {
	// 	root = deleteNodeAVL(root, x[i]);
	// 	// _Node * f= searchIterative(root, x[i]);
	// 	inorder(root);
	// std::cout << std::endl;
	// }
	// root = deleteNodeAVL(root, x[8]);
	// inorder(root);
	std::cout << "_#_#_#_#_# bf = " << std::setw(2) << balanceFactor(root) << std::endl;

	// std::cout << "_____Root  : " << root->data << " : " << root <<" | " << root->left << " | " << root->right << std::endl;
	_Node *srIter = searchIterative(root, x[3]);
	if (srIter)
		std::cout << "_____Search: " << srIter->data << " : " << srIter << " | " << srIter->left << " | " << srIter->right << std::endl;
}