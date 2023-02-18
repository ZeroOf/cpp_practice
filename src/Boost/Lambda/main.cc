
#include <iostream>
#include <boost/lambda/lambda.hpp>
#include <algorithm>
#include <list>

using namespace std;
using namespace boost::lambda;

int main() {
    list<int> v(10);
    for_each(v.begin(), v.end(), _1 = 1);
    for_each(v.begin(), v.end(), cout << _1 << "\n");

    vector<int*> vp(10);
    transform(v.begin(), v.end(), vp.begin(), &_1);
    for_each(vp.begin(), vp.end(), cout << _1 << "\n");
    int i = 1; int j = 2;
    (_1 + _2)(i, j); // ok
}