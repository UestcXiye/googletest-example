#include "calculator.h"

#include <stdexcept>

double Calculator::add(double a, double b)
{
    return a + b;
}

double Calculator::subtract(double a, double b)
{
    return a - b;
}

double Calculator::multiply(double a, double b)
{
    return a * b;
}

double Calculator::divide(double a, double b)
{
    if (b == 0) {
        throw std::invalid_argument("Division by zero");
    }
    return a / b;
}

int Calculator::factorial(int n)
{
    if (n == 0 || n == 1)
        return 1;
    return factorial(n - 1) * n;
}