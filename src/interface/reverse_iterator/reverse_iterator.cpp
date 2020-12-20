#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
 
int main(void)
{
	vector<int> numbers{1, 2, 3, 4, 5, 6};
	vector<int>::reverse_iterator rit = numbers.rbegin();
	rit += 2;
	cout << *rit << endl;

	while(rit != numbers.rend())
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;
	return 0;
}
