#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
using std::for_each;
using std::remove_if;


class Number
{
public:
	Number(int value)
	: _value(value)
	{}
	
	void display() const
	{	cout << _value << " ";	}
	
	bool isEven() const
	{
		return   (_value % 2 == 0);
	}

	bool isPrime() const
	{
		if(_value == 1)
			return false;
		for(int idx = 2; idx <= _value/2; ++idx)
		{
			if(_value % idx == 0)
				return false;
		}
		return true;
	}
private:
	int _value;
};
 
int main(void)
{
	vector<Number> numbers;
	for(int idx = 1; idx != 20; ++idx)
	{
		numbers.push_back(Number(idx));
	}

	for_each(numbers.begin(), numbers.end(), std::mem_fn(&Number::display));
	cout << endl;

	numbers.erase(std::remove_if(numbers.begin(), numbers.end(), std::mem_fn(&Number::isPrime)),
				  numbers.end());
	for_each(numbers.begin(), numbers.end(), std::mem_fn(&Number::display));
	cout << endl;
	return 0;
}
