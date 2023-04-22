//
// Created by Will Lee on 2021/10/16.
//

#ifndef CPP_PRACTICE_SECONDGRID_H
#define CPP_PRACTICE_SECONDGRID_H

#include "TimerTask.h"

class SecondGrid {

private:
    std::unordered_map<uint64_t, TimerTask> seq2Task_;
};


#endif //CPP_PRACTICE_SECONDGRID_H
