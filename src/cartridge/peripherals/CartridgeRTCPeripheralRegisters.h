#ifndef GBTEST_CARTRIDGERTCPERIPHERALREGISTERS_H
#define GBTEST_CARTRIDGERTCPERIPHERALREGISTERS_H

#include <cstdint>

namespace gbtest {

class CartridgeRTCPeripheralRegisters {

public:
    CartridgeRTCPeripheralRegisters();

    void increment();

    void setSeconds(uint8_t seconds);
    [[nodiscard]] uint8_t getSeconds() const;

    void setMinutes(uint8_t minutes);
    [[nodiscard]] uint8_t getMinutes() const;

    void setHours(uint8_t hours);
    [[nodiscard]] uint8_t getHours() const;

    void setDayCounterLow(uint8_t dayCounterLow);
    [[nodiscard]] uint8_t getDayCounterLow() const;

    void setDayCounterHigh(uint8_t dayCounterHigh);
    [[nodiscard]] uint8_t getDayCounterHigh() const;

    void setDayCounter(uint16_t dayCounter);
    [[nodiscard]] uint16_t getDayCounter() const;

    void setHalted(bool halted);
    [[nodiscard]] bool isHalted() const;

    void setDayCounterCarry(bool dayCounterCarry);
    [[nodiscard]] bool getDayCounterCarry() const;

private:
    uint8_t m_seconds;
    uint8_t m_minutes;
    uint8_t m_hours;
    uint16_t m_dayCounter;
    bool m_halted;
    bool m_dayCounterCarry;

}; // class CartridgeRTCPeripheralRegisters

} // namespace gbtest

#endif //GBTEST_CARTRIDGERTCPERIPHERALREGISTERS_H
