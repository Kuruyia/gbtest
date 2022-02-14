#include "Timer.h"

gbtest::Timer::Timer(gbtest::Bus& bus)
        : m_tickCounter(0)
        , m_hasOverflown(false)
        , m_bus(bus)
        , m_timerCounter()
        , m_timerModulo()
        , m_timerControl()
{

}

gbtest::TimerCounter& gbtest::Timer::getTimerCounterRegister()
{
    return m_timerCounter;
}

const gbtest::TimerCounter& gbtest::Timer::getTimerCounterRegister() const
{
    return m_timerCounter;
}

gbtest::TimerModulo& gbtest::Timer::getTimerModuloRegister()
{
    return m_timerModulo;
}

const gbtest::TimerModulo& gbtest::Timer::getTimerModuloRegister() const
{
    return m_timerModulo;
}

gbtest::TimerControl& gbtest::Timer::getTimerControlRegister()
{
    return m_timerControl;
}

const gbtest::TimerControl& gbtest::Timer::getTimerControlRegister() const
{
    return m_timerControl;
}

bool gbtest::Timer::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // Check if it's one of our registers
    switch (addr) {
    case 0xFF05: // [TIMA] Timer counter
        val = m_timerCounter.raw;
        return true;

    case 0xFF06: // [TMA] Timer modulo
        val = m_timerModulo.raw;
        return true;

    case 0xFF07: // [TAC] Timer Control
        val = m_timerControl.raw;
        return true;

    default:
        break;
    }

    return false;
}

bool gbtest::Timer::busWrite(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // Check if it's one of our registers
    switch (addr) {
    case 0xFF05: // [TIMA] Timer counter
        m_timerCounter.raw = val;
        return true;

    case 0xFF06: // [TMA] Timer modulo
        m_timerModulo.raw = val;
        return true;

    case 0xFF07: // [TAC] Timer Control
        m_timerControl.raw = val;
        return true;

    default:
        break;
    }

    return false;
}

bool gbtest::Timer::busReadOverride(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // Timer never overrides read requests
    return false;
}

bool gbtest::Timer::busWriteOverride(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // Timer never overrides write requests
    return false;
}

void gbtest::Timer::tick()
{
    // Disable the interrupt line
    m_bus.setInterruptLineHigh(InterruptType::Timer, false);

    // Don't do anything if the timer is disabled
    if (!m_timerControl.timerEnable) {
        return;
    }

    // Check if the timer overflown during the last tick
    if (m_hasOverflown) {
        m_hasOverflown = false;

        m_timerCounter.raw = m_timerModulo.raw;
        m_bus.setInterruptLineHigh(InterruptType::Timer, true);
    }

    // Increase the tick counter
    ++m_tickCounter;

    // Check if we have to increase the TIMA register
    if (m_tickCounter >= getTimerInvFrequency()) {
        ++m_timerCounter.raw;
        m_tickCounter = 0;

        // Check if the timer counter has overflown
        if (m_timerCounter.raw == 0x00) {
            m_hasOverflown = true;
        }
    }
}

unsigned gbtest::Timer::getTimerInvFrequency() const
{
    switch (m_timerControl.inputClockSelect) {
    case 0:
        return 1024;
    case 1:
        return 16;
    case 2:
        return 64;
    default:
        return 256;
    }
}
