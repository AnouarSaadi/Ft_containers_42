#include "srcs/Vector.hpp"
class Vector;
#include "srcs/Utils.hpp"
#include <iostream>
#include <vector>
#include <unistd.h>

int main()
{
	std::cout << "********************** My vector **********************" << std::endl;
	{
		ft::vector<int> v(4, 7);
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
			std::cout << "\t\tv["<< i <<"] = " << v[i] << std::endl;
		}
		ft::vector<int>::iterator itb = v.begin();
		std::cout << "position " << *itb << std::endl;
		ft::vector<int>::iterator it = v.insert(v.begin() + 2, 8);
		std::cout << "insert " << *it << std::endl;
		// v.insert(v.begin() + 2, 8, 6);
		// v.insert(v.begin() + 2,v.begin() + 13, v.begin() + 15);
		// itb = v.begin() + 3;
		// itb = v.erase(itb);
		for (size_t i = 0; i < v.size(); i++){
			std::cout << "\t\tv["<< i <<"] = " << v[i] << std::endl;
		}
	}
	// 	// itb = v.erase(v.begin() + 4, v.begin() + 12);
	// 	// std::cout << "new postion  "<< *itb << std::endl;
	// 	// for (size_t i = 0; i < v.size(); i++){
	// 	// 	std::cout << "\t\tv["<< i <<"] = " << v[i] << std::endl;
	// 	// }
	// 	// std::cout << v.size() << "   ----   " << v.capacity() << std::endl;
	// 	// ft::vector<int> bar (5,200);
	// 	// v.swap(bar);
	// 	// for (size_t i = 0; i < v.size(); i++) {
	// 	// 	std::cout << "\t\tv["<< i <<"] = " << v[i] << std::endl;
	// 	// }
	// 	// for (size_t i = 0; i < bar.size(); i++) {
	// 	// 	std::cout << "\t\tbar["<< i <<"] = " << bar[i] << std::endl;
	// 	// }
	// 	// ft::vector<int> va;
	// 	// va.assign(bar.begin(), bar.end());
	// 	// // va.assign(4, 150);
	// 	// for (size_t i = 0; i < va.size(); i++) {
	// 	// 	std::cout << "\t\tva["<< i <<"] = " << va[i] << std::endl;
	// 	// }
	// 	// std::cout << v.size() << "|" << va.size() << "   ----   " << v.capacity() << "|" << va.capacity() << std::endl;
	// 	// ft::vector<int> vcopy;
	// 	// // vcopy = v;
	// 	// vcopy.assign(bar.begin(), bar.end());
	// 	// std::cout << (v > vcopy) << std::endl;
	// 	// ft::vector<std::string> str;
	// 	// // solve the segmentation fault problem
	// 	// for (int i = 0; i < 10; i++)
	// 	// {
	// 	// 	str.push_back("str" + std::to_string(i));
	// 	// 	// std::cout << str[i] << std::endl;
	// 	// }
	// 	// ft::vector<std::string>::reverse_iterator rev_it = str.rbegin();
	// 	// ft::vector<std::string>::iterator end = str.end();
	// 	// std::cout << "end == " << *end << " rbegin == " << *rev_it << std::endl;
	// }
	// std::cout << "********************** std::vector **********************" << std::endl;
	// {
	// 	std::vector<int> v(4, 7);
	// 	std::cout << v.size() << "   ----   " << v.capacity() << std::endl;
	// 	v.push_back(10);
	// 	v.push_back(11);
	// 	v.push_back(12);
	// 	v.push_back(13);
	// 	v.push_back(14);
	// 	v.pop_back();
	// 	v.pop_back();
	// 	v.pop_back();
	// 	for (size_t i = 0; i < v.size(); i++){
	// 		std::cout << "\t\tv["<< i <<"] = " << v[i] << std::endl;
	// 	}
	// 	std::vector<int>::iterator itb = v.begin();
	// 	std::cout << "position " << *itb << std::endl;
	// 	std::vector<int>::iterator it = v.insert(v.begin()+ 2, 8);
	// 	std::cout << "insert " << *it << std::endl;
	// 	v.insert(v.begin() + 2, 8, 6);
	// 	v.insert(v.begin() + 2,v.begin() + 13, v.begin() + 15);
	// 	itb = v.begin() + 3;
	// 	itb = v.erase(itb);
	// 			for (size_t i = 0; i < v.size(); i++){
	// 		std::cout << "\t\tv["<< i <<"] = " << v[i] << std::endl;
	// 	}
	// 	itb = v.erase(v.begin() + 4, v.begin() + 12);
	// 	std::cout << "new postion  "<< *itb << std::endl;
	// 	for (size_t i = 0; i < v.size(); i++){
	// 		std::cout << "\t\tv["<< i <<"] = " << v[i] << std::endl;
	// 	}
	// 	std::cout << v.size() << "   ----   " << v.capacity() << std::endl;
	// 	std::vector<int> bar (5,200);
	// 	v.swap(bar);
	// 	for (size_t i = 0; i < v.size(); i++) {
	// 		std::cout << "\t\tv["<< i <<"] = " << v[i] << std::endl;
	// 	}
	// 	for (size_t i = 0; i < bar.size(); i++) {
	// 		std::cout << "\t\tbar["<< i <<"] = " << bar[i] << std::endl;
	// 	}
	// 	// assign
	// 	std::vector<int> va;
	// 	va.assign(bar.begin(), bar.end());
	// 	// va.assign(4, 150);
	// 	for (size_t i = 0; i < va.size(); i++) {
	// 		std::cout << "\t\tva["<< i <<"] = " << va[i] << std::endl;
	// 	}
	// 	std::cout << v.size() << "|" << va.size() << "   ----   " << v.capacity() << "|" << va.capacity() << std::endl;
	// 	std::vector<int> vcopy;
	// 	// vcopy = v;
	// 	vcopy.assign(bar.begin(), bar.end());
	// 	std::cout << (v > vcopy) << std::endl;
	// 	std::vector<std::string> str;
	// 	for (int i = 0; i < 10; i++)
	// 	{
	// 		str.push_back("str" + std::to_string(i));
	// 		std::cout << str[i] << std::endl;
	// 	}
	// 	std::vector<std::string>::reverse_iterator rev_it = str.rbegin();
	// 	std::vector<std::string>::iterator end = str.end();
	// 	std::cout << "end == " << *end << " rbegin == " << *rev_it << std::endl;
	// }



	return 0;
}
