#include "environment.h"
#include "max.h"
#include "min.h"

TEST(MaxTest, NegativeNumbers) {
    EXPECT_EQ(max(-3, -5), -3);
    EXPECT_EQ(max(-10, -2), -2);
}

TEST(MaxTest, MixedNumbers) {
    EXPECT_EQ(max(-5, 5), 5);
    EXPECT_EQ(max(0, -10), 0);
}

// Min 函数测试
TEST(MinTest, PositiveNumbers) {
    EXPECT_EQ(min(3, 5), 3);
    EXPECT_EQ(min(10, 2), 2);
}

TEST(MinTest, NegativeNumbers) {
    EXPECT_EQ(min(-3, -5), -5);
    EXPECT_EQ(min(-10, -2), -10);
}

int main(int argc, char* argv[])
{
    // 注册全局环境
    ::testing::InitGoogleTest(&argc, argv);

    ::testing::AddGlobalTestEnvironment(new GlobalTestEnvironment);

    return RUN_ALL_TESTS();
}