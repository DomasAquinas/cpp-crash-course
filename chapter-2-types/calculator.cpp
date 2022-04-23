// Exercises for Chapter 2

#include <cstdio>

// Define the operations for the calculator
enum class Operation {
    Add,
    Subtract,
    Multiply,
    Divide
};

// The Calculator itself
struct Calculator {

    Operation operation; // Defaults to public

    Calculator(Operation op) {
        operation = op;
    }

    int calculate(int a, int b) {
        switch (operation) {
            case Operation::Add : {
                return a + b;
            }
            case Operation::Subtract : {
                return a - b;
            }
            case Operation::Multiply : {
                return a * b;
            }
            case Operation::Divide : {
                return a / b;
            }
            default : {
                return -1;
            }
        };
    };
};

int main() {
    Calculator calculator{Operation::Divide};
    int a{5};
    int b{3};
    switch (calculator.operation) {
            case Operation::Add : {
                printf("a + b = %d\n", calculator.calculate(a, b));
                break;
            }
            case Operation::Subtract : {
                printf("a - b = %d\n", calculator.calculate(a, b));
                break;
            }
            case Operation::Multiply : {
                printf("a * b = %d\n", calculator.calculate(a, b));
                break;
            }
            case Operation::Divide : {
                printf("a / b = %d\n", calculator.calculate(a, b));
                break;
            }
        }
}
