//
// Created by Will Lee on 2021/11/27.
//

#include <gtest/gtest.h>
#include "Boost/Log/logwrapper/log_wrapper.h"

TEST(LOG, WriteLog) {
    while(true) {
        LOG_INFO("test log");
    }
}