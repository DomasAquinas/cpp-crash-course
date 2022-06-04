// AutoBrake class template

template <typename T>
struct AutoBrake {
    AutoBrake(const T& Publish) : publish{ publish } { };
    void observe(const SpeedUpdate& su) { };
    void observe(const CarDetected& cd) { };
    void set_collision_threshold_s(double x) {
        collision_threshold_s = x;
    }
    double get_collision_threshold_s() const {
        return collision_threshold_s;
    }
    double get_speed_mps() const {
        return speed_mps;
    }
private:
    double collision_threshold_s;
    double speed_mps;
    const T& publish;
};
