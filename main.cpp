#include "srcs/Vector.hpp"
#include <iostream>
#include <vector>

int main()
{
	// std::cout << "jbviudb" << std::endl;
	ft::Vector<int> v(4, 7);
	for (int i = 0; i < 4; ++i) {
		std::cout << v[i] << std::endl;
	}

	// std::vector<int> v(4, 7, std::allocator<int>());
	// for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
	// 	std::cout << *it << std::endl;
	
	return 0;
}