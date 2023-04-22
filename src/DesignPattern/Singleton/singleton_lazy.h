
#ifndef CPP_PRACTICE_SINGLETONLAZY_H
#define CPP_PRACTICE_SINGLETONLAZY_H


class SingletonLazy {
public:
    static SingletonLazy *instance();

private:
    static void init();

    static void destroy();

    SingletonLazy();

    ~SingletonLazy();

    static SingletonLazy *pInstance_;
    static pthread_once_t once_;
};


#endif //CPP_PRACTICE_SINGLETONLAZY_H
