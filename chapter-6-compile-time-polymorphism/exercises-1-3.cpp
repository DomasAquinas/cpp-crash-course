// Exercises 1-3 for C++ Crash Course Chapter 6

#include <concepts>
#include <cstdio>
#include <type_traits>

// 6-1: Implement the mode function
// int mode(const int* values, size_t length) {
//     if (length == 0) {
//         return 0;
//     }
//     int current_value { };
//     int max_count { 0 };
//     int mode { };
//     for (size_t val_idx = 0; val_idx < length; val_idx++) {
//         current_value = val_idx;
//         int current_count { 0 };
//         for (size_t count_idx = 0; count_idx < length; count_idx++) {
//             if (values[count_idx] == current_value) {
//                 current_count++;
//             }
//         }
//         if (current_count > max_count) {
//             mode = current_value;
//             max_count = current_count;
//         } else if (current_count == max_count) {
//             mode = 0;
//         }
//     }
//     return mode;
// }

// 6-3: Add an Integer concept to the mode template function
template<typename T>
concept Integer =  std::is_integral<T>::value;

// 6-2: Implement mode as a template function
template <Integer T>  T mode(const T* values, size_t length) {
    if (length == 0) {
        return 0;
    }
    T current_value { };
    int current_count { 0 };
    int max_count { 0 };
    T mode { };
    for (size_t val_idx = 0; val_idx < length; val_idx++) {
        current_value = val_idx;
        current_count = 0;
        for (size_t count_idx = 0; count_idx < length; count_idx++) {
            if (values[count_idx] == current_value) {
                current_count++;
            }
        }
        if (current_count > max_count) {
            mode = current_value;
            max_count = current_count;
        } else if (current_count == max_count) {
            mode = 0;
        }
    }
    return mode;
}

int main() {
    int test_vals[10] = {1, 2, 2, 3, 3, 3, 4, 5, 6, 6};
    printf("The mode of the set is %d\n", mode(test_vals, 10));
}
