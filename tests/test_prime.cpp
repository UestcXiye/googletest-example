#include "gtest/gtest.h"

// 测试质数判断函数
class PrimeTest : public testing::TestWithParam<int> {
public:
    bool isPrime(int n) {
        if (n <= 1) return false;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0)
                return false;
        }
        return true;
    }
};

TEST_P(PrimeTest, CheckPrimality) {
    int n = GetParam();
    if (n == 2 || n == 3 || n == 5 || n == 7 || n == 11 || n == 13) {
        EXPECT_TRUE(isPrime(n)) << n << " should be prime";
    } else if (n <= 15) {
        EXPECT_FALSE(isPrime(n)) << n << " should not be prime";
    }
}

// 使用 Values 提供参数
INSTANTIATE_TEST_SUITE_P(
    SmallNumbers,
    PrimeTest,
    testing::Values(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15)
);

// 使用 Range 生成参数
INSTANTIATE_TEST_SUITE_P(
    RangeTest,
    PrimeTest,
    testing::Range(1, 20, 2)  // 1, 3, 5, 7, 9, 11, 13, 15, 17, 19
);

// 使用 ValuesIn 从容器获取参数
std::vector<int> GetTestNumbers() {
    return {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
}

INSTANTIATE_TEST_SUITE_P(
    FromVector,
    PrimeTest,
    testing::ValuesIn(GetTestNumbers())
);