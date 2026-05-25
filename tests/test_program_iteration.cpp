#include "gtest/gtest.h"

#include <fstream>

namespace {

class ProgramIterationListener : public ::testing::EmptyTestEventListener {
public:
    explicit ProgramIterationListener(const char* log_file)
        : log_stream_(log_file, std::ios::out | std::ios::trunc) {}

    void OnTestProgramStart(const ::testing::UnitTest& unit_test) override {
        log_stream_ << "ProgramStart: total_test_count="
                    << unit_test.total_test_count() << "\n";
    }

    void OnTestIterationStart(const ::testing::UnitTest& unit_test, int iteration) override {
        log_stream_ << "IterationStart: iteration=" << iteration
                    << ", total_test_count=" << unit_test.total_test_count() << "\n";
    }

    void OnTestIterationEnd(const ::testing::UnitTest& unit_test, int iteration) override {
        log_stream_ << "IterationEnd: iteration=" << iteration
                    << ", successful_test_count=" << unit_test.successful_test_count()
                    << ", failed_test_count=" << unit_test.failed_test_count() << "\n";
    }

    void OnTestProgramEnd(const ::testing::UnitTest& unit_test) override {
        log_stream_ << "ProgramEnd: passed="
                    << (unit_test.Passed() ? "true" : "false") << "\n";
        log_stream_.flush();
    }

private:
    std::ofstream log_stream_;
};

TEST(ProgramIterationListenerTest, RunsInEachIteration) {
    SUCCEED();
}

} // namespace

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    ::testing::UnitTest::GetInstance()->listeners().Append(
        new ProgramIterationListener("program_iteration_log.txt"));

    return RUN_ALL_TESTS();
}
