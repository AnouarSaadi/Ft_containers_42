#include "Tree.hpp"

int main()
{
	ft::tree<int> tree;
	tree.insert(10);
	tree.inorder();
	/* find node with data
	struct ft::node<int>	*n = tree.find(10);
	std::cout << n->data << std::endl;
	*/
	return (0);
}