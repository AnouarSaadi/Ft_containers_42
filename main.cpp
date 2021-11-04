#include "srcs/Vector.hpp"
class Vector;
#include "srcs/Utils.hpp"
#include <iostream>
#include <vector>

int main()
{
	std::cout << "********************** My vector **********************" << std::endl;
	{
		ft::Vector<int> v(4, 7);
		std::cout << v.size() << "   ----   " << v.capacity() << std::endl;
		v.push_back(10);
		v.push_back(11);
		v.push_back(12);
		v.push_back(13);
		v.push_back(14);
		v.pop_back();
		v.pop_back();
		v.pop_back();
		for (size_t i = 0; i < v.size(); i++){
			std::cout << v[i] << std::endl;
		}
		ft::Vector<int>::iterator itb = v.begin();
		std::cout << "position " << *itb << std::endl;
		ft::Vector<int>::iterator it = v.insert(v.begin() + 2, 8);
		std::cout << "insert " << *it << std::endl;
		v.insert(v.begin() + 2, 8, 6);
		v.insert(v.begin() + 2,v.begin() + 13, v.begin() + 15);
		itb = v.begin() + 3;
		itb = v.erase(itb);
		for (size_t i = 0; i < v.size(); i++){
			std::cout << v[i] << std::endl;
				}
		itb = v.erase(v.begin() + 4, v.begin() + 12);
		std::cout << "new postion  "<< *itb << std::endl;
		for (size_t i = 0; i < v.size(); i++){
			std::cout << v[i] << std::endl;
		}
		std::cout << v.size() << "   ----   " << v.capacity() << std::endl;
	}
	std::cout << "********************** std::vector **********************" << std::endl;
	{
		std::vector<int> v(4, 7);
		std::cout << v.size() << "   ----   " << v.capacity() << std::endl;
		v.push_back(10);
		v.push_back(11);
		v.push_back(12);
		v.push_back(13);
		v.push_back(14);
		v.pop_back();
		v.pop_back();
		v.pop_back();
		for (size_t i = 0; i < v.size(); i++){
			std::cout << v[i] << std::endl;
		}
		std::vector<int>::iterator itb = v.begin();
		std::cout << "position " << *itb << std::endl;
		std::vector<int>::iterator it = v.insert(v.begin()+ 2, 8);
		std::cout << "insert " << *it << std::endl;
		v.insert(v.begin() + 2, 8, 6);
		v.insert(v.begin() + 2,v.begin() + 13, v.begin() + 15);
		itb = v.begin() + 3;
		itb = v.erase(itb);
				for (size_t i = 0; i < v.size(); i++){
			std::cout << v[i] << std::endl;
		}
		itb = v.erase(v.begin() + 4, v.begin() + 12);
		std::cout << "new postion  "<< *itb << std::endl;
		for (size_t i = 0; i < v.size(); i++) {
			std::cout << v[i] << std::endl;
		}
		std::cout << v.size() << "   ----   " << v.capacity() << std::endl;
	}
	return 0;
}
