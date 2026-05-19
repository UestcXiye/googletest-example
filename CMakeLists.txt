cmake_minimum_required(VERSION 3.14.0)
project(unit_test_demo VERSION 0.1.0 LANGUAGES C CXX)

add_library(example_lib
    src/calculator.cpp
    src/max.cpp
)
target_include_directories(example_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE example_lib)

# 下载并包含 GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    # 对于 GoogleTest 1.11以及后续版本，可能需要使用 GIT_REPOSITORY 和 GIT_TAG 来代替 URL
    URL https://gitee.com/mirrors/googletest/repository/archive/main.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

# 启用测试
include(CTest)
enable_testing()

function(add_gtest_target target)
    add_executable(${target} ${ARGN})
    target_link_libraries(${target} PRIVATE example_lib gtest_main)
    add_test(NAME ${target} COMMAND ${target})
endfunction()

# test_main 有自定义 main，所以链接 gtest 而不是 gtest_main
add_executable(test_main tests/test_main.cpp)
target_link_libraries(test_main PRIVATE example_lib gtest)
add_test(NAME test_main COMMAND test_main)

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
