#include "gtest/gtest.h"
#include "max.h"

TEST(Max, MaxOf3And5)
{
    EXPECT_EQ(5, max(3, 5));
}

TEST(Max, MaxOf10And5)
{
    EXPECT_NE(5, max(10, 5));
}
