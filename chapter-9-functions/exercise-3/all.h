// all function template, Exercise 9-3

#include <cstddef>
#include <cstdio>

template <typename Fn, typename In>
constexpr bool all(Fn function, In* input, size_t length) {
    bool result {true};
    for (size_t i {}; i<length; i++) {
        result &= function(input[i]);
    }
    return result;
}