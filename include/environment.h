#pragma once

#include "gtest/gtest.h"

#include <iostream>

class GlobalTestEnvironment : public ::testing::Environment
{
public:
    // 在所有测试开始前执行一次
    void SetUp() override
    {
        std::cout << "Global Test Environment SetUp" << std::endl;
    }

    // 在所有测试结束后执行一次
    void TearDown() override
    {
       std::cout << "Global Test Environment TearDown" << std::endl;
    }
};