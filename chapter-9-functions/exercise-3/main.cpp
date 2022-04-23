// main, Exercise 9-3

#include <cstddef>
#include <cstdio>

#include "all.h"

int main() {
    int data[]{1000, 200, 300, 400, 500};
    size_t data_len = 5;
    auto all_gt100 = all([](auto x){return x > 100;}, data, data_len);
    if(all_gt100) printf("All elements greater than 100.\n");
}
