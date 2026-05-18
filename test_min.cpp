#include "gtest/gtest.h"
#include "min.h"

// 使用类型化测试
template <typename T>
class MinFunctionTest : public ::testing::Test {};

typedef ::testing::Types<int, double, char> TestTypes;
TYPED_TEST_SUITE(MinFunctionTest, TestTypes);

TYPED_TEST(MinFunctionTest, ReturnSmaller) {
    TypeParam a = static_cast<TypeParam>(5);
    TypeParam b = static_cast<TypeParam>(3);
    EXPECT_EQ(min(a, b), b);
    EXPECT_EQ(min(b, a), b);
}
