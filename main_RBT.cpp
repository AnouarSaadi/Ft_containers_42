#include "Tree.hpp"

int main()
{
	ft::tree<int> tree;
	std::cout << std::endl;
	std::cout << "Operation: Insertion" << std::endl;
	std::cout << std::endl;
	tree.insert(15);
	tree.insert(18);
	tree.insert(12);
	tree.insert(20);
	tree.insert(19);
	tree.insert(8);
	tree.inorder();
	std::cout << std::endl;
	std::cout << "Operation: Deletion" << std::endl;
	std::cout << std::endl;
	tree.remove(19);
	tree.inorder();
	return (0);

	/* find node with data
	struct ft::node<int>	*n = tree.find(10);
	std::cout << n->data << std::endl;
	*/

}
