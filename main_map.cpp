#include "srcs/Map.hpp"
#include <map>
#include <iostream>
#include <string>
#include "srcs/Utility.hpp"
#include <iterator>

#ifndef NS
# define NS ft
#endif

// testing timeout
int main()
{
	NS::map<std::string, int> _strs;
	int i = -1;
	while (++i < 200000)
	{
		_strs.insert(NS::make_pair("hello world!" + std::to_string(i), i));
	}
}
