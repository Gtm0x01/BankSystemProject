#include <iostream>
#include <vector>
#include <string>
#include <ctime>

class Transaction {
public:
    std::string date, type;
    double amount;

    Transaction(const std::string& t, double a) : type(t), amount(a) {
        time_t now = time(0);
        date = ctime(&now);
        date.pop_back(); // remove newline
    }
};

class BankAccount {
    int accountNumber;
    std::string name;
    double balance;
    std::vector<Transaction> transactions;

public:
    BankAccount(int accNo, const std::string& accName, double initialBalance)
        : accountNumber(accNo), name(accName), balance(initialBalance) {
        transactions.emplace_back("Initial Deposit", initialBalance);
    }

    int getAccountNumber() const { return accountNumber; }
    std::string getName() const { return name; }
    double getBalance() const { return balance; }

    void setName(const std::string& newName) { name = newName; std::cout << "Name updated.\n"; }

    void deposit(double amount) {
        if (amount <= 0) return void(std::cout << "Invalid deposit.\n");
        balance += amount;
        transactions.emplace_back("Deposit", amount);
        std::cout << "Deposited Rs." << amount << "\n";
    }

    bool withdraw(double amount) {
        if (amount <= 0 || amount > balance) return std::cout << "Invalid/Insufficient funds.\n", false;
        balance -= amount;
        transactions.emplace_back("Withdraw", amount);
        std::cout << "Withdrew Rs." << amount << "\n";
        return true;
    }

    void displayDetails() const {
        std::cout << "Account Number: " << accountNumber << "\n"
                  << "Account Holder: " << name << "\n"
                  << "Balance: Rs." << balance << "\n";
    }

    void displayTransactions() const {
        std::cout << "Transaction History:\n";
        for (const auto& t : transactions)
            std::cout << t.date << " | " << t.type << " | Rs." << t.amount << "\n";
    }

    void calculateInterest(double rate) {
        double interest = balance * rate / 100;
        balance += interest;
        transactions.emplace_back("Interest", interest);
        std::cout << "Interest added: Rs." << interest << "\n";
    }
};

class BankSystem {
    std::vector<BankAccount> accounts;

public:
    void addAccount(int accNo, const std::string& name, double initialDeposit) {
        accounts.emplace_back(accNo, name, initialDeposit);
        std::cout << "Account created.\n";
    }

    BankAccount* findAccount(int accNo) {
        for (auto& acc : accounts) if (acc.getAccountNumber() == accNo) return &acc;
        return nullptr;
    }

    void showAllAccounts() const {
        if (accounts.empty()) return void(std::cout << "No accounts.\n");
        for (const auto& acc : accounts) { acc.displayDetails(); std::cout << "-------------------\n"; }
    }

    bool deleteAccount(int accNo) {
        for (auto it = accounts.begin(); it != accounts.end(); ++it) {
            if (it->getAccountNumber() == accNo) {
                if (it->getBalance() > 0) {
                    std::cout << "Withdraw Rs." << it->getBalance() << " before deleting.\n";
                    return false;
                }
                accounts.erase(it);
                std::cout << "Account deleted.\n";
                return true;
            }
        }
        std::cout << "Account not found.\n";
        return false;
    }
};

int main() {
    BankSystem bank;
    int accNo, choice;
    std::string name;
    double amount;

    auto getAccount = [&](int accNo) {
        auto* acc = bank.findAccount(accNo);
        if (!acc) std::cout << "Account not found.\n";
        return acc;
    };

    do {
        std::cout << "\n1.Open Account\n2.Deposit\n3.Withdraw\n4.Show Details\n5.Show Transactions\n6.Delete Account\n7.Calculate Interest\n8.Update Name\n9.Exit\nChoice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter Account Number: "; std::cin >> accNo;
            std::cout << "Enter Name: "; std::cin.ignore(); std::getline(std::cin, name);
            std::cout << "Enter Initial Deposit: "; std::cin >> amount;
            bank.addAccount(accNo, name, amount); break;

        case 2:
            std::cout << "Enter Account Number: "; std::cin >> accNo;
            if (auto* acc = getAccount(accNo)) { std::cout << "Deposit amount: "; std::cin >> amount; acc->deposit(amount); }
            break;

        case 3:
            std::cout << "Enter Account Number: "; std::cin >> accNo;
            if (auto* acc = getAccount(accNo)) { std::cout << "Withdraw amount: "; std::cin >> amount; acc->withdraw(amount); }
            break;

        case 4:
            std::cout << "Enter Account Number: "; std::cin >> accNo;
            if (auto* acc = getAccount(accNo)) acc->displayDetails();
            break;

        case 5:
            std::cout << "Enter Account Number: "; std::cin >> accNo;
            if (auto* acc = getAccount(accNo)) acc->displayTransactions();
            break;

        case 6:
            std::cout << "Enter Account Number: "; std::cin >> accNo;
            if (auto* acc = getAccount(accNo)) {
                while (acc->getBalance() > 0) {
                    std::cout << "You must withdraw the full balance (Rs." << acc->getBalance() << ") before deleting the account.\n";
                    std::cin >> amount;
                    acc->withdraw(amount);
                }
                bank.deleteAccount(accNo);
            }
            break;

        case 7:
            std::cout << "Enter Account Number: "; std::cin >> accNo;
            if (auto* acc = getAccount(accNo)) { std::cout << "Interest rate (%): "; std::cin >> amount; acc->calculateInterest(amount); }
            break;

        case 8:
            std::cout << "Enter Account Number: "; std::cin >> accNo;
            if (auto* acc = getAccount(accNo)) {
                std::cout << "Current Name: " << acc->getName() << "\nNew Name: ";
                std::cin.ignore(); std::getline(std::cin, name);
                acc->setName(name);
            }
            break;

        case 9: std::cout << "Exiting...\n"; break;
        default: std::cout << "Invalid option.\n";
        }

    } while (choice != 9);

    return 0;
}
