#include "gtest/gtest.h"

#include <iostream>

class FooTest : public ::testing::Test
{
protected:
  static void SetUpTestCase() {
    std::cout << "TestSuite SetUp" << std::endl;
  }

  static void TearDownTestCase() {
    std::cout << "TestSuite TearDown" << std::endl;
  }

  void SetUp() override {
        std::cout << "TestCase SetUp" << std::endl;
    }

    void TearDown() override {
        std::cout << "TestCase TearDown" << std::endl;
    }
};

TEST_F(FooTest, Test1)
{
    std::cout << "Test 1" << std::endl;
}

TEST_F(FooTest, Test2)
{
    std::cout << "Test 2" << std::endl;
}
