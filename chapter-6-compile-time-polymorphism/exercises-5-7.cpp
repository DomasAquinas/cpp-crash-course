// Exercises 6-7 through 6-7 for C++ Crash Course

#include <cstdio>

template<typename T>
struct Logger {
    virtual ~Logger() = default;
    virtual void log_transfer(T& from, T& to, double amount) = 0;
};

template<typename T>
struct ConsoleLogger : Logger<T> {
    ConsoleLogger(const char* prepend_string)
        : prepend_string{ prepend_string }
    { }
    void log_transfer(T& from, T& to, double amount) override {
        printf("[cons] %s %s -> %s: %f\n", prepend_string, from.get_id(), to.get_id(), amount);
    }
private:
    const char* prepend_string { };
};

template<typename T>
struct FileLogger : Logger<T> {
    void log_transfer(T& from, T& to, double amount) override {
        printf("[file] %s -> %s: %f\n", from.get_id(), to.get_id(), amount);
    }
};

template<typename T>
struct AccountDatabase {
    virtual ~AccountDatabase() = default;
    virtual double get_balance(T& account) = 0;
    virtual void deposit_funds(T& account, double amount) = 0;
    virtual void withdraw_funds(T& account, double amount) = 0;
    virtual void transfer_funds(T& from, T& to, double amount) = 0;
};

template<typename T>
struct InMemoryAccountDatabase : AccountDatabase<T> {
    double get_balance(T& account) override {
        return account.get_balance();
    }
    void deposit_funds(T& account, double amount) override {
        account.deposit_funds(amount);
    }
    void withdraw_funds(T& account, double amount) override {
        account.withdraw_funds(amount);
    } 
    void transfer_funds(T& from, T& to, double amount) override {
        from.withdraw_funds(amount);
        to.deposit_funds(amount);
    }
};

// 6-6: Implement an account class with functions to keep track of balances
// 6-7: Refactor Account into an interface 
struct Account {
    ~Account() = default;
    virtual double get_balance() = 0;
    virtual void deposit_funds(double amount) = 0;
    virtual void withdraw_funds(double amount) = 0;
    virtual char* get_id() = 0;
};

// 6-7 Implement the Account interface in CheckingAccount and SavingsAccount
struct CheckingAccount : Account {
    CheckingAccount(const double balance, char* id)
        : balance{ balance }, id{ id } 
    { };
    double get_balance() override {
        return balance;
    }
    void deposit_funds(const double amount) override {
        balance += amount;
    }
    void withdraw_funds(const double amount) override {
        balance -= amount;
    }
    char* get_id() {
        return id;
    }
private:
    double balance { 0.00 };
    char*  id      { "Checking" };
};

struct SavingsAccount : Account {
    SavingsAccount(const double balance, char* id)
        : balance{ balance }, id{ id } 
    { };
    double get_balance() override {
        return balance;
    }
    void deposit_funds(const double amount) override {
        balance += amount;
    }
    void withdraw_funds(const double amount) override {
        balance -= amount;
    }
    char* get_id() {
        return id;
    }
private:
    double balance { 0.00 };
    char*  id      { "Savings" };
};

// 6-5: Convert Bank to a template class that accepts a parameter for Account
template<typename T>
struct Bank {
    Bank(Logger<T>* logger, AccountDatabase<T>* account_database)
        : logger{ logger }
        , account_database{ account_database }
    { }
    void set_logger(Logger<T>* new_logger) {
        logger = new_logger;
    }
    void make_transfer(T& from, T& to, double amount) {
        account_database->transfer_funds(from, to, amount);
        if (logger) logger->log_transfer(from, to, amount);
    }
    void report_balance(T& account) {
        printf(
            "Account %s balance is %f\n",
            account.get_id(), account_database->get_balance(account)
        );
    }
    void deposit_funds(T& account, double amount) {
        account_database->deposit_funds(account, amount);
    }
    void withdraw_funds(T& account, double amount) {
        account_database->withdraw_funds(account, amount);
    }
private:
    Logger<T>* logger;
    AccountDatabase<T>* account_database;
};

int main() {
    ConsoleLogger<Account> console_logger { "Output:" };
    FileLogger<Account> file_logger;
    InMemoryAccountDatabase<Account> in_memory_account_database;
    CheckingAccount account_a { 500.00, "Checking" };
    SavingsAccount account_b { 400.00, "Savings" };
    Bank<Account> bank{ &console_logger, &in_memory_account_database };
    bank.set_logger(&console_logger);
    bank.make_transfer(account_a, account_b, 49.95);
    bank.set_logger(&file_logger);
    bank.make_transfer(account_b, account_a, 20.00);
    bank.deposit_funds(account_a, 1000.00);
    bank.report_balance(account_a);
}
