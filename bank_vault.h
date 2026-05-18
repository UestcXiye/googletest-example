#pragma once

#include <string>

class BankVault {
private:
    double secret_balance;
    std::string password;
    
    bool ValidatePassword(const std::string& pwd) {
        return pwd == password;
    }
    
    // 允许特定测试访问私有成员
    FRIEND_TEST(BankVaultTest, AccessPrivateMembers);
    FRIEND_TEST(BankVaultTest, TestPasswordValidation);
    
public:
    BankVault() : secret_balance(1000000), password("secret123") {}
    
    bool Withdraw(double amount, const std::string& pwd) {
        if (ValidatePassword(pwd) && amount <= secret_balance) {
            secret_balance -= amount;
            return true;
        }
        return false;
    }
};