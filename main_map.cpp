#include "srcs/Set.hpp"
#include <map>
#include <iostream>

#ifndef NS
# define NS ft
#endif

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

int main() // ! erase need to check
{
	// map tests
	std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< map tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"
			  << std::endl;
	NS::set<int> maptGolbal;
	print_namespace(maptGolbal);

	// begin()
	{
		std::cout << "\nbegin() & end() " << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> map1;
		map1.insert(5);
		map1.insert(10);
		map1.insert(4);
		map1.insert(2);
		NS::set<int>::iterator it = map1.begin();
		print_map(map1, "map1");
		std::cout << "map1.begin(): " << (*it).first << std::endl;
		std::cout << "=======================================" << std::endl;
	}
	// assign operator=()
	{
		std::cout << "\nassign operator=()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
		map1.insert(NS::make_pair(4, 4));
		print_map(map1, "map1");
		NS::set<int> map2;
		std::cout << "before assigning map1 to map2" << std::endl;
		print_map(map2, "map2");
		map2 = map1;
		std::cout << "after assigning map1 to map2" << std::endl;
		print_map(map2, "map2");
		std::cout << "=======================================" << std::endl;
	}


	// clear()
	{
		std::cout << "\nclear()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
		map1.insert(NS::make_pair(4, 4));
		print_map(map1, "map1");
		map1.clear();
		std::cout << "after clearing map1" << std::endl;
		print_map(map1, "map1");
		std::cout << "=======================================" << std::endl;
	}

	// count()
	{
		std::cout << "\ncount()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
		map1.insert(NS::make_pair(4, 4));
		print_map(map1, "map1");
		std::cout << "map1.count(5): " << map1.count(5) << std::endl;
		std::cout << "map1.count(6): " << map1.count(6) << std::endl;
		std::cout << "=======================================" << std::endl;
	}

	// empty() and size()
	{
		std::cout << "\nempty()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
		map1.insert(NS::make_pair(4, 4));
		print_map(map1, "map1");
		std::cout << "map1.empty(): " << map1.empty() << std::endl;
		map1.clear();
		std::cout << "after clearing map1" << std::endl;
		print_map(map1, "map1");
		std::cout << "map1.empty(): " << map1.empty() << std::endl;
		std::cout << "=======================================" << std::endl;
	}

	// find()
	{
		std::cout << "\nfind()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
		print_map(map1, "map1");
		if (map1.find(5) != map1.end())
			std::cout << "5 has been found and its second is = " << map1.find(5)->second << std::endl;
		else
			std::cout << "5 has not been found" << std::endl;
		if (map1.find(6) != map1.end())
			std::cout << "6 has been found and its second is = " << map1.find(6)->second << std::endl;
		else
			std::cout << "6 has not been found" << std::endl;
		std::cout << "=======================================" << std::endl;
	}

	// insert()
	{
		std::cout << "\ninsert()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
		print_map(map1, "map1");
		NS::set<int>::iterator it = map1.insert(NS::make_pair(4, 4)).first;
		print_map(map1, "map1");
		std::cout << "inserted 4, 4 at " << (*it).first << std::endl;
		NS::pair<int> arr[] = {NS::make_pair(0, 20), NS::make_pair(2, 30),
									NS::make_pair(3, 40), NS::make_pair(4, 50)};
		NS::set<int> map2;
		map2.insert(arr, arr + 4);
		print_map(map2, "map2");
		std::cout << "=======================================" << std::endl;
	}

	// map constructors
	{
		std::cout << "\nmap constructors" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1[10] = 3;
		map1[4] = 4;
		print_map(map1, "map1");
		NS::set<int> map2(map1);
		print_map(map2, "map2");
		NS::set<int> map3(map2.begin(), map2.end());
		print_map(map3, "map3");
		std::cout << "=======================================" << std::endl;
	}

	// erase()
	{
		std::cout << "\nerase()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> map1;
		map1.insert(NS::make_pair(0, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
		map1.insert(NS::make_pair(4, 4));
		map1.insert(NS::make_pair(3, 300));
		map1.insert(NS::make_pair(3, 300));
		map1.insert(NS::make_pair(1, 110));
		map1.insert(NS::make_pair(0, 10));
		print_map(map1, "map1");
		std::cout << "map1.erase(0): " << map1.erase(0) << std::endl;
		NS::set<int>::iterator it = map1.begin();
		std::advance(it, 2);
		map1.erase(map1.begin(), it);
		print_map(map1, "map1");
		map1.erase(map1.begin());
		print_map(map1, "map1");

		std::cout << "=======================================" << std::endl;
	}

	// max_size()
	{
		std::cout << "\nmax_size()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> map1;
		std::cout << "map1.max_size(): " << map1.max_size() << std::endl;
		std::cout << "=======================================" << std::endl;
	}

	// swap()
	{
		std::cout << "\nswap()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
		map1.insert(NS::make_pair(4, 4));
		print_map(map1, "map1");
		NS::set<int> map2;
		map2.insert(NS::make_pair(0, 1));
		map2.insert(NS::make_pair(2, 2));
		map2.insert(NS::make_pair(10, 3));
		map2.insert(NS::make_pair(4, 4));
		print_map(map2, "map2");
		map1.swap(map2);
		print_map(map1, "map1");
		print_map(map2, "map2");
		std::cout << "=======================================" << std::endl;
	}

	// lower_bound()
	{
		std::cout << "\nlower_bound()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
		map1.insert(NS::make_pair(4, 4));
		print_map(map1, "map1");
		NS::set<int>::iterator it = map1.lower_bound(3);
		std::cout << "map1.lower_bound(3): " << (*it).first << std::endl;
		it = map1.lower_bound(5);
		std::cout << "map1.lower_bound(5): " << (*it).first << std::endl;
		it = map1.lower_bound(6);
		std::cout << "map1.lower_bound(6): " << (*it).first << std::endl;
		std::cout << "=======================================" << std::endl;
	}

	// upper_bound()
	{
		std::cout << "\nupper_bound()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
		map1.insert(NS::make_pair(4, 4));
		print_map(map1, "map1");
		NS::set<int>::iterator it = map1.upper_bound(3);
		std::cout << "map1.upper_bound(3): " << (*it).first << std::endl;
		it = map1.upper_bound(5);
		std::cout << "map1.upper_bound(5): " << (*it).first << std::endl;
		it = map1.upper_bound(6);
		std::cout << "map1.upper_bound(6): " << (*it).first << std::endl;
		std::cout << "=======================================" << std::endl;
	}

	// equal_range()
	{
		std::cout << "\nequal_range()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
		map1.insert(NS::make_pair(4, 4));
		print_map(map1, "map1");
		NS::pair<NS::set<int>::iterator, NS::set<int>::iterator> range = map1.equal_range(3);
		std::cout << "map1.equal_range(3): " << (*range.first).first << " " << (*range.second).first << std::endl;
		range = map1.equal_range(5);
		std::cout << "map1.equal_range(5): " << (*range.first).first << " " << (*range.second).first << std::endl;
		range = map1.equal_range(6);
		std::cout << "map1.equal_range(6): " << (*range.first).first << " " << (*range.second).first << std::endl;
		std::cout << "=======================================" << std::endl;
	}

	// get_allocator()
	{
		std::cout << "\nget_allocator()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> map1;
		print_map(map1, "map1");
		NS::set<int>::allocator_type alloc = map1.get_allocator();
		NS::pair<const int, int> *ptr = alloc.allocate(1);
		alloc.deallocate(ptr, 1);
		std::cout << "alloc max size: " << alloc.max_size() << std::endl;

		std::cout << "=======================================" << std::endl;
	}

	// const iterators
	{
		std::cout << "\nconst iterators" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
		map1.insert(NS::make_pair(4, 4));
		print_map(map1, "map1");
		NS::set<int>::const_iterator it = map1.begin();
		std::cout << "map1.begin(): " << (*it).first << std::endl;
		it = map1.end();
		--it;
		std::cout << "map1.end(): " << (*it).first << std::endl;
		std::cout << "=======================================" << std::endl;
	}

	// reverse iterators
	{
		std::cout << "\nreverse iterators" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
		map1.insert(NS::make_pair(4, 4));
		print_map(map1, "map1");
		NS::set<int>::reverse_iterator it = map1.rbegin();
		// print all elements in reverse order
		for (; it != map1.rend(); ++it)
		{
			std::cout << "[" << (*it).first << "] = " << (*it).second << std::endl;
		}

		std::cout << "=======================================" << std::endl;
	}

	std::cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< end of map tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"
			  << std::endl;
	// end of map tests

	return 0;
}
