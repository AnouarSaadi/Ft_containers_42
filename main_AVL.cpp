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

_Node* leftRotate(_Node *x)
{
	std::cout << "---> Left Rotate" << std::endl;

	_Node *y = x->right;
	_Node *tmp = y->left;
	if (y->left != nullptr)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent != nullptr)
	{
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	y->left = x;
	x->right = tmp;
	x->parent = y;
	x->height = std::max(nodeHeight(x->right), nodeHeight(x->left)) + 1;
	y->height = std::max(nodeHeight(y->right), nodeHeight(y->left)) + 1;
 	return (y); // new root of the rotated subtree
}

_Node* rightRotate(_Node *x)
{
	std::cout << "---> Right Rotate" << std::endl;
	_Node *y = x->left;
	_Node *tmp = y->right;
	if (y->right != nullptr)
		y->right->parent = x;
	y->parent = x->parent;
	if (x->parent != nullptr)
	{
		if (x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->right = y;
	}
	y->right = x;
	x->left = tmp;
	x->parent = y;
	x->height = std::max(nodeHeight(x->right), nodeHeight(x->left)) + 1;
	y->height = std::max(nodeHeight(y->right), nodeHeight(y->left)) + 1;
	return (y); // new root of the rotated subtree
}

int getBalanceFactor(_Node *node)
{
	if (!node)
		return (0);
	// if (node->right && node->left)
	// 	return (node->right->height - node->left->height);
	// else if (node->right && node->left == nullptr)
	// 	return (node->right->height);
	// else if (node->left && node->right == nullptr)
	// 	return (-node->left->height);
	return (nodeHeight(node->right) - nodeHeight(node->left));
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
	// case1: the data will be inserted into the left child
	else if (data < root->data)
	{
		root->left = insertNodeAVL(root->left, data);
		root->left->parent = root;
	}
	// case2: the data will be inserted into the right child
	else if (data > root->data)
	{
		root->right = insertNodeAVL(root->right, data);
		root->right->parent = root;
	}
	// Update the height of the node
	root->height = 1 + std::max(nodeHeight(root->right), nodeHeight(root->left));
	std::cout << "Height: " << root->height << std::endl;
	int bf = getBalanceFactor(root);
	std::cout << "Insertion: Balance factor before balancing = [ " << std::setw(2) << bf << " ] " << std::endl;
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
	bf = getBalanceFactor(root);
	std::cout << "Insertion: Balance factor after balancing = [ " << std::setw(2) << bf << " ] " << std::endl;
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
	_Node *y = x;
	while (y->left != nullptr)
		y = y->left;
	return (y);
}

_Node * deleteNodeAVL(_Node * root, int data)
{
	_Node *tmp = nullptr;
	_Node *_node = nullptr;
	if (!root || !(_node = searchIterative(root, data)))
		return (root);
	if (_node->data < root->data)
		root->left = deleteNodeAVL(root->left, _node->data);
	else if (_node->data >root->data)
		root->right = deleteNodeAVL(root->right, _node->data);
	else
	{
		if (root->left == nullptr || root->right == nullptr)
		{
			tmp = (root->right != NULL) ? root->right : root->left;
			if (tmp == nullptr)
			{
				// std::cout << "_Content of root1: " << root /*<<" : "<< root->data << " : "<< root->left << " : " << root->right */<< std::endl;
				tmp = root;
				root = nullptr;
				// std::cout << "_Content of root1: " << root /*<<" : "<< root->data << " : "<< root->left << " : " << root->right */<< std::endl;
			}
			else
			{
				// std::cout << "_Content of root: " << root <<" : "<< root->data << " : "<< root->left << " : " << root->right << std::endl;
				*root = *tmp;
				// std::cout << "_Content of root: " << root <<" : "<< root->data << " : "<< root->left << " : " << root->right << std::endl;
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
	int bf = getBalanceFactor(root);
	std::cout << "Deletion: Balance factor before balancing = [ " << std::setw(2) << bf << " ] " << std::endl;
	// Rebalancing
	// Right

	if (bf > 1 && getBalanceFactor(root->left) >= 0) // ! check the conditions []
		root = leftRotate(root);
	// Left Right
	if (bf > 1 && getBalanceFactor(root->left) < 0)
	{
		root->right = rightRotate(root->right);
		root = leftRotate(root);
	}
	// Left
	if (bf < -1 && getBalanceFactor(root->right) <= 0)
		root = rightRotate(root);
	// Right Left
	if (bf < -1  && getBalanceFactor(root->right) > 0)
	{
		// the node added into the left of root
		root->left = leftRotate(root->left);
		root = rightRotate(root);
	}
	//
	bf = getBalanceFactor(root);
	std::cout << "Deletion: Balance factor after balancing = [ " << std::setw(2) << bf << " ] " << std::endl;

	return root;
}

void inorder(_Node *x)
{
	if (x != nullptr)
	{
		inorder(x->left);
		std::cout <<"Node: Data: " <<x->data << " Add: " << x << std::endl;
		(x->left) ? std::cout << "\t-Left Child: Data: " << x->left->data << " Add: " << x->left<< std::endl : std::cout <<  "\t-Left Child: "<<x->left << std::endl;
		(x->right) ? std::cout << "\t\t-Right Child: Data: " <<x->right->data << " Add: " << x->right<< std::endl : std::cout<<  "\t\t-Right Child: "<<x->right << std::endl;
		std::cout << std::endl;
		inorder(x->right);
	}
}

void preorder(_Node *x)
{
	if (x != nullptr)
	{
		std::cout << x->data << " ";
		preorder(x->left);
		preorder(x->right);
	}
}

void postorder(_Node *x)
{
	if (x != nullptr)
	{
		postorder(x->left);
		postorder(x->right);
		std::cout << x->data << " ";
	}
}

int main()
{
	_Node *root = nullptr;
	int x[10];
	x[0] = 10;
	x[1] = 30;
	x[2] = 20;
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
	root = deleteNodeAVL(root, 50);
	std::cout << "Deleleting of 50: Done!" << std::endl;
	root = deleteNodeAVL(root, 97);
	// root = deleteNodeAVL(root, 30);
	// root = deleteNodeAVL(root, 20);
	inorder(root);
	// for (int i = 0; i < 10; i++)
	// {
	// 	root = deleteNodeAVL(root, x[i]);
	// 	// _Node * f= searchIterative(root, x[i]);
	// 	inorder(root);
	// }
	// // root = deleteNodeAVL(root, x[3]);
	std::cout << "_#_#_#_#_# bf = " << std::setw(2) << getBalanceFactor(root) << std::endl;

	std::cout << "_____Root  : " << root->data << " : " << root <<" | " << root->left << " | " << root->right << std::endl;
	// _Node *srIter = searchIterative(root, x[3]);
	// if (srIter)
	// 	std::cout << "_____Search: " << srIter->data << " : " << srIter << " | " << srIter->left << " | " << srIter->right << std::endl;
}