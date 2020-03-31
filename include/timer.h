#ifndef TIMER_H
#define TIMER_H

#include <chrono>
using std::chrono::time_point;
using std::chrono::steady_clock;
class Timer{
private:
    time_point<steady_clock> prev_time_point;
    time_point<steady_clock> current_time_point;
    double elapsed;
public:
    Timer();
    double restart();
};

#endif
