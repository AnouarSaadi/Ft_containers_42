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
		for (int i = 0; (size_t)i < v.size(); i++){
			std::cout << v[i] << std::endl;
		}
		std::cout << v.size() << "   ----   " << v.capacity() << std::endl;
		v.push_back(10);
		v.push_back(11);
		v.push_back(12);
		v.push_back(13);
		v.push_back(14);
		v.pop_back();
		v.pop_back();
		v.pop_back();
		ft::Vector<int>::iterator itb = v.begin();
		std::cout << "position " << *itb << std::endl;
		ft::Vector<int>::iterator it = v.insert(v.begin(), 8);
		std::cout << "insert " << *it << std::endl;
		v.insert(v.begin() + 2, 8, 6);

		for (int i = 0; (size_t)i < v.size(); i++){
			std::cout << v[i] << std::endl;
		}
		std::cout << v.size() << "   ----   " << v.capacity() << std::endl;
	}
	std::cout << "********************** std::vector **********************" << std::endl;
	{
		std::vector<int> v(4, 7);
		for (int i = 0; (size_t)i < v.size(); i++){
			std::cout << v[i] << std::endl;
		}
		std::cout << v.size() << "   ----   " << v.capacity() << std::endl;
		v.push_back(10);
		v.push_back(11);
		v.push_back(12);
		v.push_back(13);
		v.push_back(14);
		v.pop_back();
		v.pop_back();
		v.pop_back();
		std::vector<int>::iterator itb = v.begin();
		std::cout << "position " << *itb << std::endl;
		std::vector<int>::iterator it = v.insert(v.begin(), 8);
		std::cout << "insert " << *it << std::endl;
		v.insert(v.begin() + 2, 8, 6);

		for (int i = 0; (size_t)i < v.size(); i++)
		{
			std::cout << v[i] << std::endl;
		}
		std::cout << v.size() << "   ----   " << v.capacity() << std::endl;
	}
	return 0;
}
