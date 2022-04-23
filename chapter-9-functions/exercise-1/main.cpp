// main.cpp, Exercise 9-1

#include <algorithm>
#include <cstdio>

#include "fold.h"

using namespace std;

int main() {
    int data[]{100, 200, 300, 400, 500};
    size_t data_len = 5;
    auto sum = fold([](auto x, auto y){return x + y;}, data, data_len, 0);
    printf("Sum: %d\n", sum);

    auto maximum = fold([](auto x, auto y){return max(x, y);}, data, data_len, 0);
    printf("Max: %d\n", maximum);

    auto minimum = fold([](auto x, auto y){return min(x, y);}, data, data_len, 0);
    printf("Min: %d\n", minimum);

    auto n_over_200 = fold([](auto x, auto y){return (y > 200)? ++x : x;}, data, data_len, 0);
    printf("Number over 200: %d\n", n_over_200);
}
