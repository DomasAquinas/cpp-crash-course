// Exercise 6-4 for C++ Crash Course

#include <cstdio>

// 6-4: Refactor mean to accept an array

// template<typename T>
// T mean(const T* values, size_t length) {
//     T result { };
//     for (size_t i { }; i < length; i++) {
//         result += values[];
//     }
//     return result / length;
// }

template<typename T, size_t length>
T mean(const T (&values)[length]) {
    T result { };
    for (const T& value : values) {
        result += value;
    }
    return result / length;
}

int main() {
    int mean_value = mean({1,2,3,4,5});
    printf("The mean of the array is %d\n", mean_value);
}
