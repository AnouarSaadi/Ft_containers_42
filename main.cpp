#include "srcs/Vector.hpp"
class Vector;
#include "srcs/Utils.hpp"
#include <iostream>
#include <vector>

int main()
{
	ft::Vector<int> v(4, 7);
	for (int i = 0; i < 4; ++i){
		std::cout << v[i] << std::endl;
	}
	ft::Vector<int>::iterator i = v.begin();
	v.at(3) = 0;
	std::cout << v.back() << std::endl;
	std::cout << v.capacity()  <<  std::endl;
	std::cout << v.max_size()  <<  std::endl;

	std::vector<int> v0(4, 7);
		for (; i != v.end(); ++i) {
		std::cout << *i << std::endl;
	}
	v0.push_back(56);
	v0.push_back(51);
	v0[5] = 0;
	std::cout << v0.at(5) << std::endl;

	std::cout << v0.capacity()  <<  std::endl;
	std::cout << v0.max_size()  <<  std::endl;

	ft::Vector<int> v1(v.begin(), v.end());
		for (int i = 0; i < 4; ++i){
		std::cout << v1[i] << std::endl;
	}
	std::cout << v1.max_size()  <<  std::endl;
	return 0;
}


/* 

	sie = 4
	capacity = 4

	reserve(s + 1);
	cap * 2 > n
		cap = cap * 2

 */