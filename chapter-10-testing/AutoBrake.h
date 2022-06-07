// AutoBrake class template
#pragma once

#include <iostream>
#include <stdexcept>

#include "AutoBrakePods.h"
#include "IServiceBus.h"


struct AutoBrake {
    AutoBrake(IServiceBus& bus)
        : collision_threshold_s{ 5 },
          speed_mps{},
          last_speed_limit{ 39 } {
        bus.subscribe([this](const SpeedUpdate& update) {
            speed_mps = update.velocity_mps;
        });
        bus.subscribe([this, &bus](const CarDetected& cd) {
            const auto relative_velocity_mps = speed_mps - cd.velocity_mps;
            const auto time_to_collision_s = cd.distance_m /
                relative_velocity_mps;
            if (time_to_collision_s > 0 &&
                time_to_collision_s <= collision_threshold_s) {
                bus.publish(BrakeCommand{ time_to_collision_s });
            }
        });
    }
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
    double get_last_speed_limit() const {
        return last_speed_limit;
    }
private:
    double collision_threshold_s;
    double speed_mps;
    double last_speed_limit;
};
