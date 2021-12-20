#include <cstdlib>
#include <iostream>

typedef struct node {
	int			data;
	struct node	*right;
	struct node	*left;
	struct node	*parent;
	size_t		height;
} _Node;

_Node * newNode(int data)
{
	_Node * _new = new _Node();
	_new->data = data;
	_new->right = NULL;
	_new->left = NULL;
	_new->parent = NULL;
	_new->height = 1;
	return (_new);
}

/* Height function use for determining the height of the given node */
size_t nodeHeight(_Node *x)
{
	if (x == NULL)
		return (0);
	return (x->height);
}

// Searching
_Node* searchRecursicve(_Node* &root, int data)
{
	if (root->data == data || !root)
		return root;
	if (data < root->data)
		return (searchRecursicve(root->left, data));
	else
		return (searchRecursicve(root->right, data));
}

_Node* find(_Node* root, int data)
{
	_Node *current = root;
    while (current != nullptr) {
        if (current->data == data) {
            break;
        }
        current = current->data < data ? current->right : current->left;
    }
    return current;
}

/* Insertion of the given node _new into the BST tree roo t*/
void insertNode(_Node * &root, _Node *&_new)
{
	if (find(root, _new->data))
		return ;
	_Node *y = NULL;
	_Node *x = root;
	while (x != NULL)
	{
		y = x;
		if (_new->data < x->data)
			x = x->left;
		else
			x = x->right;
	}
	if (!y)
		root = _new;
	else if (_new->data < y->data)
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
	_Node *current = x;
	while(current->left)
		current = current->left;
	return (current);
}

/* The findParent function used to find the parent of the given node */
_Node*  findParent(_Node * &root, _Node * &_node)
{
	_Node * parent = NULL;
	if (!find(root, _node->data) || root == _node)
		return (root);
	parent = root;
	if (parent->left == _node || parent->right == _node)
		return (parent);
	if (parent->data > _node->data)
		parent = findParent(parent->left, _node);
	if (parent->data < _node->data)
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
void replaceNodes(_Node **root, _Node *u, _Node *v)
{
	// _Node *parent1 = findParent(root, u);
	if (u->parent == nullptr)
		*root = v;
	else if (u == u->parent->left)
	{
		u->parent->left = v;
	}
	else
	{
		u->parent->right = v;
	}
	if (v != NULL)
		v->parent = u->parent;
}

void deleteNode(_Node* &root, _Node *&_node)
{
	if (!find(root, _node->data) || (!root))
		return ;
	if (!(_node->left))
		replaceNodes(&root, _node, _node->right);
	else if (!(_node->right))
		replaceNodes(&root, _node, _node->left);
	else
	{
		_Node * successor = treeSuccessor(root, _node);
		_Node * succPar = findParent(root, successor);
		if (succPar != _node)
		{
			replaceNodes(&root, successor, successor->right);
			successor->right = _node->right;
			_Node *succRP = findParent(root, successor->right);
			succRP = successor;
		}
		replaceNodes(&root, _node, successor);
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
// 	_Node *srIter = find(root, x[0]->data);
// 	if (srIter)
// 		std::cout << " ____Search___ " << srIter->data << " | " << srIter->left << " | " << srIter->right << std::endl;
// 	else
// 		std::cout << " ____Node not found ____" << std::endl;
// }