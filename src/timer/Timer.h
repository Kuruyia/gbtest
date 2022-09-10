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

    TimerCounterReg& getTimerCounterRegister();
    [[nodiscard]] const TimerCounterReg& getTimerCounterRegister() const;

    TimerModuloReg& getTimerModuloRegister();
    [[nodiscard]] const TimerModuloReg& getTimerModuloRegister() const;

    TimerControlReg& getTimerControlRegister();
    [[nodiscard]] const TimerControlReg& getTimerControlRegister() const;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    void tick(bool isDoubleSpeedTick) override;

private:
    [[nodiscard]] unsigned getTimerInvFrequency() const;

    unsigned m_tickCounter;
    bool m_hasOverflown;

    Bus& m_bus;

    TimerCounterReg m_timerCounter;
    TimerModuloReg m_timerModulo;
    TimerControlReg m_timerControl;

}; // class Timer

} // namespace gbtest

#endif //GBTEST_TIMER_H
