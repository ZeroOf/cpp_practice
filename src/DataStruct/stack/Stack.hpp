
#ifndef CPP_PRACTICE_STACK_HPP
#define CPP_PRACTICE_STACK_HPP

template<typename T=int, int size = 10>
class Stack {
    struct Node {
        T _value;
        Node *_next;
    };
public:
    Stack();

    ~Stack();

    bool IsEmpty();

    bool IsFull();

    bool Push(T value);

    bool Pop();

    T getTop();

private:
    Node *_head;
    int _size;
    Node *_point;
};

template<typename T, int size>
Stack<T, size>::Stack()
        : _head(NULL), _size(0) {
    cout << "Stack()" << endl;
}

template<typename T, int size>
Stack<T, size>::~Stack() {
    _point = _head;
    while (_point) {
        _point = _point->_next;
        delete _head;
        _head = _point;
    }
    cout << "~Stack()" << endl;
}

template<typename T, int size>
bool Stack<T, size>::IsEmpty() {
    return _size == 0;
}

template<typename T, int size>
bool Stack<T, size>::Push(T value) {
    if (IsFull()) return false;
    else {
        _point = new Node();
        _point->_value = value;
        _point->_next = _head;
        _head = _point;
        _size++;
    }
    return true;
}

template<typename T, int size>
bool Stack<T, size>::Pop() {
    if (IsEmpty()) return false;
    else {
        _point = _head;
        _head = _head->_next;
        delete _point;
        --_size;
    }
    return true;
}

template<typename T, int size>
T Stack<T, size>::getTop() {
    T *tmp = new T();
    if (IsEmpty()) return *tmp;
    else return _head->_value;
}

template<typename T, int size>
bool Stack<T, size>::IsFull() {
    return _size == size;
}

#endif //CPP_PRACTICE_STACK_HPP
