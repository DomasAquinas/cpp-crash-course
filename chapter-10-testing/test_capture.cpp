// Test_capture

#include <functional>
#include <iostream>

int main() {
    int num {};
    std::function test_func = [&num]() {num ++;};
    std::cout << num;
}
