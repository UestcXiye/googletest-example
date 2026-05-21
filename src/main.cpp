#include <gtest/gtest.h>

#include "custom_listener.h"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();
    listeners.Append(new CustomListener("test_log.txt"));

    return RUN_ALL_TESTS();
}
