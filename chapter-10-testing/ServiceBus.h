// Service bus for the AutoBrake examples
#pragma once

struct BrakeCommand;

class ServiceBus {
public:
    void publish(const BrakeCommand&);

    // ...
};
