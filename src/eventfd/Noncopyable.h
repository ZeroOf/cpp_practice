
#ifndef __WD_NONCOPYABLE_H__
#define __WD_NONCOPYABLE_H__

namespace net {

    class Noncopyable {
    protected:
        Noncopyable() {}

        ~Noncopyable() {}

        Noncopyable(const Noncopyable &) = delete;

        Noncopyable &operator=(const Noncopyable &) = delete;
    };
}


#endif
