#include "srcs/Set.hpp"
#include <map>
#include <iostream>

#ifndef NS
# define NS ft
#endif


int main()
{
	NS::set<int> st;
	NS::map<std::string, int> _strs;
	int i = -1;
	while (++i < 200000)
	{
		_strs.insert(NS::make_pair("hello world!" + std::to_string(i), i));
	}
	st.insert(1);
	std::cout << (st.find(1) != st.end()) << std::endl;
	return 0;
}
