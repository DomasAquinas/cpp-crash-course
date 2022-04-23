// Main function for chapter 8 exercises

#include <cstdio>

#include "Fibonacci.h"
#include "PrimeNumberRange.h"

int main() {
    for (const auto i : FibonacciRange{5000}) {
        printf("%d ", i);
    }
    // Exercise 8-3
    printf("\n\n");
    for (const auto i : PrimeNumberRange{5000}) {
        printf("%d ", i);
    }
}
