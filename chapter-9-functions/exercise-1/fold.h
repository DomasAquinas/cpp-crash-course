// fold function template, Exercise 9-1

#include <cstddef>

template <typename Fn, typename In, typename Out>
constexpr Out fold(Fn function, In* input, size_t length, Out initial) {
    for (size_t i {}; i < length; i++) {
        initial = function(initial, input[i]);
    }
    return initial;
}
