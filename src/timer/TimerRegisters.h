#ifndef GBTEST_TIMERREGISTERS_H
#define GBTEST_TIMERREGISTERS_H

#include <cstdint>

namespace gbtest {

// [TIMA] Timer counter
struct TimerCounterReg {
    uint8_t raw;
}; // struct TimerCounterReg

static_assert(sizeof(TimerCounterReg) == 1, "Timer counter register structure size is incorrect");

// [TMA] Timer modulo
struct TimerModuloReg {
    uint8_t raw;
}; // struct TimerModuloReg

static_assert(sizeof(TimerModuloReg) == 1, "Timer modulo register structure size is incorrect");

// [TAC] Timer Control
union TimerControlReg {
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
}; // union TimerControlReg

static_assert(sizeof(TimerControlReg) == 1, "Timer control register structure size is incorrect");

} // namespace gbtest

#endif //GBTEST_TIMERREGISTERS_H
