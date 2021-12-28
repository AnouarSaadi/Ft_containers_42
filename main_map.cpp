#include "srcs/Map.hpp"
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
	/* Constructors */
	// #ifdef CONS
		NS::map<char,int> first;

		first['a']=10;
		first['b']=30;
		first['c']=50;
		first['d']=70;

		NS::map<char,int> second (first.begin(),first.end());

		NS::map<char,int> third (second);

		NS::map<char,int,classcomp> fourth;                 // class as Compare

		bool(*fn_pt)(char,char) = fncomp;
		NS::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare
	// #endif
	/* Capacity */
	NS::map<char,int> _mymap;

	_mymap['a']= 10;
	_mymap['b']= 20;
	_mymap['c']= 30;
	_mymap['c']= 30;

	while (!_mymap.empty())
	{
		std::cout << _mymap.begin()->first << " => " << _mymap.begin()->second << " " << _mymap.size() << '\n';
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
	NS::map<char,int> mymaperase;
	NS::map<char,int>::iterator it2;

	// insert some values:
	mymaperase['a']=10;
	mymaperase['b']=20;
	mymaperase['c']=30;
	mymaperase['d']=40;
	mymaperase['e']=50;
	mymaperase['f']=60;

	it2=mymaperase.find('b');
	mymaperase.erase (it2);                   // erasing by iterator

	mymaperase.erase ('c');                  // erasing by key
	it2=mymaperase.find ('e');
	mymaperase.erase ( it2, mymaperase.end() );    // erasing by range
	// show content:
	for (it2=mymaperase.begin(); it2!=mymaperase.end(); ++it2)
	std::cout << it2->first << " => " << it2->second << '\n';
	/* swap */
	NS::map<char,int> foo,bar;

	foo['x']=100;
	foo['y']=200;

	bar['a']=11;
	bar['b']=22;
	bar['c']=33;

	foo.swap(bar);

	std::cout << "foo contains:\n";
	for (NS::map<char,int>::iterator _it=foo.begin(); _it!=foo.end(); ++_it)
	std::cout << _it->first << " => " << _it->second << '\n';

	std::cout << "bar contains:\n";
	for (NS::map<char,int>::iterator it1=bar.begin(); it1!=bar.end(); ++it1)
	std::cout << it1->first << " => " << it1->second << '\n';

	// /* key_compare */
	mymap.clear();

//   NS::map<char,int>::key_compare mycomp = mymap.key_comp();

  mymap['a']=100;
  mymap['b']=200;
  mymap['c']=300;

  std::cout << "mymap contains:\n";

  NS::pair<char, int> highest = *mymap.rbegin();     // key value of last element

  NS::map<char,int>::iterator _it = mymap.begin();
  do {
    std::cout << _it->first << " => " << _it->second << '\n';
  } while ( mymap.value_comp()(*_it++, highest) );

	std::cout << '\n';

	NS::map<char,int> mycmmmp;
	char c;

	mycmmmp ['a']=101;
	mycmmmp ['c']=202;
	mycmmmp ['f']=303;

	for (c='a'; c<'h'; c++)	
	{
	std::cout << c;
	if (mycmmmp.count(c)>0)
		std::cout << " is an element of mymap.\n";
	else 
		std::cout << " is not an element of mymap.\n";
	}

	NS::map<char,int> mapbound;
	NS::map<char,int>::iterator itlow,itup;

	mapbound['a']=20;
	// mapbound['b']=40;
	mapbound['c']=60;
	mapbound['d']=80;
	mapbound['e']=100;

	itlow=mapbound.lower_bound ('b');  // itlow points to b
	std::cout << "lower_bound: " << itlow->first << std::endl;
	itup=mapbound.upper_bound ('d');   // itup points to e (not d!)
	std::cout << "upper_bound: " << itup->first << std::endl;
	
	mapbound.erase(itlow,itup);        // erases [itlow,itup)

	// print content:
	for (NS::map<char,int>::iterator it=mapbound.begin(); it!=mapbound.end(); ++it)
	std::cout << it->first << " => " << it->second << '\n';

	return 0;
}
