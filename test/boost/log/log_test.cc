//
// Created by Will Lee on 2021/11/27.
//

#include <logwrapper/log_wrappter.h>
#include <gtest/gtest.h>


TEST(LOG, WriteLog) {
    while(true) {
        LOG_INFO("test log");
    }
}