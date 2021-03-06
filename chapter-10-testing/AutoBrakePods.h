// POD classes for the AutoBrake examples
#pragma once

struct SpeedUpdate {
    double velocity_mps;
};

struct CarDetected {
    double distance_m;
    double velocity_mps;
};

struct BrakeCommand {
    double time_to_collision_s;
};

// Exercise 10-1
struct SpeedLimitDetected {
    unsigned short speed_mps;
};
