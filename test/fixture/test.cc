//
// Created by Will Lee on 2021/10/3.
//

#include "Queue.hpp"
#include "gtest/gtest.h"

class QueueTest : public ::testing::Test {
protected:
    void SetUp() override {
        q1_.push(1);
        q2_.push(2);
        q2_.push(3);
    }

    Queue<int> q0_;
    Queue<int> q1_;
    Queue<int> q2_;
};

TEST_F(QueueTest, isEmptyInitially) {
    EXPECT_TRUE(q0_.empty());
}

TEST_F(QueueTest, DequeueWorks) {
    EXPECT_EQ(q1_.front(), 1);
}

int main(int argc, char**argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}