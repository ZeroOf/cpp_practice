
#ifndef __WD_THREAD_H__
#define __WD_THREAD_H__

#include "Noncopyable.h"
#include <pthread.h>
#include <functional>

namespace net {

//这是一个具体类
    class Thread
            : Noncopyable {
    public:
        typedef std::function<void()> ThreadCallback;

        Thread(ThreadCallback &&cb);

        ~Thread();

        void Start();

        void Join();

        inline bool IsRunning() const { return _isRunning; }

    private:
        static void *threadFunc(void *arg);//线程的执行体
    private:
        pthread_t _pthid;
        bool _isRunning;
        ThreadCallback _cb;
    };

}//end of namespace net
#endif 



