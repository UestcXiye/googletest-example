#include "gtest/gtest.h"

template <typename T>
class NumericTest : public ::testing::Test {
public:
    T Add(T a, T b) { return a + b; }
    T Multiply(T a, T b) { return a * b; }
};

typedef ::testing::Types<int, long, float, double> NumericTypes;
TYPED_TEST_SUITE(NumericTest, NumericTypes);

TYPED_TEST(NumericTest, Addition) {
    TypeParam a = static_cast<TypeParam>(2);
    TypeParam b = static_cast<TypeParam>(3);
    EXPECT_EQ(this->Add(a, b), static_cast<TypeParam>(5));
}

TYPED_TEST(NumericTest, Multiplication) {
    TypeParam a = static_cast<TypeParam>(4);
    TypeParam b = static_cast<TypeParam>(5);
    EXPECT_EQ(this->Multiply(a, b), static_cast<TypeParam>(20));
}