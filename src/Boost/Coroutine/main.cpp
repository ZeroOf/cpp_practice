
#include <boost/coroutine2/coroutine.hpp>
#include <iostream>

int main() {
    typedef boost::coroutines2::coroutine<int> coro_t;

    coro_t::pull_type source(
            [&](coro_t::push_type &sink) {
                int first = 1, second = 1;
                sink(first);
                sink(second);
                for (int i = 0; i < 8; ++i) {
                    int third = first + second;
                    first = second;
                    second = third;
                    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
                    sink(third);
                }
            });

    for (auto i:source)
        std::cout << i << " ";
}