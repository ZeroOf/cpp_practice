#include <iostream>
#include <string>
#include <list>
#include <deque>
#include <set>
using namespace std;
void Set()
{
	set<string> set1;
	set1.insert("cat");
	set1.insert("dog");
}
int main()
{
	cout << "------------------------------------------" << endl
		 << "list" << endl;
	list<int> Is{1,3,5,7};
	list<int>::const_iterator pos = Is.cbegin();
	int a[3] = {4,5,6};
	auto t=Is.insert(pos,a,a+3); 
	cout << "t " << *t << endl;
	cout << "pos " << *pos << endl;
	cout << "------------------------------------------" << endl
		 << "deque" << endl;
	deque<int> De(10);
	return 0;
}

