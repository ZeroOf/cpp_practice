
#include "queue.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;


Queue::Queue()
        : _nu_front(0), _nu_back(0) {
    cout << "queue()" << endl;
}


bool Queue::empty() const {
    return !(_nu_front - _nu_back);
}

bool Queue::full() const {
    return !((_nu_back + 1) % 10 - _nu_front);
}

void Queue::push(int x) {
    if (full()) {
        cout << "full" << endl;
    } else {
        _data[_nu_back] = x;
        _nu_back = (_nu_back + 1) % 10;
    }
}

void Queue::pop() {
    if (empty()) {
        cout << "empty" << endl;
    } else {
        _nu_front = (_nu_front + 1) % 10;
    }
}

int Queue::front() {
    int ret = 0;
    if (empty()) {
        cout << "empty" << endl;
    } else {
        ret = _data[_nu_front];
    }
    return ret;
}

int Queue::back() {
    int ret = 0;
    if (empty()) {
        cout << "empty" << endl;
    } else {
        ret = _data[(_nu_back + 9) % 10];
    }
    return ret;
}


Queue::~Queue() {
    cout << "~stack" << endl;
}

int main() {
    Queue q;
    cout << q.front() << endl;
    int i;
    for (i = 1; i < 20; i++) {
        q.push(i);
        if (i % 2) q.pop();
        cout << "front:" << q.front() << endl;
        cout << "back:" << q.back() << endl;

    }
    for (i = 0; i < 10; i++) {
        q.pop();
        cout << "front:" << q.front() << endl;
    }
    return 0;
}
