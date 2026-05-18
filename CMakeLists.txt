cmake_minimum_required(VERSION 3.10.0)
project(unit_test_demo VERSION 0.1.0 LANGUAGES C CXX)

# 添加主程序
add_executable(main main.cpp max.cpp)

# 下载并包含 GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    # 对于 GoogleTest 1.11以及后续版本，可能需要使用 GIT_REPOSITORY 和 GIT_TAG 来代替 URL
    URL https://gitee.com/mirrors/googletest/repository/archive/main.zip
)
# 下载并使 GoogleTest 可用
FetchContent_MakeAvailable(googletest)

# 启用测试
include(CTest)
enable_testing()

# 添加测试可执行文件
add_executable(test_main test_main.cpp max.cpp)
# 链接 GoogleTest
target_link_libraries(test_main gtest) # 注意：用 gtest 而不是 gtest_main，因为我们有自定义 main
# 注册测试
add_test(NAME test_main COMMAND test_main)

# 添加测试可执行文件
add_executable(test_max test_max.cpp max.cpp)
# 链接 GoogleTest
target_link_libraries(test_max gtest_main)
# 注册测试
add_test(NAME test_max COMMAND test_max)

add_executable(test_min test_min.cpp)
target_link_libraries(test_min gtest_main)
add_test(NAME test_min COMMAND test_min)

add_executable(test_prime test_prime.cpp)
target_link_libraries(test_prime gtest_main)
add_test(NAME test_prime COMMAND test_prime)

add_executable(test_suite test_suite.cpp)
target_link_libraries(test_suite gtest_main)
add_test(NAME test_suite COMMAND test_suite)

add_executable(test_calculator test_calculator.cpp calculator.cpp)
target_link_libraries(test_calculator gtest_main)
add_test(NAME test_calculator COMMAND test_calculator)

add_executable(test_container test_container.cpp)
target_link_libraries(test_container gtest_main)
add_test(NAME test_container COMMAND test_container)

add_executable(test_numeric test_numeric.cpp)
target_link_libraries(test_numeric gtest_main)
add_test(NAME test_numeric COMMAND test_numeric)

add_executable(test_queue test_queue.cpp)
target_link_libraries(test_queue gtest_main)
add_test(NAME test_queue COMMAND test_queue)

add_executable(test_bank_vault test_bank_vault.cpp)
target_link_libraries(test_bank_vault gtest_main)
add_test(NAME test_bank_vault COMMAND test_bank_vault)

add_executable(test_utility test_utility.cpp)
target_link_libraries(test_utility gtest_main)
add_test(NAME test_utility COMMAND test_utility)