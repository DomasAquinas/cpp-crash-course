// Service bus mock class

#include "AutoBrakePods.h"
#include "IServiceBus.h"


class MockServicebus : IServiceBus {
    void publish(const BrakeCommand&) override {
        commands_published++;
    }
    void subscribe(SpeedUpdateCallback callback) override {
        speed_update_callback = callback;
    }
    void subscribe(CarDetectedCallback callback) override {
        car_detected_callback = callback;
    }
    BrakeCommand last_command{};
    int commands_published{};
    SpeedUpdateCallback speed_update_callback{};
    CarDetectedCallback car_detected_callback{};
};
