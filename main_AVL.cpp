#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <map>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

typedef struct node {
	int			data;
	struct node	*right;
	struct node	*left;
	struct node	*parent;
	size_t		height;
} _Node;

typedef struct avl_tree {
	_Node *root;
} avlTree;

_Node * newNode(int data);

size_t nodeHeight(_Node *x);

_Node* find(_Node* root, int data);

void subtreeShift(avlTree *tree, _Node *u, _Node *v)
{
	std::cout << "Replace " << u->parent << " parent of " << u << " by "<< v << std::endl;
	if (u->parent == nullptr)
		tree->root = v;
	else if (u == u->parent->left)
	{
		std::cout << "case left: " << u->parent->left << std::endl;
		u->parent->left = v;
		std::cout << "case left: " << u->parent->left << std::endl;
	}
	else
	{
		std::cout << "case right: " << u->parent->right << std::endl;
		u->parent->right = v;
	}
	if (v != NULL)
		v->parent = u->parent;
	std::cout << "After replace " << u << " by "<< v<< std::endl;
}

_Node *treeMin(_Node *x);
// RECURSION
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

// Iterative
void left_rotate(avlTree *tree,_Node *x)
{
	std::cout << "---> Left Rotate Iterative" << std::endl;

	_Node *y = x->right;
	_Node *tmp = y->left;
	if (y->left != nullptr)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == nullptr)
		tree->root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->right = tmp;
	x->parent = y;
	x->height = std::max(nodeHeight(x->right), nodeHeight(x->left)) + 1;
	y->height = std::max(nodeHeight(y->right), nodeHeight(y->left)) + 1;
}

void right_rotate(avlTree *tree, _Node *x)
{
	std::cout << "---> Right Rotate Iterative" << std::endl;
	_Node *y = x->left;
	_Node *tmp = y->right;
	if (y->right != nullptr)
		y->right->parent = x;
	y->parent = x->parent;
	if (x->parent == nullptr)
		tree->root = y;
	else if (x == x->parent->right)
		x->parent->right = y;
	else
		x->parent->right = y;
	y->right = x;
	x->left = tmp;
	x->parent = y;
	x->height = std::max(nodeHeight(x->right), nodeHeight(x->left)) + 1;
	y->height = std::max(nodeHeight(y->right), nodeHeight(y->left)) + 1;
}

int getBalanceFactor(_Node *node)
{
	return ((node == nullptr) ? 0 : (nodeHeight(node->right) - nodeHeight(node->left)));
}

