#include <iostream>
#include <forward_list>

using namespace std;

/*
 * Compared to std::list this container provides more space efficient storage when bidirectional iteration is not needed.
 * forward_list is a singly linked list.
 *
 * member functions:
 *  - empty: checks if the list is empty
 *  - max_size: returns the maximum number of elements allowed in the list
 *  - front: returns a reference to the first element in the list
 *  - push_front: adds an element to the front of the list
 *  - pop_front: removes an element from the front of the list
 *  - reverse: reverses the order of the elements in the list
 *  - sort: sorts the elements in the list
 *  - merge: merges two sorted lists into one sorted list
 *  - splice_after: inserts elements from another list after a specified position
 *  - unique: removes duplicate elements from the list
 *  - remove: removes elements from the list that match a given value
 *  - remove_if: removes elements from the list that match a given condition
 *
 * iterators:
 *  - begin: returns an iterator to the first element in the list
 *  - end: returns an iterator to the element after the last element in the list
 */


template<typename T>
std::ostream &operator<<(std::ostream &s, const std::forward_list<T> &v) {
  s.put('{');
  for (char comma[]{'\0', ' ', '\0'}; const auto &e : v)
  s << comma << e, comma[0] = ',';
  return s << "}\n";
}

void DemoMerge() {
  forward_list<int> fl1 = {1, 2, 3};
  forward_list<int> fl2 = {4, 5, 6};
  fl1.merge(fl2);
  cout << fl1 << endl; // {1, 2, 3, 4, 5, 6}
}

void DemoRemove() {
  forward_list<int> fl = {1, 2, 3, 4, 5, 6};
  fl.remove(3);
  cout << fl << endl; // {1, 2, 4, 5, 6}
}

void DemoUnique() {
  forward_list<int> fl = {1, 2, 2, 3, 3, 3};
  fl.unique();
  cout << fl << endl; // {1, 2, 3}
}

void DemoSort() {
  forward_list<int> fl = {3, 2, 1, 6, 5, 4};
  fl.sort();
  cout << fl << endl; // {1, 2, 3, 4, 5, 6}
}

void DemoSpliceAfter() {
  std::cout << "DemoSpliceAfter" << std::endl;
  forward_list<int> fl1 = {1, 2, 3};
  forward_list<int> fl2 = {4, 5, 6};
  fl1.splice_after(fl1.begin(), fl2);
  cout << fl1 << endl; // {1, 2, 3, 4, 5, 6}

  cout << "fl2:" << fl2 << endl;
}

int main() {
  DemoMerge();
  DemoRemove();
  DemoUnique();
  DemoSort();
  DemoSpliceAfter();
  return 0;
}
