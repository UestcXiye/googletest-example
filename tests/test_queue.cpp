#include "gtest/gtest.h"

#include <queue>

// 定义通用队列测试
template <typename T>
class QueueTest : public ::testing::Test {
protected:
    std::queue<T> queue;
};

TYPED_TEST_SUITE_P(QueueTest);

TYPED_TEST_P(QueueTest, EmptyByDefault) {
    EXPECT_TRUE(this->queue.empty());
}

TYPED_TEST_P(QueueTest, PushAndSize) {
    this->queue.push(TypeParam());
    EXPECT_EQ(this->queue.size(), 1);
    this->queue.push(TypeParam());
    EXPECT_EQ(this->queue.size(), 2);
}

TYPED_TEST_P(QueueTest, PopReducesSize) {
    this->queue.push(TypeParam());
    this->queue.push(TypeParam());
    this->queue.pop();
    EXPECT_EQ(this->queue.size(), 1);
}

// 注册所有测试
REGISTER_TYPED_TEST_SUITE_P(
    QueueTest,
    EmptyByDefault,
    PushAndSize,
    PopReducesSize
);

// 可以在不同地方用不同类型实例化
typedef ::testing::Types<int, double> NumericTypes;
INSTANTIATE_TYPED_TEST_SUITE_P(Numeric, QueueTest, NumericTypes);

typedef ::testing::Types<std::string, std::vector<int>> ComplexTypes;
INSTANTIATE_TYPED_TEST_SUITE_P(Complex, QueueTest, ComplexTypes);