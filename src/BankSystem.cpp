#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include <vector>
#include "BankAccount.h"

class BankSystem {
    std::vector<BankAccount> accounts;

public:
    void addAccount(int accNo, const std::string& name, double initialDeposit);
    BankAccount* findAccount(int accNo);
    void showAllAccounts() const;
    bool deleteAccount(int accNo);
};

#endif
