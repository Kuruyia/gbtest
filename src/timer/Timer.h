#ifndef GBTEST_TIMER_H
#define GBTEST_TIMER_H

#include <cstdint>

#include "TimerRegisters.h"

#include "../platform/bus/BusProvider.h"
#include "../platform/bus/Bus.h"
#include "../utils/Tickable.h"

namespace gbtest {

class Timer
        : public BusProvider, public Tickable {

public:
    explicit Timer(Bus& bus);
    ~Timer() override = default;

    TimerCounter& getTimerCounterRegister();
    [[nodiscard]] const TimerCounter& getTimerCounterRegister() const;

    TimerModulo& getTimerModuloRegister();
    [[nodiscard]] const TimerModulo& getTimerModuloRegister() const;

    TimerControl& getTimerControlRegister();
    [[nodiscard]] const TimerControl& getTimerControlRegister() const;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    void tick() override;

private:
    [[nodiscard]] unsigned getTimerInvFrequency() const;

    unsigned m_tickCounter;
    bool m_hasOverflown;

    Bus& m_bus;

    TimerCounter m_timerCounter;
    TimerModulo m_timerModulo;
    TimerControl m_timerControl;

}; // class Timer

} // namespace gbtest

#endif //GBTEST_TIMER_H
