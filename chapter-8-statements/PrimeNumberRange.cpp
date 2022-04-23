// PrimeNumberRange class, Exercise 8-2

#include <cstddef>

#include "PrimeNumberRange.h"

bool PrimeNumberIterator::operator!= (int x) const {
    return x>= current;
}

PrimeNumberIterator& PrimeNumberIterator::operator++ () {
    bool isPrime {false};
    while (!isPrime) {
        current++;
        isPrime = true;
        for (int num {2}; num < current; num++) {
            if (current % num == 0) {
                isPrime = false;
            }
        }
    }
    return *this;
}

int PrimeNumberIterator::operator* () const {
    return current;
}

PrimeNumberRange::PrimeNumberRange(int max) : max {max} { };

PrimeNumberIterator PrimeNumberRange::begin() const {
    return PrimeNumberIterator { };
}

int PrimeNumberRange::end() const {
    return max;
}
