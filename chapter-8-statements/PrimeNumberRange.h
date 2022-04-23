// PrimeNumberRange class, exercise 8-2

class PrimeNumberIterator {
public:

    bool operator != (int x) const;

    PrimeNumberIterator& operator++ ();

    int operator* () const;

private:
    int current {1};
};


class PrimeNumberRange {
public:

    explicit PrimeNumberRange(int max);

    PrimeNumberIterator begin() const;

    int end() const;

private:
    const int max;
};
