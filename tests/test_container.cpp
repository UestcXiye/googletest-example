#include "gtest/gtest.h"

#include <vector>
#include <deque>
#include <list>

// 测试不同类型的容器
template <typename T>
class ContainerTest : public ::testing::Test {
protected:
    T container;
    
    void SetUp() override {
        // 添加测试数据
        container.push_back(1);
        container.push_back(2);
        container.push_back(3);
    }

    void TearDown() override {
        // 清空数据
        container.clear();
    }
};

// 要测试的容器类型
typedef ::testing::Types<
    std::vector<int>,
    std::deque<int>,
    std::list<int>
> ContainerTypes;

TYPED_TEST_SUITE(ContainerTest, ContainerTypes);

TYPED_TEST(ContainerTest, InitialSize) {
    EXPECT_EQ(this->container.size(), 3);
}

TYPED_TEST(ContainerTest, Clear) {
    this->container.clear();
    EXPECT_TRUE(this->container.empty());
}

TYPED_TEST(ContainerTest, FrontBack) {
    EXPECT_EQ(this->container.front(), 1);
    EXPECT_EQ(this->container.back(), 3);
}