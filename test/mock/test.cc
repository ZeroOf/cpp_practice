//
// Created by Will Lee on 2021/10/5.
//

#include "MockTurtle.h"

using ::testing::AtLeast;

TEST(PaintTest, CanDrawSometing) {
    MockTurtle turtle;
    EXPECT_CALL(turtle, PenDown()).Times(testing::AtLeast(1));

    turtle.PenDown();
}