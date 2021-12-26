#include "srcs/Map.hpp"
#include <map>

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
	/* Constructors */

	NS::map<int,int> first;

	first[1]=10;
	first[2]=30;
	first[3]=50;
	first[4]=70;
	NS::map<int,int> second (first.begin(),first.end());

	// NS::map<int,int> third (second);

	// NS::map<char,int,classcomp> fourth;                 // class as Compare

	// bool(*fn_pt)(char,char) = fncomp;
	// NS::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

	/* Capacity */
	NS::map<char,int> _mymap;

	_mymap['a']=10;
	_mymap['b']=20;
	_mymap['c']=30;

	while (!_mymap.empty())
	{
		std::cout << _mymap.begin()->first << " => " << _mymap.begin()->second << '\n';
		_mymap.erase(_mymap.begin());
	}

	// std::cout << "mymap.size() is " << _mymap.size() << '\n';

	/* Insert */
	NS::map<char,int> mymap;

	// first insert function version (single parameter):
	mymap.insert ( NS::pair<char,int>('a',100) );
	mymap.insert ( NS::pair<char,int>('z',200) );

	NS::pair<NS::map<char,int>::iterator,bool> ret;
	ret = mymap.insert ( NS::pair<char,int>('z',500) );
	if (ret.second==false) {
	std::cout << "element 'z' already existed";
	std::cout << " with a value of " << ret.first->second << '\n';
	}

	// second insert function version (with hint position):
	NS::map<char,int>::iterator it = mymap.begin();
	mymap.insert (it, NS::pair<char,int>('b',300));  // max efficiency inserting
	mymap.insert (it, NS::pair<char,int>('c',400));  // no max efficiency inserting

	// third insert function version (range insertion):
	NS::map<char,int> anothermap;
	anothermap.insert(mymap.begin(),mymap.find('c'));

	// showing contents:
	std::cout << "mymap contains:\n";
	for (it=mymap.begin(); it!=mymap.end(); ++it)
	std::cout << it->first << " => " << it->second << '\n';

	std::cout << "anothermap contains:\n";
	for (it=anothermap.begin(); it!=anothermap.end(); ++it)
	std::cout << it->first << " => " << it->second << '\n';

	/* erase */
	{
		NS::map<char,int> mymaperase;
		NS::map<char,int>::iterator it;

		// insert some values:
		mymaperase['a']=10;
		mymaperase['b']=20;
		mymaperase['c']=30;
		mymaperase['d']=40;
		mymaperase['e']=50;
		mymaperase['f']=60;

		it=mymaperase.find('b');
		mymaperase.erase (it);                   // erasing by iterator

		mymaperase.erase ('c');                  // erasing by key

		it=mymaperase.find ('e');
		mymaperase.erase ( it, mymaperase.end() );    // erasing by range
		// show content:
		for (it=mymaperase.begin(); it!=mymaperase.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	}

	return 0;
}
