// LengthHistogram, Exercise 9-2

#include <cstddef>
#include <cstdio>

#include "LengthHistogram.h"

void LengthHistogram::ingest(const char* x) {
    size_t index {};
    while(const auto c = x[index]) {
        index++;
    }
    if (index < 50) counts[index-1]++;
}

void LengthHistogram::print() const {
    for (auto index{0}; index < 50; index++) {
        printf("%d: ", index+1);
        auto n_asterisks = counts[index];
        while (n_asterisks--) printf("*");
        printf("\n");
    }
}