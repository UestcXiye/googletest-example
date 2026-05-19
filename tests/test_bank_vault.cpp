#include "gtest/gtest.h"
#include "bank_vault.h"

TEST(BankVaultTest, AccessPrivateMembers) {
    BankVault vault;
    // 可以直接访问私有成员
    EXPECT_EQ(vault.secret_balance, 1000000);
    EXPECT_EQ(vault.password, "secret123");
}

TEST(BankVaultTest, TestPasswordValidation) {
    BankVault vault;
    // 可以调用私有方法
    EXPECT_TRUE(vault.ValidatePassword("secret123"));
    EXPECT_FALSE(vault.ValidatePassword("wrong"));
}

TEST(BankVaultTest, DISABLED_TestWithdraw)
{
    BankVault vault;
    EXPECT_TRUE(vault.Withdraw(100, "secret123"));
    EXPECT_FALSE(vault.Withdraw(2000000, "secret123"));
    EXPECT_FALSE(vault.Withdraw(0, "wrong"));
}