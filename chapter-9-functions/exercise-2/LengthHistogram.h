// LengthHistogram, Exercise 9-2

#include <cstddef>

class LengthHistogram {
public:
    void ingest(const char* x);
    void print() const;
private:
    size_t counts[50] {};
};
