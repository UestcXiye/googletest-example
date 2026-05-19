#include "gtest/gtest.h"

int add(int a, int b) {
    return a + b;
}

struct AddParam {
    int a;
    int b;
    int expected;
};

class AddTest : public ::testing::TestWithParam<AddParam> {
};

TEST_P(AddTest, HandlesDifferentInputs) {
    AddParam param = GetParam();

    EXPECT_EQ(add(param.a, param.b), param.expected);
}

INSTANTIATE_TEST_SUITE_P(
    AddCases,
    AddTest,
    ::testing::Values(
        AddParam{1, 2, 3},
        AddParam{0, 0, 0},
        AddParam{-1, 1, 0},
        AddParam{-2, -3, -5},
        AddParam{100, 200, 300}
    )
);
