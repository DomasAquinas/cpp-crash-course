// AutoBrake class template

template <typename T>
struct AutoBrake {
    AutoBrake(const T& Publish);
    void observe(const SpeedUpdate&);
    void observe(const CarDetected&);
private:
    const T& publish;
};
