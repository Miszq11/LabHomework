#include "../include/timer.h"

using std::chrono::seconds;
Timer::Timer():
prev_time_point(steady_clock::now()),
current_time_point(steady_clock::now())
{}

double Timer::restart(){
    prev_time_point = current_time_point;
    current_time_point = steady_clock::now();
    elapsed = seconds((current_time_point-prev_time_point).count()).count();
    return elapsed;
}
