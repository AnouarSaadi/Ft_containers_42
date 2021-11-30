#include <cstdlib>
#include <iostream>


typedef struct node {
	int key;
	struct node *right;
	struct node *left;
} _Node;

_Node * newNode(int key)
{
	_Node * _new = (_Node *) malloc(sizeof(_Node));
	_new->key = key;
	_new->right = NULL;
	_new->left = NULL;
	return (_new);
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

_Node* searchIterative(_Node* root, int key, _Node* &parent)
{
	_Node *x = root;
	while (x && x->key != key)
	{
		parent = x;
		if (key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	if (x == NULL)
		std::cout << "_____here_____"  << std::endl;
	return (x);
}

// Insertion
void insertNode(_Node * &root, _Node *_new)
{
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

// Deletion
_Node *treeMax(_Node *x)
{
	while(x->right)
		x = x->right;
	return (x);
}

_Node *treeMin(_Node *x)
{
	while(x->left)
		x = x->left;
	return (x);
}

_Node * treeSuccessor(_Node * x)
{
	std::cout << "___TreeSuccessor___" << std::endl;
	if (x->right)
		return (treeMin(x->right));
	_Node *y = x;
	while(y && y->right)
		x = y;
	return (y);
}

void	treeReplace(_Node * &root, _Node *&u, _Node *&v)
{
	if (u == nullptr)
		root = v;
	else if (u == u->left)
		u->left = v;
	else
	{
		u->right = v;
	std::cout << " ____Replace___" << std::endl;
	}
	// if (v == nullptr)
	// 	v = u;
}

void deleteNode(_Node* &root, _Node *_node)
{ 
	_Node *parent = nullptr;
	_Node *curr = searchIterative(root, _node->key, parent);
	if (!curr)
		return ;
	if (!(curr->left) && !(curr->right))
	{
		if (curr != root)
		{
			if (parent->left == curr->left)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		else
			root = NULL;
	}
	else if (curr->right && curr->left)
	{
		_Node *successor = treeSuccessor(curr);
		std::cout << " _____Successor____ " << successor->key << std::endl;
		treeReplace(root, curr, successor);
		if (curr->key == successor->key)
			std::cout << " _____Successor == Curr____ " << successor->key << std::endl;
	}
	

	// if (_node->left == NULL)
	// 	treeReplace(&(*root), _node, _node->right);
	// else if (!(_node->right))
	// 	treeReplace(&(*root), _node, _node->left);
	// else
	// {
	// 	_Node * succ = treeSuccessor(_node);
	// 	std::cout << " _____Successor____ " << succ->key << std::endl;
	// 	if(succ != _node)
	// 	{
	// 		treeReplace(&(*root), succ, succ->right);
	// 		succ->right = _node->right;
	// 		succ->right = succ;
	// 	}
	// 	treeReplace(&(*root), _node, succ);
	// 	succ->left = _node->left;
	// 	succ->left = succ;
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
	for (size_t i = 0; i < 10; i++)
		insertNode(root, x[i]);
	deleteNode(root, x[2]);
	// _Node *successor = treeSuccessor(x[2]);
	// std::cout << " _____Successor____ " << successor->key << std::endl;
	_Node *par;
	_Node *srIter = searchIterative(root, x[2]->key, par);
	if (srIter)
		std::cout << " ____Search___ " << srIter->key << " | " << srIter->left << " | " << srIter->right << std::endl;
	else
		std::cout << " ____Node not found ____" << std::endl;
	// std::cout << " ____New______ " << x->key << " | " << x->left << " | " << x->right << std::endl;
	// insertNode(&root, x);
	// std::cout << " ____Root_____ " << root->key << " | " << root->left << " | " << root->right << std::endl;
	// _Node *x1 = newNode(5);
	// insertNode(&root, x1);
	// std::cout << " ____Root_____ " << root->key << " | " << root->left << " | " << root->right << std::endl;
	// _Node *x2 = newNode(20);
	// insertNode(&root, x2);
	// std::cout << " ____Root_____ " << root->key << " | " << root->left << " | " << root->right << std::endl;
	// _Node *x3 = newNode(15);
	// insertNode(&root, x3);
	// std::cout << " ____Root_____ " << root->key << " | " << root->left << " | " << root->right << std::endl;
	// _Node *sr = searchRecursicve(root, x1->key);
	// std::cout << " ____Search___ " << sr->key << " | " << sr->left << " | " << sr->right << std::endl;
	
}