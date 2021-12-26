//
// Created by Will Lee on 2021/12/9.
//

#ifndef CPP_PRACTICE_APPBASE_H
#define CPP_PRACTICE_APPBASE_H

#include <boost/asio.hpp>

class AppBase {
public:
    AppBase();

    void Run();

private:
    virtual bool OnActivite() = 0;

    virtual void OnDeactivite() = 0;

    void Daemon();

    void SetSignal();

protected:
    boost::asio::thread_pool threadPool_;
};


#endif //CPP_PRACTICE_APPBASE_H
