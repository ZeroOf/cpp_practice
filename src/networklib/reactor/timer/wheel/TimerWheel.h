//
// Created by Will Lee on 2021/10/16.
//

#ifndef CPP_PRACTICE_TIMERWHEEL_H
#define CPP_PRACTICE_TIMERWHEEL_H

#include "SecondGrid.h"
#include <array>

class TimerWheel {
    const size_t static SecondsPerMinunes = 60;
    std::array<SecondGrid, SecondsPerMinunes> grids_;
public:
    void OnSecond();

    uint64_t RegisterTime(std::function<void()> &&func, uint64_t seconds, bool isRepeat = false, uint64_t interval = 0);

    bool UnregisteTimer(uint64_t seq);
};


#endif //CPP_PRACTICE_TIMERWHEEL_H
