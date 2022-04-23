// Exercise 3-2

#include <cstdio>

// Exercise functions

char read_from(char* word, size_t n_chars, int index) {
    if ((index < 0) || (index >= n_chars-1)) {
        printf("Who knows what's out there!!");
        return '!';  // '!' means you did it wrong!
    } else {
        return word[index];
    }
}

void write_to(char* word, size_t n_chars, int index, char insert) {
    if ((index < 0) || (index >= n_chars-1)) {
        printf("Are you crazy!?");
    } else {
        word[index] = insert;
    }
}

int main() {
    char lower[] = "abc?e";
    char upper[] = "ABC?E";
    char read_test = 'c';//read_from(upper, sizeof(upper), 0);

    write_to(lower, sizeof(lower), 5, 'd');
    write_to(upper, sizeof(lower), 3, read_from(lower, sizeof(lower), 6));

    printf("lower: %s\nupper: %s\n", lower, upper);
}
