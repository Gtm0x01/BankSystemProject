#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
public:
    std::string date, type;
    double amount;

    Transaction(const std::string& t, double a);
};

#endif
