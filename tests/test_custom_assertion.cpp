#include "gtest/gtest.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace {

struct Address {
    std::string city;
    std::string zip_code;
};

struct UserProfile {
    int id;
    std::string name;
    int age;
    bool active;
    Address address;
    std::vector<std::string> roles;
};

std::string FormatRoles(const std::vector<std::string>& roles) {
    std::ostringstream stream;
    stream << "[";
    for (std::size_t i = 0; i < roles.size(); ++i) {
        if (i > 0) {
            stream << ", ";
        }
        stream << roles[i];
    }
    stream << "]";
    return stream.str();
}

::testing::AssertionResult UserProfileMatches(
    const UserProfile& actual,
    const UserProfile& expected) {
    std::ostringstream failures;

    if (actual.id != expected.id) {
        failures << "id: expected " << expected.id << ", actual " << actual.id << "\n";
    }
    if (actual.name != expected.name) {
        failures << "name: expected " << expected.name << ", actual " << actual.name << "\n";
    }
    if (actual.age != expected.age) {
        failures << "age: expected " << expected.age << ", actual " << actual.age << "\n";
    }
    if (actual.active != expected.active) {
        failures << "active: expected " << expected.active << ", actual " << actual.active << "\n";
    }
    if (actual.address.city != expected.address.city) {
        failures << "address.city: expected " << expected.address.city
                 << ", actual " << actual.address.city << "\n";
    }
    if (actual.address.zip_code != expected.address.zip_code) {
        failures << "address.zip_code: expected " << expected.address.zip_code
                 << ", actual " << actual.address.zip_code << "\n";
    }
    if (actual.roles != expected.roles) {
        failures << "roles: expected " << FormatRoles(expected.roles)
                 << ", actual " << FormatRoles(actual.roles) << "\n";
    }

    const std::string message = failures.str();
    if (message.empty()) {
        return ::testing::AssertionSuccess();
    }

    return ::testing::AssertionFailure() << "UserProfile mismatch:\n" << message;
}

bool Contains(const std::string& text, const std::string& expected) {
    return text.find(expected) != std::string::npos;
}

} // namespace

TEST(CustomAssertionTest, VerifiesComplexObjectProperties) {
    const UserProfile actual{
        1001,
        "Alice",
        28,
        true,
        {"Shanghai", "200000"},
        {"admin", "editor"}
    };

    const UserProfile expected{
        1001,
        "Alice",
        28,
        true,
        {"Shanghai", "200000"},
        {"admin", "editor"}
    };

    EXPECT_TRUE(UserProfileMatches(actual, expected));
}

TEST(CustomAssertionTest, ReportsAllMismatchedProperties) {
    const UserProfile actual{
        1002,
        "Bob",
        30,
        false,
        {"Beijing", "100000"},
        {"viewer"}
    };

    const UserProfile expected{
        1001,
        "Alice",
        28,
        true,
        {"Shanghai", "200000"},
        {"admin", "editor"}
    };

    const ::testing::AssertionResult result = UserProfileMatches(actual, expected);
    const std::string message = result.message();

    std::cout << message;

    EXPECT_FALSE(result);
    EXPECT_TRUE(Contains(message, "id: expected 1001, actual 1002"));
    EXPECT_TRUE(Contains(message, "name: expected Alice, actual Bob"));
    EXPECT_TRUE(Contains(message, "age: expected 28, actual 30"));
    EXPECT_TRUE(Contains(message, "address.city: expected Shanghai, actual Beijing"));
    EXPECT_TRUE(Contains(message, "roles: expected [admin, editor], actual [viewer]"));
}

TEST(CustomAssertionTest, DISABLED_ShowsGoogleTestFailureMessage) {
    const UserProfile actual{
        1002,
        "Bob",
        30,
        false,
        {"Beijing", "100000"},
        {"viewer"}
    };

    const UserProfile expected{
        1001,
        "Alice",
        28,
        true,
        {"Shanghai", "200000"},
        {"admin", "editor"}
    };

    EXPECT_TRUE(UserProfileMatches(actual, expected));
}
