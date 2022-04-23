// Exercises 4-1 through 4-6 ...ish

#include <cstdio>
#include <ctime>


struct TimerClass {
    time_t timestamp;
    
    TimerClass() {
        timestamp = time(nullptr);
    }

    ~TimerClass() {
        time_t destruction_time = time(nullptr);
        double lifetime = difftime(destruction_time, timestamp);
        printf("This timer object lasted %.f seconds.\n", lifetime);
    }

    TimerClass(const TimerClass& original) {
        this->timestamp = original.timestamp;
    }

    TimerClass& operator=(const TimerClass& original) {
        if (this == &original) return *this;
        this->timestamp = original.timestamp;
        return *this;
    }

    TimerClass(TimerClass&& original) noexcept {
        this->timestamp = original.timestamp;
        original.timestamp = 0;
    }

    TimerClass& operator=(TimerClass&& original) noexcept {
        if (this == &original) return *this;
        this->timestamp = original.timestamp;
        original.timestamp = 0;
        return *this;
    }
};

int main() {
    TimerClass timer;
    int fun_num{0};
    for (int i = 1; i < 15000000; i++) {
        fun_num += i;
    };
    TimerClass timer_copy{timer};
    for (int i = 1; i < 30000000; i++) {
        fun_num += i;
    };
    TimerClass timer_ac;
    timer_ac = timer;
    for (int i = 1; i < 30000; i++) {
        fun_num += i;
    };
}