
#ifndef CPP_PRACTICE_QUEUE_H
#define CPP_PRACTICE_QUEUE_H

class Queue {
public:
    Queue();

    void push(int);

    void pop();

    int front();

    int back();

    bool empty() const;

    bool full() const;

    ~Queue();

private:
    int _data[10]{};
    int _nu_front;
    int _nu_back;
};


#endif //CPP_PRACTICE_QUEUE_H
