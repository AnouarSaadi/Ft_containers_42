#include "Map.hpp"
#include <map>

#ifndef NS
# define NS ft
#endif

int main()
{
	NS::map<int, int> _map;
	_map.insert(NS::make_pair(1, 9));
	_map.insert(NS::make_pair(2, 10));
	_map.insert(NS::make_pair(2, 11));

	// NS::map<int, int>::iterator _it = _map.find(2);
	std::cout << _map[5] << std::endl;
	// _map.insert(ft::make_pair(1, 8));
	return (0);
}
