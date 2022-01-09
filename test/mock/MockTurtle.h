//
// Created by Will Lee on 2021/10/5.
//

#ifndef CPP_PRACTICE_MOCKTURTLE_H
#define CPP_PRACTICE_MOCKTURTLE_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>

class MockTurtle : public Turtle {
public:
    MOCK_METHOD(void, PenUp, (), (override));
    MOCK_METHOD(void, PenDown, (), (override));
    MOCK_METHOD(void, Forward, (int distance), (override));
    MOCK_METHOD(void, Turn, (int degrees), (override));
    MOCK_METHOD(void, GoTo, (int x, int y), (override));
    MOCK_METHOD(int, GetX, (), (const, override));
    MOCK_METHOD(int, GetY, (), (const, override));
};


#endif //CPP_PRACTICE_MOCKTURTLE_H
