
#ifndef CPP_PRACTICE_QUEUE_HPP
#define CPP_PRACTICE_QUEUE_HPP

template <typename Type, int kSize = 10>
class Queue
{
public:
    Queue();
    ~Queue();

    bool empty() const;
    bool full() const;
    void push(const Type & elem);
    void pop();
    Type & front();
    const Type & front() const
    {
        return _base[_front];
    }

    Type & back();
    const Type & back() const
    {
        return _base[(_rear - 1 + kSize) % kSize];
    }
private:
    int _front;
    int _rear;
    Type * _base;
};

template <typename Type, int kSize>
Queue<Type, kSize>::Queue()
        : _front(0)
        , _rear(0)
        , _base(new Type[kSize]())
{
}

template <typename Type, int kSize>
Queue<Type, kSize>::~Queue()
{
    delete [] _base;
}

template <typename Type, int kSize>
bool Queue<Type, kSize>::empty() const
{
    return _front == _rear;
}


template <typename Type, int kSize>
bool Queue<Type, kSize>::full() const
{
    return _front == (_rear + 1) % kSize;
}

template <typename Type, int kSize>
void Queue<Type, kSize>::push(const Type & element)
{
    if(full())
    {
        LogInfo("queue is full, cannot push an element");
    }
    else{
        _base[_rear++] = element;
        _rear %= kSize;
    }
}

template <typename Type, int kSize>
void Queue<Type, kSize>::pop()
{
    if(empty())
    {
        LogInfo("queue is empty, cannot pop an element");
        return;
    }
    ++_front;
    _front %= kSize;
}


template <typename Type, int kSize>
Type & Queue<Type, kSize>::front()
{
    return _base[_front];
}

template <typename Type, int kSize>
Type & Queue<Type, kSize>::back()
{
    return _base[(_rear - 1 + kSize) % kSize];
}

#endif //CPP_PRACTICE_QUEUE_HPP
