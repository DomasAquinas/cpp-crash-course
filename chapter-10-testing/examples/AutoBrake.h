// AutoBrake class template

struct SpeedUpdate;
struct CarDetected;

template <typename T>
struct AutoBrake {
    AutoBrake(const T& Publish)
        : collision_threshold_s { 5 },
          speed_mps{},
          publish{ publish } { };
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
