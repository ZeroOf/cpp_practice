#include "TimerThread.h"
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <functional>

using std::cout;
using std::endl;

int test0() {
    Timer timer(3, 6, []() {
        srand(clock());
        int number = rand() % 100;
        cout << " number = " << number << endl;
    });

    Thread thread(std::bind(&Timer::Start, &timer));
  thread.Start();
    sleep(30);
  timer.Stop();
    thread.join();
    return 0;
}

int test1() {
    TimerThread timer(3, 6, []() {
        srand(clock());
        int number = rand() % 100;
        cout << "number = " << number << endl;
    });
  timer.Start();
    sleep(30);
  timer.Stop();
    return 0;
}

int main() {
    test1();
    return 0;
}
