
#ifndef CPP_PRACTICE_SINGLETONHUNGRY_H
#define CPP_PRACTICE_SINGLETONHUNGRY_H


class SingletonHungry {
public:
    class AutoRelease;
    static SingletonHungry* getInstance();
private:
    SingletonHungry() = default;
    ~SingletonHungry() = default;

    static SingletonHungry* pInstance_;
    static AutoRelease autoRelease_;
};


#endif //CPP_PRACTICE_SINGLETONHUNGRY_H
