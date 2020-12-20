
#ifndef __WD_EVENTFD_H__
#define __WD_EVENTFD_H__

#include <functional>


namespace wd {

    class Eventfd {
    public:
        using EventfdCallback = std::function<void()>;

        Eventfd(EventfdCallback &&cb);

        ~Eventfd();

        void Start();

        void Stop();

        void Wakeup();

    private:
        int createEventfd();

        void handleRead();

    private:
        int _fd;
        bool _isStarted;
        EventfdCallback _cb;
    };

}//end of namespace wd

#endif
