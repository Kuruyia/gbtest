#ifndef GBTEST_TIMERREGISTERS_H
#define GBTEST_TIMERREGISTERS_H

#include <cstdint>

namespace gbtest {

// [TIMA] Timer counter
struct TimerCounter {
    uint8_t raw;
}; // struct TimerCounter

static_assert(sizeof(TimerCounter) == 1, "Timer counter structure size is incorrect");

// [TMA] Timer modulo
struct TimerModulo {
    uint8_t raw;
}; // struct TimerModulo

static_assert(sizeof(TimerModulo) == 1, "Timer modulo structure size is incorrect");

// [TAC] Timer Control
union TimerControl {
    struct {
        uint8_t inputClockSelect: 2;    // Timer clock frequency selection
        // 00b:   4096 Hz on single speed;   8192 Hz on double speed
        // 01b: 262144 Hz on single speed; 524288 Hz on double speed
        // 10b:  65536 Hz on single speed; 131072 Hz on double speed
        // 11b:  16384 Hz on single speed;  32768 Hz on double speed
        uint8_t timerEnable: 1;         // Enable/disable the timer
        uint8_t unused: 5;
    };
    uint8_t raw;
}; // union TimerControl

static_assert(sizeof(TimerControl) == 1, "Timer control structure size is incorrect");

}

#endif //GBTEST_TIMERREGISTERS_H
