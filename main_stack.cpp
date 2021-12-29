#include <iostream>       // std::cout
#include <stack>
#include "srcs/Stack.hpp"
#include <vector>

#ifndef NS
# define NS ft
#endif

int main ()
{
	NS::vector<int> myvector (2,200);

	NS::stack<int,NS::vector<int> > mystack (myvector);
	NS::stack<int,NS::vector<int> > mystack1 (mystack);
	std::cout << "equal: " <<  (mystack == mystack1) <<std::endl;

	std::cout << "size: " << mystack.size() << '\n';

	int sum (0);

	for (int i=1;i<=10;i++) mystack.push(i);

	while (!mystack.empty())
	{
		sum += mystack.top();
		mystack.pop();
	}

	std::cout << "total: " << sum << '\n';

	NS::stack<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';

	for (int i=0; i<5; i++) myints.push(i);
	std::cout << "1. size: " << myints.size() << '\n';

	myints.pop();
	std::cout << "2. size: " << myints.size() << '\n';

	mystack.top() += 2;

  	std::cout << "mystack.top() is now " << mystack.top() << '\n';

  return 0;
}