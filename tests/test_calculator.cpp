#include "gtest/gtest.h"
#include "calculator.h"

class CalculatorTest : public ::testing::TestWithParam<
    std::tuple<double, double, char, double>> {
};

TEST_P(CalculatorTest, Operations) {
    double a = std::get<0>(GetParam());
    double b = std::get<1>(GetParam());
    char op = std::get<2>(GetParam());
    double expected = std::get<3>(GetParam());
    
    Calculator calc;
    double result;
    
    switch (op) {
        case '+': result = calc.add(a, b); break;
        case '-': result = calc.subtract(a, b); break;
        case '*': result = calc.multiply(a, b); break;
        case '/': result = calc.divide(a, b); break;
    }
    
    EXPECT_NEAR(result, expected, 0.0001);
}

INSTANTIATE_TEST_SUITE_P(
    BasicOperations,
    CalculatorTest,
    ::testing::Values(
        std::make_tuple(2.0, 3.0, '+', 5.0),
        std::make_tuple(5.0, 3.0, '-', 2.0),
        std::make_tuple(4.0, 3.0, '*', 12.0),
        std::make_tuple(10.0, 2.0, '/', 5.0)
    )
);

class CalculatorCombinedTest : public ::testing::TestWithParam<
    std::tuple<double, double, char>> {
};

TEST_P(CalculatorCombinedTest, Operations) {
    double a = std::get<0>(GetParam());
    double b = std::get<1>(GetParam());
    char op = std::get<2>(GetParam());

    Calculator calc;
    double result = 0.0;
    double expected = 0.0;

    switch (op) {
        case '+':
            result = calc.add(a, b);
            expected = a + b;
            break;
        case '-':
            result = calc.subtract(a, b);
            expected = a - b;
            break;
    }

    EXPECT_NEAR(result, expected, 0.0001);
}

INSTANTIATE_TEST_SUITE_P(
    CombinedOperations,
    CalculatorCombinedTest,
    ::testing::Combine(
        ::testing::Values(1.0, 2.0),      // a
        ::testing::Values(3.0, 4.0),      // b
        ::testing::Values('+', '-')       // op
    )
);
