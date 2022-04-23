// Exercises for C++ Crash Course, Chapter 5

#include <cstdio>

struct Logger {
    virtual ~Logger() = default;
    virtual void log_transfer(long from, long to, double amount) = 0;
};

struct ConsoleLogger : Logger {
    // Exercise 5-4: Add a const char* to construction, prepend it to output
    ConsoleLogger(const char* prepend_string)
        : prepend_string{ prepend_string }
    { }
    void log_transfer(long from, long to, double amount) override {
        printf("[cons] %s %ld -> %ld: %f\n", prepend_string, from, to, amount);
    }
private:
    const char* prepend_string { };
};

struct FileLogger : Logger {
    void log_transfer(long from, long to, double amount) override {
        printf("[file] %ld -> %ld: %f\n", from, to, amount);
    }
};

// Exercise 5-1: Define the AccountDatabase interface
struct AccountDatabase {
    virtual ~AccountDatabase() = default;
    virtual double get_amount(long account_id) = 0;
    virtual void set_amount(long account_id, double amount) = 0;
};

// Exercise 5-2: Implement the interface in the InMemoryAccountDatabase
struct InMemoryAccountDatabase : AccountDatabase {
    double get_amount(long account_id) override {
        // look up the account and get the amount...
        return amount;
    }
    void set_amount(long account_id, double amount) override {
        // pretend to look up the account...
        this->amount = amount;
    }
private:
    double amount { 0.00 };
};

// Exercise 5-3: Use constructor injection to add InMemoryAccountDatabase
struct Bank {
    Bank(Logger* logger, AccountDatabase* account_database)
        : logger{ logger }
        , account_database{ account_database }
    { }
    void set_logger(Logger* new_logger) {
        logger = new_logger;
    }
    void make_transfer(long from, long to, double amount) {
        // Process the transaction
        if (logger) logger->log_transfer(from, to, amount);
    }
    void report_amount(long account_id) {
        printf(
            "Account %ld balance is %f\n",
            account_id, account_database->get_amount(account_id)
        );
    }
    void set_amount(long account_id, double amount) {
        account_database->set_amount(account_id, amount);
    }
private:
    Logger* logger;
    AccountDatabase* account_database;
};

int main() {
    ConsoleLogger console_logger { "Output:" };
    FileLogger file_logger;
    InMemoryAccountDatabase in_memory_account_database;
    Bank bank{ &console_logger, &in_memory_account_database };
    bank.set_logger(&console_logger);
    bank.make_transfer(1000, 2000, 49.95);
    bank.set_logger(&file_logger);
    bank.make_transfer(2000, 4000, 20.00);
    bank.set_amount(1234, 1000.00);
    bank.report_amount(1234);
}
