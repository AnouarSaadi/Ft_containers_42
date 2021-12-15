#include <cstdlib>
#include <iostream>
#include <iomanip>

typedef struct node {
	int key;
	struct node *right;
	struct node *left;
} _Node;

_Node * newNode(int key);

int treeHeight(_Node * &x);

_Node* searchIterative(_Node* root, int key);

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
	return (pivot); // new root of the rotated subtree
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
	return (pivot); // new root of the rotated subtree
}

int balanceFactor(_Node *node)
{
	if (!node)
		return (0);
	if (node->right && node->left)
		return (treeHeight(node->right) - treeHeight(node->left));
	else if (node->right && node->left == NULL)
		return (treeHeight(node->right));
	else if (node->left && node->right == NULL)
		return (-treeHeight(node->left));
	return (0);
}

_Node * insertNodeAVL(_Node * &root, _Node *&_new)
{
	if (searchIterative(root, _new->key))
		return (root);
	if (!root)
	{
		root = _new;
		return (root);
	}
	else if (_new->key < root->key)
		root->left = insertNodeAVL(root->left, _new);
	else if (_new->key > root->key)
		root->right = insertNodeAVL(root->right, _new);
	int bf = balanceFactor(root);
	std::cout << "^^^Insertion bf = [ " << std::setw(2) << bf << " ] " << std::endl;
	// Left
	if (bf < -1 && _new->key < root->left->key)
		root = rightRotation(root);
	// Right
	if (bf > 1 && _new->key > root->right->key)
		root = leftRotation(root);
	// Left Right
	if (bf < -1 && _new->key > root->left->key)
	{
		// the node added into the right of root
		root->left = leftRotation(root->left);
		root = rightRotation(root);
	}
	// Right Left
	if (bf > 1 && _new->key < root->right->key)
	{
		// the node added into the left of root
		root->right = rightRotation(root->right);
		root = leftRotation(root);
	}
	return (root);
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
	while (x->left)
		x = x->left;
	return (x);
}

_Node * deleteNodeAVL(_Node * root, _Node *_node)
{
	// Recursive deletion
	if (root->left == NULL && root->right == NULL)
	{
		delete root;
		return NULL;
	}
	if (_node->key < root->key)
	{
		root->left = deleteNodeAVL(root->left, _node);
	}
	else if (_node->key >root->key)
	{
		root->right = deleteNodeAVL(root->right, _node);
	}
	else
	{
		if (root->left)
		{
			_Node *tmp = treePre(root->left);
			root->key = tmp->key;
			root->left = deleteNodeAVL(root->left, _node);
		}
		else
		{
			_Node *tmp = treeSuc(root->right);
			root->key = tmp->key;
			root->right = deleteNodeAVL(root->right, _node);
		}
	}
	return root;
}

void inorder(_Node *x)
{
	if (x != NULL)
	{
		inorder(x->left);
		std::cout << "__#__INORDER: " << x->key << " : " << x << " : " << x->left <<" : "<< x->right << std::endl;
		inorder(x->right);
	}
}

void preorder(_Node *x)
{
	if (x != NULL)
	{
		std::cout << "__#__PRORDER: " << x->key << " : " << x << " : " << x->left <<" : "<< x->right << std::endl;
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
		std::cout << "__#__POSTORDER: " << x->key << " : " << x << " : " << x->left <<" : "<< x->right << std::endl;
	}
}


int main()
{
	_Node *root = NULL;
	_Node *x[10];
	x[0] = newNode(10);
	x[1] = newNode(30);
	x[2] = newNode(20);
	x[3] = newNode(40);
	x[4] = newNode(50);
	x[5] = newNode(60);
	x[6] = newNode(95);
	x[7] = newNode(11);
	x[8] = newNode(99);
	x[9] = newNode(97);
	for (int i = 0; i < 10; i++)
		root = insertNodeAVL(root, x[i]);
	inorder(root);
	// for (int i = 0; i < 10; i++)
	// 	root = deleteNodeAVL(root, x[i]);
	// root = deleteNodeAVL(root, x[3]);
	// deleteNodeAVL(root, x[3]);
	// deleteNodeAVL(root, x[5]);
	// deleteNodeAVL(root, x[1]);
	// deleteNodeAVL(root, x[6]);
	// deleteNodeAVL(root, x[2]);
	std::cout << "_#_#_#_#_# bf = " << std::setw(2) << balanceFactor(root) << std::endl;
	inorder(root);

	std::cout << "_____Root  : " << root->key << " : " << root <<" | " << root->left << " | " << root->right << std::endl;
	_Node *srIter = searchIterative(root, x[3]->key);
	if (srIter)
		std::cout << "_____Search: " << srIter->key << " : " << srIter << " | " << srIter->left << " | " << srIter->right << std::endl;
}