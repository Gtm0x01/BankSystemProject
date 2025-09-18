#include "BankAccount.h"
#include <iostream>

BankAccount::BankAccount(int accNo, const std::string& accName, double initialBalance)
    : accountNumber(accNo), name(accName), balance(initialBalance) {
    transactions.emplace_back("Initial Deposit", initialBalance);
}

int BankAccount::getAccountNumber() const { return accountNumber; }
std::string BankAccount::getName() const { return name; }
double BankAccount::getBalance() const { return balance; }

void BankAccount::setName(const std::string& newName) {
    name = newName;
    std::cout << "Name updated.\n";
}

void BankAccount::deposit(double amount) {
    if (amount <= 0) {
        std::cout << "Invalid deposit.\n";
        return;
    }
    balance += amount;
    transactions.emplace_back("Deposit", amount);
    std::cout << "Deposited Rs." << amount << "\n";
}

bool BankAccount::withdraw(double amount) {
    if (amount <= 0 || amount > balance) {
        std::cout << "Invalid/Insufficient funds.\n";
        return false;
    }
    balance -= amount;
    transactions.emplace_back("Withdraw", amount);
    std::cout << "Withdrew Rs." << amount << "\n";
    return true;
}

void BankAccount::displayDetails() const {
    std::cout << "Account Number: " << accountNumber << "\n"
              << "Account Holder: " << name << "\n"
              << "Balance: Rs." << balance << "\n";
}

void BankAccount::displayTransactions() const {
    std::cout << "Transaction History:\n";
    for (const auto& t : transactions)
        std::cout << t.date << " | " << t.type << " | Rs." << t.amount << "\n";
}

void BankAccount::calculateInterest(double rate) {
    double interest = balance * rate / 100;
    balance += interest;
    transactions.emplace_back("Interest", interest);
    std::cout << "Interest added: Rs." << interest << "\n";
}
