//
// Created by Will Lee on 2021/10/1.
//

#include <boost/coroutine2/all.hpp>
#include <iostream>

using core_t = boost::coroutines2::coroutine<bool>;

void FirstPrint(core_t::push_type &notify) {
    for (int i = 0; i < 10; ++i) {
        std::cout << "print 1" << std::endl;
        notify(true);
    }
    notify(false);
}

void SecondPrint(core_t::pull_type &wait) {
    for (auto i: wait) {
        if (i) {
            std::cout << "print 2" << std::endl;
        }
    }
}

int main() {
    core_t::pull_type async(boost::coroutines2::fixedsize_stack(),
                            [](core_t::push_type &yield) {
                                FirstPrint(yield);
                            });
    SecondPrint(async);
}