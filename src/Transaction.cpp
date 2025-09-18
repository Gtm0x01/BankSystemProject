#include "Transaction.h"
#include <ctime>

Transaction::Transaction(const std::string& t, double a) : type(t), amount(a) {
    time_t now = time(0);
    date = ctime(&now);
    date.pop_back();
}
