#include <vector>
#include <iostream>
#include <boost/timer/timer.hpp>

using namespace std;
int price[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

int CutRod(int length) {
  if (length == 0) {
    return 0;
  }
  int q = 0;
  for (int i = 1; i <= length; ++i) {
    q = max(q, price[i] + CutRod(length - i));
  }
  return q;
}

void testNest() {
  cout << __func__ << endl;
  boost::timer::auto_cpu_timer t;
  for (int i = 1; i <= 10; ++i) {
    cout << i << " price is " << CutRod(i) << endl;
  }
}

int MemoizedCutRodAux(vector<int> &maxPrice, int length) {
  if (length == 0) {
    return 0;
  }
  if (maxPrice[length] > 0) {
    return maxPrice[length];
  }
  int maxTmpPrice = 0;
  for (int i = 1; i <= length; ++i) {
    maxTmpPrice = max(maxTmpPrice, price[i] + MemoizedCutRodAux(maxPrice, length - i));
  }
  maxPrice[length] = maxTmpPrice;
  return maxTmpPrice;
}

int MemoizedCutRod(int length) {
  static vector<int> maxPrice(11, 0);
  return MemoizedCutRodAux(maxPrice, length);
}

void testMemoize() {
  cout << __func__ << endl;
  boost::timer::auto_cpu_timer t;
  for (int i = 1; i <= 10; ++i) {
    cout << i << " price is " << MemoizedCutRod(i) << endl;
  }
}

int BottomUpCutRob(int length) {
  vector<int> maxPrice(length + 1, 0);
  for (int i = 1; i <= length; ++i) {
    int tmpPrice = 0;
    for (int j = 1; j <= i; ++j) {
      tmpPrice = max(tmpPrice, price[j] + maxPrice[i - j]);
    }
    maxPrice[i] = tmpPrice;
  }
  return maxPrice[length];
}

void testBottomUp() {
  cout << __func__ << endl;
  boost::timer::auto_cpu_timer t;
  for (int i = 1; i <= 10; ++i) {
    cout << i << " price is " << BottomUpCutRob(i) << endl;
  }
}

pair<int, int> ExtendedBottomUpCutRob(int length) {
  vector<pair<int, int>> maxPrice(length + 1);
  for (int i = 1; i <= length; ++i) {
    pair<int, int> tmpPrice{0, 0};
    for (int j = 1; j <= i; ++j) {
      if (tmpPrice.first < price[j] + maxPrice[i - j].first) {
        tmpPrice.first = price[j] + maxPrice[i - j].first;
        tmpPrice.second = j;
      }
    }
    maxPrice[i] = tmpPrice;
  }
  return maxPrice[length];
}

void testExtended() {
  cout << __func__ << endl;
  boost::timer::auto_cpu_timer t;
  for (int i = 1; i <= 10; ++i) {
    auto ret = ExtendedBottomUpCutRob(i);
    cout << ret.first << " : " << ret.second << endl;
  }
}

int main() {
  cout << "hello cut" << endl;
  testExtended();
  testNest();
}