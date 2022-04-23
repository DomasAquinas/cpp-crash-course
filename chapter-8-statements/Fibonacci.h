// Fibonnaci Generation classes, Exercise 8-1

class FibonacciIterator {
public:

    bool operator!= (int x) const;

    FibonacciIterator& operator++ ();

    int operator* () const;

private:
    int current {1}, last {1};
};


class FibonacciRange {
public:

    explicit FibonacciRange(int max);

    FibonacciIterator begin() const;

    int end() const;

private:
    const int max;
};