_Node * insertNodeAVL(_Node * &root, int data)
{
	// RECURSION
	if (find(root, data))
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

_Node * minValueNode(_Node *node)
{
	_Node *current = node;
	while (current->left != nullptr)
	{
		current = current->left;
	}
	return current;
}

_Node * deleteNodeAVL(_Node * root, int data)
{
	_Node *tmp = nullptr;
	_Node *_node = nullptr;
	if (!root || !(_node = find(root, data)))
		return (root);
	if (_node->data < root->data)
		root->left = deleteNodeAVL(root->left, _node->data);
	else if (_node->data > root->data)
		root->right = deleteNodeAVL(root->right, _node->data);
	else
	{
		if (root->left == nullptr)
		{
			tmp = root->left;
			delete root;
			return tmp;
		}
		else if (root->right == nullptr)
		{
			tmp = root->right;
			delete root;
			return tmp;
		}
		else
		{
			tmp = minValueNode(root->right);
			std::cout << "Root: " << root << " Predecessor: " << tmp << std::endl;
			root->data = tmp->data;
			root->right = deleteNodeAVL(root->right, tmp->data);
		}
	}
	if (!root)
		return (root);
	// root->height = std::max(nodeHeight(root->right), nodeHeight(root->left)) + 1;
	int bf = getBalanceFactor(root);
	std::cout << "Deletion: Balance factor before balancing = [ " << std::setw(2) << bf << " ] " << std::endl;
	// Rebalancing
	// Right
	if (bf > 1 && getBalanceFactor(root->left) >= 0) // ! check the conditions []
	{	
		root = leftRotate(root);
	}
	// Left Right
	else if (bf > 1 && getBalanceFactor(root->left) < 0)
	{
		root->right = rightRotate(root->right);
		root = leftRotate(root);
	}
	// Left
	else if (bf < -1 && getBalanceFactor(root->right) <= 0)
	{
		root = rightRotate(root);
	}
	// Right Left
	else if (bf < -1  && getBalanceFactor(root->right) > 0)
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
		std::cout <<  "Node: Data: " <<x->data << " Add: " << x  << std::endl;
		(x->left) ? std::cout << "\tLeft Child: Data: " << x->left->data << " Add: " << x->left<< std::endl : std::cout <<  "\tLeft Child: "<<x->left << std::endl;
		(x->right) ? std::cout << "\t\tRight Child: Data: " <<x->right->data << " Add: " << x->right<< std::endl : std::cout<<  "\t\tRight Child: "<<x->right << std::endl;
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

size_t updateHeight(_Node *x)
{
	return (1 + std::max(nodeHeight(x->right), nodeHeight(x->left)));
}

void deletionBalance(avlTree *tree, _Node *node)
{
	std::cout << "deletionBalance" << std::endl;
	_Node *del = node;
	while (del != nullptr)
	{
		del->height = updateHeight(del);
		if (getBalanceFactor(del) <= -2 || getBalanceFactor(del) >= 2)
		{
			_Node *tmp = del;
			_Node *current = (tmp->left->height > tmp->right->height) ? tmp->left : tmp->right;
			_Node *tallChild = nullptr;
			if (current->left->height > current->right->height)
				tallChild = current->left;
			else if (current->right->height > current->left->height)
				tallChild = current->right;
			else
			{
				tallChild = (current == tmp->left) ? current->left : current->right;
			}
			if (current == tmp->left)
			{
				if (tallChild == tmp->left->left)
					right_rotate(tree, tmp);
				else if (tallChild == tmp->left->right)
				{
					left_rotate(tree, current);
					right_rotate(tree, tmp);
				}
			}
			else if (current == tmp->right)
			{
				if (tallChild == tmp->right->right)
					left_rotate(tree, tmp);
				else if (tallChild == tmp->right->left)
				{
					right_rotate(tree, current);
					left_rotate(tree, tmp);
				}
			}
		}
		del = del->parent;
	}
}

void deletion(avlTree *tree, int data)
{
	_Node *del = find(tree->root, data);
	std::cout << "Deleting... " << data << " : " << del << std::endl;
	if (!tree->root || !del)
		return ;
	if	(del->left == nullptr)
	{
		_Node *tmp = del;
		std::cout << "Case1: " << tmp->parent << " parent of " << del << " : " << del->right << std::endl;
		subtreeShift(tree, del, del->right);
		std::cout << "Case1: " << tmp->parent << " parent of " << tmp << " : " << del->right << std::endl;
		if (del->right != nullptr)
			deletionBalance(tree, del->right);
		delete del;
	}
	else if (del->right == nullptr)
	{
		std::cout << "Case2: " << del << " : " << del->left << std::endl;
		subtreeShift(tree, del, del->left);
		std::cout << "Case2: " << del << " : " << del->left << std::endl;
		if (del->left != nullptr)
			deletionBalance(tree, del->left);
		delete del;
	}
	else
	{
		_Node *tmp = treeMin(del->right);
		if (tmp->parent != del)
		{
			subtreeShift(tree, del, del->right);
			tmp->right = del->right;
			tmp->right->parent = tmp;
		}
		subtreeShift(tree, del, tmp);
		tmp->left = del->left;
		tmp->left->parent = tmp;
		if (tmp)
			deletionBalance(tree, tmp);
		delete del;

	}
	std::cout << "\tDeleting Done! " << data << std::endl;
}

int main()
{
	avlTree tree;
	tree.root = nullptr;
	int x[10];
	x[0] = 5;
	x[1] = 10;
	x[2] = 4;
	x[3] = 2;
	x[4] = 1;
	x[5] = 3;
	x[6] = 95;
	x[7] = 11;
	x[8] = 99;
	x[9] = 97;
	for (int i = 0; i < 6; i++)
		tree.root = insertNodeAVL(tree.root, x[i]);
	inorder(tree.root);
	// deletion(&tree, 50);
	// std::cout << "Deleleting of 50: Done!" << std::endl;
	// inorder(tree.root);
	// root = deletion(root, 97);
	// root = deleteNodeAVL(root, 30);
	// root = deleteNodeAVL(root, 20);
	// inorder(root);
	// for (int i = 0; i < 10; i++)
	// {
	// 	root = deleteNodeAVL(root, x[i]);
	// 	// _Node * f= find(root, x[i]);
	// 	inorder(root);
	// }
	// // root = deleteNodeAVL(root, x[3]);

	std::cout << "Root  : " << tree.root->data << " : " << tree.root <<" | " << tree.root->left << " | " << tree.root->right << std::endl;
	std::cout << "Balance Factor of Root = " << std::setw(2) << getBalanceFactor(tree.root) << std::endl;
	// _Node *srIter = find(root, x[3]);
	// if (srIter)
	// 	std::cout << "_____Search: " << srIter->data << " : " << srIter << " | " << srIter->left << " | " << srIter->right << std::endl;
}