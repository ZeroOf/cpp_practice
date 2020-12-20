
#ifndef CPP_PRACTICE_SINGLETON_HPP
#define CPP_PRACTICE_SINGLETON_HPP

template<typename T>
class Singleton {
public:
    template<typename...args>
    static T *getInstance(args... arg) {
        if (!instance_) {
            autorelease_;
            instance_ = new T(arg...);
        }
        return instance_;
    }

private:
    class Autorelease {
    public:
        ~Autorelease() {
            if (instance_)
                delete instance_;
        }
    };

    static T *instance_;
    static Autorelease autorelease_;
};

template<typename T>
T *Singleton<T>::instance_ = nullptr;

template<typename T>
class Singleton<T>::Autorelease Singleton<T>::autorelease_;

#endif //CPP_PRACTICE_SINGLETON_HPP
