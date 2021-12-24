#include "Tree.hpp"
#include <map>

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
	ft::tree<int>::iterator it = tree.begin();
	it++;
	std::cout << *it << std::endl;
	// for (; it != tree.end(); it++)
	// {
	// 	std::cout << *it << std::endl;
	// }
	(void)it;
	tree.preorder();
	std::cout << std::endl;
	std::cout << "Operation: Deletion" << std::endl;
	std::cout << std::endl;
	tree.remove(15);
	tree.remove(19);
	tree.remove(18);
	tree.remove(8);
	tree.remove(20);
	tree.remove(12);
	tree.preorder();
	return (0);

	/* find node with data
	struct ft::node<int>	*n = tree.find(10);
	std::cout << n->data << std::endl;
	*/
}
