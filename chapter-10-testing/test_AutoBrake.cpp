// Autobrake unit tests

#include <cstdio>
#include <iostream>
#include <stdexcept>

#include "AutoBrake.h"
#include "MockServiceBus.h"

// Assertion function
constexpr void assert_that(bool statement, const char* message) {
    if (!statement) throw std::runtime_error{ message };
}

// Tests

void initial_speed_is_zero() {
    MockServicebus bus{};
    AutoBrake auto_brake{ bus };
    assert_that(auto_brake.get_speed_mps() == 0L, "speed not equal 0");
}

void initial_sensitivity_is_five() {
    MockServicebus bus{};
    AutoBrake auto_brake{ bus };
    assert_that(auto_brake.get_collision_threshold_s() == 5L,
                "sensitivity is not 5");
}

void sensitivity_greater_than_1() {
    MockServicebus bus{};
    AutoBrake auto_brake{ bus };
    try {
        auto_brake.set_collision_threshold_s(0.5L);
    } catch(const std::exception&) {
        return;
    }
    assert_that(false, "no exception thrown");
}

void speed_is_saved() {
    MockServicebus bus{};
    AutoBrake auto_brake{ bus };

    bus.speed_update_callback(SpeedUpdate{ 100L });
    assert_that(100L == auto_brake.get_speed_mps(), "speed not saved to 100");
    bus.speed_update_callback(SpeedUpdate{ 50L });
    assert_that(50L == auto_brake.get_speed_mps(), "speed not saved to 50");
    bus.speed_update_callback(SpeedUpdate{ 0L });
    assert_that(0L == auto_brake.get_speed_mps(), "speed not saved to 0");
}

void alert_when_imminent() {
    MockServicebus bus{};
    AutoBrake auto_brake{ bus };
    auto_brake.set_collision_threshold_s(10L);
    bus.speed_limit_callback(SpeedLimitDetected{ 200L });
    bus.speed_update_callback(SpeedUpdate{ 100L });
    bus.car_detected_callback(CarDetected{ 100L, 0L});
    assert_that(bus.commands_published == 1,
                "brake commands published not one");
}

void no_alert_when_not_imminent() {
    MockServicebus bus{};
    AutoBrake auto_brake{ bus };
    auto_brake.set_collision_threshold_s(2L);
    bus.speed_limit_callback(SpeedLimitDetected{ 200L });
    bus.speed_update_callback(SpeedUpdate{ 100L });
    bus.car_detected_callback(CarDetected{ 1000L, 50L });
    assert_that(bus.commands_published == 0, "brake command published");
}

// Exercise 10-3
void initial_speed_limit_is_39() {
    MockServicebus bus{};
    AutoBrake auto_brake{ bus };
    assert_that(auto_brake.get_last_speed_limit() == 39L,
                "initial speed limit not 39");
}

// Exercise 10-5
void speed_limit_is_saved() {
    MockServicebus bus{};
    AutoBrake auto_brake{ bus };
    bus.speed_limit_callback(SpeedLimitDetected{ 15L });
    assert_that(auto_brake.get_last_speed_limit() == 15L,
                "speed limit not saved to 15");
    bus.speed_limit_callback(SpeedLimitDetected{ 45L });
    assert_that(auto_brake.get_last_speed_limit() == 45L,
                "speed limit not saved to 45");
    bus.speed_limit_callback(SpeedLimitDetected{ 70L });
    assert_that(auto_brake.get_last_speed_limit() == 70L,
                "speed limit not saved to 70");
}

// Exercise 10-7
void no_alert_when_under_limit() {
    MockServicebus bus{};
    AutoBrake auto_brake{ bus };
    bus.speed_limit_callback(SpeedLimitDetected{ 35L });
    bus.speed_update_callback(SpeedUpdate{ 34L });
    assert_that(bus.commands_published == 0, "brake command published");
}

// Exercise 10-9
void alert_when_over_limit() {
    MockServicebus bus{};
    AutoBrake auto_brake{ bus };
    bus.speed_limit_callback(SpeedLimitDetected{ 35L });
    bus.speed_update_callback(SpeedUpdate{ 40L });
    assert_that(bus.commands_published == 1,
                "brake commands published not one");
    assert_that(bus.last_command.time_to_collision_s == 0,
                "time to collision not 0");
}

void alert_when_limit_drops_below_speed() {
    MockServicebus bus{};
    AutoBrake auto_brake{ bus };
    bus.speed_limit_callback(SpeedLimitDetected{ 35L });
    bus.speed_update_callback(SpeedUpdate{ 30L });
    bus.speed_limit_callback(SpeedLimitDetected{ 25L });
    assert_that(bus.commands_published == 1,
                "brake commands published not one");
    assert_that(bus.last_command.time_to_collision_s == 0,
                "time to collision not 0");
}

// Test harness
void run_test(void(*unit_test)(), const char* name) {
    try {
        unit_test();
        printf("[+] Test %s successful.\n", name);
    } catch(const std::exception& e) {
        printf("[-] Test failure in %s. %s.\n", name, e.what());
    }
}

int main() {
    run_test(initial_speed_is_zero, "initial speed is 0");
    run_test(initial_sensitivity_is_five, "initial sensitivity is 5");
    run_test(sensitivity_greater_than_1, "sensitivity greater than 1");
    run_test(speed_is_saved, "speed is saved");
    run_test(alert_when_imminent, "alert when imminent");
    run_test(no_alert_when_not_imminent, "no alert when not imminent");
    run_test(initial_speed_limit_is_39, "initial speed limit is 39");
    run_test(speed_limit_is_saved, "speed limit is saved");
    run_test(no_alert_when_under_limit, "no alert when under limit");
    run_test(alert_when_over_limit, "alert when over limit");
    run_test(alert_when_limit_drops_below_speed,
             "alert when limit drops below speed");
}
