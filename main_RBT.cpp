#include "Tree.hpp"

int main()
{
	ft::tree<int> tree;
	tree.insert(15);
	tree.insert(18);
	tree.insert(12);
	tree.insert(20);
	tree.insert(19);
	// tree.insert(8);
	tree.inorder();
	return (0);

	/* find node with data
	struct ft::node<int>	*n = tree.find(10);
	std::cout << n->data << std::endl;
	*/
}