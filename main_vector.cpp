#include <iostream>
#include <vector>

int main() {
	std::vector<int> v;
	v.push_back(1);

	for (int  i = 0; i < 5; i++)
		std::cout << v.at(i);
}