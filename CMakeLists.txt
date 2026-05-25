cmake_minimum_required(VERSION 3.14.0)
project(unit_test_demo VERSION 0.1.0 LANGUAGES C CXX)

add_library(example_lib
    src/calculator.cpp
    src/max.cpp
)
target_include_directories(example_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 下载并包含 GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    # 对于 GoogleTest 1.11以及后续版本，可能需要使用 GIT_REPOSITORY 和 GIT_TAG 来代替 URL
    URL https://gitee.com/mirrors/googletest/repository/archive/main.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

add_executable(main src/main.cpp tests/test_max.cpp)
target_link_libraries(main PRIVATE example_lib gtest)

# 启用测试
include(CTest)
enable_testing()
add_test(NAME custom_listener_demo COMMAND main)

function(add_gtest_target target)
    add_executable(${target} ${ARGN})
    target_link_libraries(${target} PRIVATE example_lib gtest_main)
    add_test(NAME ${target} COMMAND ${target})
endfunction()

# test_global_environment 有自定义 main，用于演示全局测试环境事件
add_executable(test_global_environment tests/test_global_environment.cpp)
target_link_libraries(test_global_environment PRIVATE example_lib gtest)
add_test(NAME test_global_environment COMMAND test_global_environment)

add_executable(test_program_iteration tests/test_program_iteration.cpp)
target_link_libraries(test_program_iteration PRIVATE gtest)
add_test(
    NAME test_program_iteration
    COMMAND test_program_iteration --gtest_repeat=2
)

add_gtest_target(test_max tests/test_max.cpp)
add_gtest_target(test_min tests/test_min.cpp)
add_gtest_target(test_prime tests/test_prime.cpp)
add_gtest_target(test_suite tests/test_suite.cpp)
add_gtest_target(test_calculator tests/test_calculator.cpp)
add_gtest_target(test_container tests/test_container.cpp)
add_gtest_target(test_numeric tests/test_numeric.cpp)
add_gtest_target(test_queue tests/test_queue.cpp)
add_gtest_target(test_bank_vault tests/test_bank_vault.cpp)
add_gtest_target(test_utility tests/test_utility.cpp)
add_gtest_target(test_database tests/test_database.cpp)
add_gtest_target(test_add_param tests/test_add_param.cpp)
add_gtest_target(test_custom_assertion tests/test_custom_assertion.cpp)
add_gtest_target(test_calculator_namespace tests/test_calculator_namespace.cpp)
add_gtest_target(test_calculator_nested_namespace tests/test_calculator_nested_namespace.cpp)

add_executable(test_network_client tests/test_network_client.cpp)
target_link_libraries(test_network_client PRIVATE example_lib gmock_main)
add_test(NAME test_network_client COMMAND test_network_client)
