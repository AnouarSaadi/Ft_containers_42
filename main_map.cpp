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
		NS::set<int> set1;
		set1.insert(5);
		set1.insert(10);
		set1.insert(4);
		set1.insert(2);
		NS::set<int>::iterator it = set1.begin();
		print_map(set1, "set1");
		std::cout << "set1.begin(): " << (*it) << std::endl;
		std::cout << "=======================================" << std::endl;
	}
	// assign operator=()
	{
		std::cout << "\nassign operator=()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> set1;
		set1.insert(5);
		set1.insert(2);
		set1.insert(10);
		set1.insert(4);
		print_map(set1, "set1");
		NS::set<int> set2;
		std::cout << "before assigning set1 to set2" << std::endl;
		print_map(set2, "set2");
		set2 = set1;
		std::cout << "after assigning set1 to set2" << std::endl;
		print_map(set2, "set2");
		std::cout << "=======================================" << std::endl;
	}


	// clear()
	{
		std::cout << "\nclear()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> set1;
		set1.insert(5);
		set1.insert(2);
		set1.insert(10);
		set1.insert(4);
		print_map(set1, "set1");
		set1.clear();
		std::cout << "after clearing set1" << std::endl;
		print_map(set1, "set1");
		std::cout << "=======================================" << std::endl;
	}

	// count()
	{
		std::cout << "\ncount()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> set1;
		set1.insert(5);
		set1.insert(2);
		set1.insert(10);
		set1.insert(4);
		print_map(set1, "set1");
		std::cout << "set1.count(5): " << set1.count(5) << std::endl;
		std::cout << "set1.count(6): " << set1.count(6) << std::endl;
		std::cout << "=======================================" << std::endl;
	}

	// empty() and size()
	{
		std::cout << "\nempty()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> set1;
		set1.insert(5);
		set1.insert(2);
		set1.insert(10);
		set1.insert(4);
		print_map(set1, "set1");
		std::cout << "set1.empty(): " << set1.empty() << std::endl;
		set1.clear();
		std::cout << "after clearing set1" << std::endl;
		print_map(set1, "set1");
		std::cout << "set1.empty(): " << set1.empty() << std::endl;
		std::cout << "=======================================" << std::endl;
	}

	// find()
	{
		std::cout << "\nfind()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> set1;
		set1.insert(5);
		set1.insert(2);
		set1.insert(10);
		print_map(set1, "set1");
		if (set1.find(5) != set1.end())
			std::cout << "5 has been found and its second is = " << set1.find(5)->second << std::endl;
		else
			std::cout << "5 has not been found" << std::endl;
		if (set1.find(6) != set1.end())
			std::cout << "6 has been found and its second is = " << set1.find(6)->second << std::endl;
		else
			std::cout << "6 has not been found" << std::endl;
		std::cout << "=======================================" << std::endl;
	}

	// insert()
	{
		std::cout << "\ninsert()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> set1;
		set1.insert(5);
		set1.insert(2);
		set1.insert(10);
		print_map(set1, "set1");
		NS::set<int>::iterator it = set1.insert(4).first;
		print_map(set1, "set1");
		std::cout << "inserted 4, 4 at " << (*it) << std::endl;
		std::cout << "=======================================" << std::endl;
	}

	// map constructors
	{
		std::cout << "\nmap constructors" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> set1;
		set1.insert(5);
		set1.insert(2);
		print_map(set1, "set1");
		NS::set<int> set2(set1);
		print_map(set2, "set2");
		NS::set<int> map3(set2.begin(), set2.end());
		print_map(map3, "map3");
		std::cout << "=======================================" << std::endl;
	}

	// erase()
	{
		std::cout << "\nerase()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> set1;
		set1.insert(0);
		set1.insert(2);
		set1.insert(10);
		set1.insert(4);
		set1.insert(3);
		set1.insert(3);
		set1.insert(1);
		set1.insert(NS::make_pair(0, 10));
		print_map(set1, "set1");
		std::cout << "set1.erase(0): " << set1.erase(0) << std::endl;
		NS::set<int>::iterator it = set1.begin();
		std::advance(it, 2);
		set1.erase(set1.begin(), it);
		print_map(set1, "set1");
		set1.erase(set1.begin());
		print_map(set1, "set1");

		std::cout << "=======================================" << std::endl;
	}

	// max_size()
	{
		std::cout << "\nmax_size()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> set1;
		std::cout << "set1.max_size(): " << set1.max_size() << std::endl;
		std::cout << "=======================================" << std::endl;
	}

	// swap()
	{
		std::cout << "\nswap()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> set1;
		set1.insert(5);
		set1.insert(2);
		set1.insert(10);
		set1.insert(4);
		print_map(set1, "set1");
		NS::set<int> set2;
		set2.insert(0);
		set2.insert(NS::make_pair(2, 2));
		set2.insert(10);
		set2.insert(4);
		print_map(set2, "set2");
		set1.swap(set2);
		print_map(set1, "set1");
		print_map(set2, "set2");
		std::cout << "=======================================" << std::endl;
	}

	// lower_bound()
	{
		std::cout << "\nlower_bound()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> set1;
		set1.insert(5);
		set1.insert(2);
		set1.insert(10);
		set1.insert(4);
		print_map(set1, "set1");
		NS::set<int>::iterator it = set1.lower_bound(3);
		std::cout << "set1.lower_bound(3): " << (*it) << std::endl;
		it = set1.lower_bound(5);
		std::cout << "set1.lower_bound(5): " << (*it) << std::endl;
		it = set1.lower_bound(6);
		std::cout << "set1.lower_bound(6): " << (*it) << std::endl;
		std::cout << "=======================================" << std::endl;
	}

	// upper_bound()
	{
		std::cout << "\nupper_bound()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> set1;
		set1.insert(5);
		set1.insert(2);
		set1.insert(10);
		set1.insert(4);
		print_map(set1, "set1");
		NS::set<int>::iterator it = set1.upper_bound(3);
		std::cout << "set1.upper_bound(3): " << (*it) << std::endl;
		it = set1.upper_bound(5);
		std::cout << "set1.upper_bound(5): " << (*it) << std::endl;
		it = set1.upper_bound(6);
		std::cout << "set1.upper_bound(6): " << (*it) << std::endl;
		std::cout << "=======================================" << std::endl;
	}

	// equal_range()
	{
		std::cout << "\nequal_range()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> set1;
		set1.insert(5);
		set1.insert(2);
		set1.insert(10);
		set1.insert(4);
		print_map(set1, "set1");
		NS::pair<NS::set<int>::iterator, NS::set<int>::iterator> range = set1.equal_range(3);
		std::cout << "set1.equal_range(3): " << (*range.first).first << " " << (*range.second).first << std::endl;
		range = set1.equal_range(5);
		std::cout << "set1.equal_range(5): " << (*range.first).first << " " << (*range.second).first << std::endl;
		range = set1.equal_range(6);
		std::cout << "set1.equal_range(6): " << (*range.first).first << " " << (*range.second).first << std::endl;
		std::cout << "=======================================" << std::endl;
	}

	// get_allocator()
	{
		std::cout << "\nget_allocator()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> set1;
		print_map(set1, "set1");
		NS::set<int>::allocator_type alloc = set1.get_allocator();
		NS::pair<const int, int> *ptr = alloc.allocate(1);
		alloc.deallocate(ptr, 1);
		std::cout << "alloc max size: " << alloc.max_size() << std::endl;

		std::cout << "=======================================" << std::endl;
	}

	// const iterators
	{
		std::cout << "\nconst iterators" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> set1;
		set1.insert(5);
		set1.insert(2);
		set1.insert(10);
		set1.insert(4);
		print_map(set1, "set1");
		NS::set<int>::const_iterator it = set1.begin();
		std::cout << "set1.begin(): " << (*it) << std::endl;
		it = set1.end();
		--it;
		std::cout << "set1.end(): " << (*it) << std::endl;
		std::cout << "=======================================" << std::endl;
	}

	// reverse iterators
	{
		std::cout << "\nreverse iterators" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::set<int> set1;
		set1.insert(5);
		set1.insert(2);
		set1.insert(10);
		set1.insert(4);
		print_map(set1, "set1");
		NS::set<int>::reverse_iterator it = set1.rbegin();
		// print all elements in reverse order
		for (; it != set1.rend(); ++it)
		{
			std::cout << "[" << (*it) << "] = " << (*it) << std::endl;
		}

		std::cout << "=======================================" << std::endl;
	}

	std::cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< end of map tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"
			  << std::endl;
	// end of map tests

	return 0;
}
