#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include <vector>
#include "Transaction.h"

class BankAccount {
    int accountNumber;
    std::string name;
    double balance;
    std::vector<Transaction> transactions;

public:
    BankAccount(int accNo, const std::string& accName, double initialBalance);

    int getAccountNumber() const;
    std::string getName() const;
    double getBalance() const;

    void setName(const std::string& newName);

    void deposit(double amount);
    bool withdraw(double amount);
    void displayDetails() const;
    void displayTransactions() const;
    void calculateInterest(double rate);
};

#endif
