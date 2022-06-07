// Service bus mock class
#pragma once

#include "AutoBrakePods.h"
#include "IServiceBus.h"


class MockServicebus : public IServiceBus {
public:
    void publish(const BrakeCommand&) override {
        commands_published++;
    }
    void subscribe(SpeedUpdateCallback callback) override {
        speed_update_callback = callback;
    }
    void subscribe(CarDetectedCallback callback) override {
        car_detected_callback = callback;
    }
    void subscribe(SpeedLimitCallback callback) override {
        speed_limit_callback = callback;
    }
    BrakeCommand last_command{};
    int commands_published{};
    SpeedUpdateCallback speed_update_callback{};
    CarDetectedCallback car_detected_callback{};
    SpeedLimitCallback speed_limit_callback{};
};
