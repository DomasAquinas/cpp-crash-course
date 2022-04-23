// main.cpp, Exercise 9-2

#include <cstdio>

#include "LengthHistogram.h"

int main(int argc, char* argv[]) {
    LengthHistogram len;
    for (size_t i {1}; i<argc; i++) {
        len.ingest(argv[i]);
    }
    len.print();
}
