#include "srcs/Vector.hpp"
class Vector;
#include <iostream>
#include <vector>
#include <unistd.h>


#ifndef NS
# define NS ft
#endif
int main()
{
		/* ********************* vector ********************* */
	NS::vector<int> v(4, 7);
	std::cout << v.size() << "   ----   " << v.capacity() << std::endl;
	// TODO: Solving the iterator problem
	// std::cout << "___begin__ " << *(v.begin()) << std::endl;
	// v.push_back(10);
	// v.push_back(11);
	// v.push_back(12);
	// v.push_back(13);
	// v.push_back(14);
	// v.pop_back();
	// v.pop_back();
	// v.pop_back();
	// NS::vector<int> l;
	// l = v;
	// std::cout << " ___compare__ " << (l == v) << std::endl;
	NS::vector<int>::iterator _begin_(v.begin());
	std::cout << "____begin__ " << *_begin_ << std::endl;
	// NS::vector<int>::iterator _end_ = v.end();
	// size_t in = 0;
	// for (; _begin_ != _end_; _begin_++){
	// 	std::cout << "\t\tv["<< in++ <<"] = " << *_begin_ << std::endl;
	// }
	// NS::vector<int>::iterator itb = v.begin();
	// std::cout << "position " << *itb << std::endl;
	// NS::vector<int>::iterator it = v.insert(v.begin() + 2, 8);
	// std::cout << "insert " << *it << std::endl;
	// v.insert(v.begin() + 2, 8, 6);
	// for (size_t i = 0; i < v.size(); i++){
	// 	std::cout << "\t\tv["<< i <<"] = " << v[i] << " " << *(v.begin()) << "\t" << v.size() << std::endl;
	// }
	// v.insert(v.begin() + 2,v.begin() + 13, v.begin() + 15);
	// itb = v.end() - 3;
	// itb = v.erase(itb);
	// for (size_t i = 0; i < v.size(); i++){
	// 	std::cout << "\t\tv["<< i <<"] = " << v[i] << " " << *(v.begin()) << "\t" << v.size() << std::endl;
	// }
	// itb = v.erase(v.begin() + 4, v.begin() + 12);
	// std::cout << "new postion  "<< *itb << std::endl;
	// for (size_t i = 0; i < v.size(); i++){
	// 	std::cout << "\t\tv["<< i <<"] = " << v[i] << std::endl;
	// }
	// std::cout << v.size() << "   ----   " << v.capacity() << std::endl;
	// NS::vector<int> bar(5, 800);
	// v.swap(bar);
	// for (size_t i = 0; i < v.size(); i++) {
	// 	std::cout << "\t\tv["<< i <<"] = " << v[i] << std::endl;
	// }
	// for (size_t i = 0; i < bar.size(); i++) {
	// 	std::cout << "\t\tbar["<< i <<"] = " << bar[i] << std::endl;
	// }
	// NS::vector<int> va;
	// va.assign(bar.begin(), bar.end());
	// // va.assign(4, 150);
	// for (size_t i = 0; i < va.size(); i++) {
	// 	std::cout << "\t\tva["<< i <<"] = " << va[i] << std::endl;
	// }
	// std::cout << v.size() << "|" << va.size() << "   ----   " << v.capacity() << "|" << va.capacity() << std::endl;
	// NS::vector<int> vcopy;
	// // // vcopy = v;
	// vcopy.assign(bar.begin(), bar.end());
	// for (size_t i = 0; i < vcopy.size(); i++) {
	// 	std::cout << "\t\tvcopy["<< i <<"] = " << vcopy[i] << std::endl;
	// }
	// std::cout << (v > vcopy) << std::endl;
	// NS::vector<std::string> str;
	// for (int i = 0; i < 10; i++)
	// {
	// 	str.push_back("str" + std::to_string(i));
	// 	std::cout << str[i] << std::endl;
	// }
	// bar.resize(40);
	// bar.resize(4);
	// for (size_t i = 0; i < bar.size(); i++) {
	// 	std::cout << "\t\tbar["<< i <<"] = " << bar[i] << "\t" << bar.size() <<'|'<<bar.capacity()<< std::endl;
	// }
	// NS::vector<int>::reverse_iterator rev_it = vcopy.rbegin() + 3;
	// // std::cout << "Debugging... rev it   " << &(*rev_it) << " " << sizeof(rev_it) << std::endl; // ! check the size
	// std::cout << "rev :";
	// for (;rev_it != vcopy.rend(); ++rev_it)
    // 	std::cout << ' ' << *rev_it;
  	// std::cout << '\n';
	// std::cout << "vec :";
  	// for (NS::vector<int>::iterator it = vcopy.begin(); it != vcopy.end(); ++it)
    // 	std::cout << ' ' << *it;
  	// std::cout << '\n';
	return 0;
}
