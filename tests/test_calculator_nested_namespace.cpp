#include "gtest/gtest.h"
#include "calculator.h"

#include <stdexcept>

namespace calculator {

namespace add {

TEST(CalculatorAddTest, HandlesPositiveAndNegativeNumbers) {
    Calculator calculator;

    EXPECT_DOUBLE_EQ(calculator.add(1.5, 2.5), 4.0);
    EXPECT_DOUBLE_EQ(calculator.add(-4.0, 6.0), 2.0);
}

} // namespace add

namespace subtract {

TEST(CalculatorSubtractTest, HandlesPositiveAndNegativeNumbers) {
    Calculator calculator;

    EXPECT_DOUBLE_EQ(calculator.subtract(8.0, 3.0), 5.0);
    EXPECT_DOUBLE_EQ(calculator.subtract(-8.0, -3.0), -5.0);
}

} // namespace subtract

namespace multiply {

TEST(CalculatorMultiplyTest, HandlesPositiveAndNegativeNumbers) {
    Calculator calculator;

    EXPECT_DOUBLE_EQ(calculator.multiply(6.0, 7.0), 42.0);
    EXPECT_DOUBLE_EQ(calculator.multiply(-3.0, 4.0), -12.0);
}

} // namespace multiply

namespace divide {

TEST(CalculatorDivideTest, HandlesValidInputAndDivisionByZero) {
    Calculator calculator;

    EXPECT_DOUBLE_EQ(calculator.divide(9.0, 3.0), 3.0);
    EXPECT_THROW(calculator.divide(9.0, 0.0), std::invalid_argument);
}

} // namespace divide

namespace factorial {

TEST(CalculatorFactorialTest, HandlesZeroOneAndPositiveNumbers) {
    Calculator calculator;

    EXPECT_EQ(calculator.factorial(0), 1);
    EXPECT_EQ(calculator.factorial(1), 1);
    EXPECT_EQ(calculator.factorial(6), 720);
}

} // namespace factorial

} // namespace calculator
