#pragma once

#ifndef CUSTOM_LISTENER_H
#define CUSTOM_LISTENER_H

#include <gtest/gtest.h>

#include <fstream>
#include <string>

class CustomListener : public ::testing::EmptyTestEventListener {
public:
    explicit CustomListener(const std::string& log_file)
        : log_stream_(log_file, std::ios::out | std::ios::trunc) {}

    void OnTestProgramStart(const ::testing::UnitTest& unit_test) override {
        log_stream_ << "测试程序开始\n";
    }

    void OnTestSuiteStart(const ::testing::TestSuite& test_suite) override {
        log_stream_ << "测试套件开始: " << test_suite.name() << "\n";
    }

    void OnTestStart(const ::testing::TestInfo& test_info) override {
        log_stream_ << "测试开始: " << test_info.test_suite_name() << "." << test_info.name() << "\n";
    }

    void OnTestEnd(const ::testing::TestInfo& test_info) override {
        log_stream_ << "测试结束: " << test_info.test_suite_name() << "." << test_info.name()
                    << " - " << (test_info.result()->Passed() ? "通过" : "失败") << "\n";
    }

    void OnTestSuiteEnd(const ::testing::TestSuite& test_suite) override {
        log_stream_ << "测试套件结束: " << test_suite.name() << "\n";
    }

    void OnTestProgramEnd(const ::testing::UnitTest& unit_test) override {
        log_stream_ << "测试程序结束\n";
        log_stream_.flush();
    }

private:
    std::ofstream log_stream_;
};

#endif // CUSTOM_LISTENER_H
