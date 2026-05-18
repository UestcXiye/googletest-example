#include "gtest/gtest.h"
#include "utility.h"

TEST(UtilityTest, PrivateStaticMethod) {
    EXPECT_EQ(UtilityTestAccess::CallPrivateMethod(5), 10);
    EXPECT_EQ(UtilityTestAccess::CallPrivateMethod(0), 0);
    EXPECT_EQ(UtilityTestAccess::CallPrivateMethod(-1), -2);
}