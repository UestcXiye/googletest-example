#include "gtest/gtest.h"
#include "calculator.h"

#include <stdexcept>

namespace calculator_namespace_test {

class CalculatorNamespaceTest : public ::testing::Test {
protected:
    Calculator calculator;
};

TEST_F(CalculatorNamespaceTest, Add) {
    EXPECT_DOUBLE_EQ(calculator.add(2.0, 3.0), 5.0);
    EXPECT_DOUBLE_EQ(calculator.add(-2.0, 3.0), 1.0);
}

TEST_F(CalculatorNamespaceTest, Subtract) {
    EXPECT_DOUBLE_EQ(calculator.subtract(5.0, 3.0), 2.0);
    EXPECT_DOUBLE_EQ(calculator.subtract(-2.0, -3.0), 1.0);
}

TEST_F(CalculatorNamespaceTest, Multiply) {
    EXPECT_DOUBLE_EQ(calculator.multiply(4.0, 3.0), 12.0);
    EXPECT_DOUBLE_EQ(calculator.multiply(-2.0, 3.0), -6.0);
}

TEST_F(CalculatorNamespaceTest, Divide) {
    EXPECT_DOUBLE_EQ(calculator.divide(10.0, 2.0), 5.0);
    EXPECT_THROW(calculator.divide(10.0, 0.0), std::invalid_argument);
}

TEST_F(CalculatorNamespaceTest, Factorial) {
    EXPECT_EQ(calculator.factorial(0), 1);
    EXPECT_EQ(calculator.factorial(1), 1);
    EXPECT_EQ(calculator.factorial(5), 120);
}

} // namespace calculator_namespace_test
