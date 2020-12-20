#ifndef CPP_PRACTICE_TSSINGLETON_HPP
#define CPP_PRACTICE_TSSINGLETON_HPP

template<typename Type>
class TSSingleton {
public:
    template<typename... Args>
    //Args 模板参数包
    static Type *getInstance(Args... args) //args 函数参数包
    {
        pthread_once(&_once, init);// 在多线程环境下，init只会被执行一次
        if (!_pInstance->isInitEnd())
            _pInstance->init(args...);
        return _pInstance;
    }

    static void init() {
        atexit(destroy);
        _pInstance = new Type;
    }

    static void destroy() {
        if (_pInstance)
            delete _pInstance;
    }

private:
    TSSingleton();

    ~TSSingleton();

private:
    static Type *_pInstance;
    static pthread_once_t _once;
};

template<typename Type>
Type *TSSingleton<Type>::_pInstance = NULL;

template<typename Type>
pthread_once_t TSSingleton<Type>::_once = PTHREAD_ONCE_INIT;

#endif //CPP_PRACTICE_TSSINGLETON_HPP
