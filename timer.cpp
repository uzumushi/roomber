//
// Created by ubntu on 17/10/25.
//

#include "timer.h"
#include "constants.h"

TIMER::TIMER() {
    max_time = MAX_TIME;
}

int TIMER::startTimer() {
    start_time = std::chrono::system_clock::now();
}

int TIMER::getLeftTime() {

    double elapsed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - start_time).count();

    int left_time = max_time - elapsed;

    return left_time;
}