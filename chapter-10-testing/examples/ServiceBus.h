// Service bus for the AutoBrake examples

struct BrakeCommand;

class ServiceBus {
public:
    void publish(const BrakeCommand&);

    // ...
};
