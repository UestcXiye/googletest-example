#include "gtest/gtest.h"

class LifecycleTest : public ::testing::Test {
protected:
    LifecycleTest() { std::cout << "1. Constructor\n"; }
    ~LifecycleTest() { std::cout << "5. Destructor\n"; }
    
    void SetUp() override { std::cout << "2. SetUp\n"; }
    void TearDown() override { std::cout << "4. TearDown\n"; }
    
    static void SetUpTestSuite() { std::cout << "0. SetUpTestSuite\n"; }
    static void TearDownTestSuite() { std::cout << "6. TearDownTestSuite\n"; }
};

TEST_F(LifecycleTest, Test1) {
    std::cout << "3. Test1 body\n";
}

TEST_F(LifecycleTest, Test2) {
    std::cout << "3. Test2 body\n";
}

// 输出顺序：
// 0. SetUpTestSuite
// 1. Constructor
// 2. SetUp
// 3. Test1 body
// 4. TearDown
// 5. Destructor
// 1. Constructor
// 2. SetUp
// 3. Test2 body
// 4. TearDown
// 5. Destructor
// 6. TearDownTestSuite