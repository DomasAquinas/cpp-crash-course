// AutoBrake class template
#pragma once

#include <iostream>
#include <stdexcept>

#include "AutoBrakePods.h"
#include "IServiceBus.h"


struct AutoBrake {
    AutoBrake(IServiceBus& bus)
        : collision_threshold_s{ 5 },
          speed_mps{} { };
    void set_collision_threshold_s(double x) {
        if (x < 1) throw std::runtime_error{ "Collision less than 1." };
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
};
