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
	std::cout << " bf = [ " << std::setw(2) << bf << " ] " << std::endl;
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
void replaceNodes(_Node * &root, _Node * &_node1, _Node * &_node2);
_Node * treeSuccessor(_Node *root,_Node * x);

_Node * deleteNodeAVL(_Node * &root, _Node *_node)
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
	// std::cout << "____x[0]: " << x[0] << std::endl;
	// root = insertNodeAVL(root, x[0]);
	// std::cout << "____x[1]: " << x[1] << std::endl;
	// root = insertNodeAVL(root, x[1]);
	// std::cout << "____x[2]: " << x[2] << std::endl;
	// root = insertNodeAVL(root, x[2]);
	// std::cout << "____x[3]: " << x[3] << std::endl;
	// root = insertNodeAVL(root, x[3]);
	// std::cout << "____x[4]: " << x[4] << std::endl;
	// root = insertNodeAVL(root, x[4]);
	// std::cout << "____x[5]: " << x[5] << std::endl;
	// root = insertNodeAVL(root, x[5]);
	inorder(root);
	// std::cout << "Height: " << treeHeight(root) << std::endl;
	// for (int i = 0; i < 10; i++)
	// 	deleteNode(root, x[i]);
	// std::cout << "____Height____ " << treeHeight(root) << std::endl;
	std::cout << "_____Root  : " << root->key << " : " << root <<" | " << root->left << " | " << root->right << std::endl;
	_Node *srIter = searchIterative(root, x[3]->key);
	if (srIter)
		std::cout << "_____Search: " << srIter->key << " : " << srIter << " | " << srIter->left << " | " << srIter->right << std::endl;
}