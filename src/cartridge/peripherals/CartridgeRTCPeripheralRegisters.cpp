#include "CartridgeRTCPeripheralRegisters.h"

gbtest::CartridgeRTCPeripheralRegisters::CartridgeRTCPeripheralRegisters()
        : m_seconds()
        , m_minutes()
        , m_hours()
        , m_dayCounter()
        , m_halted(false)
        , m_dayCounterCarry(false)
{

}

void gbtest::CartridgeRTCPeripheralRegisters::increment()
{
    // Increment the seconds
    ++m_seconds;

    if (m_seconds != 60) {
        return;
    }

    m_seconds = 0;

    // Increment the minutes
    ++m_minutes;

    if (m_minutes != 60) {
        return;
    }

    m_minutes = 0;

    // Increment the hours
    ++m_hours;

    if (m_hours != 24) {
        return;
    }

    m_hours = 0;

    // Increment the days
    ++m_dayCounter;

    if (m_dayCounter != 512) {
        return;
    }

    m_dayCounter = 0;

    // Set the carry bit
    m_dayCounterCarry = true;
}

void gbtest::CartridgeRTCPeripheralRegisters::setSeconds(uint8_t seconds)
{
    m_seconds = seconds;
}

uint8_t gbtest::CartridgeRTCPeripheralRegisters::getSeconds() const
{
    return (m_seconds & 0x3F);
}

void gbtest::CartridgeRTCPeripheralRegisters::setMinutes(uint8_t minutes)
{
    m_minutes = minutes;
}

uint8_t gbtest::CartridgeRTCPeripheralRegisters::getMinutes() const
{
    return (m_minutes & 0x3F);
}

void gbtest::CartridgeRTCPeripheralRegisters::setHours(uint8_t hours)
{
    m_hours = hours;
}

uint8_t gbtest::CartridgeRTCPeripheralRegisters::getHours() const
{
    return (m_hours & 0x1F);
}

void gbtest::CartridgeRTCPeripheralRegisters::setDayCounterLow(uint8_t dayCounterLow)
{
    m_dayCounter &= 0x100;
    m_dayCounter |= dayCounterLow;
}

uint8_t gbtest::CartridgeRTCPeripheralRegisters::getDayCounterLow() const
{
    return (m_dayCounter & 0xFF);
}

void gbtest::CartridgeRTCPeripheralRegisters::setDayCounterHigh(uint8_t dayCounterHigh)
{
    // Set the MSB of the day counter
    m_dayCounter &= 0xFF;
    m_dayCounter |= ((dayCounterHigh & 0x01) << 8);

    // Set the halted state
    setHalted(dayCounterHigh & 0x40);

    // Set the carry bit
    setDayCounterCarry(dayCounterHigh & 0x80);
}

uint8_t gbtest::CartridgeRTCPeripheralRegisters::getDayCounterHigh() const
{
    // Prepare the high byte
    uint8_t highByte = 0x00;

    // Get the MSB of the day counter
    highByte |= ((m_dayCounter >> 8) & 0x01);

    // Get the halted state
    highByte |= (isHalted() << 6);

    // Get the carry bit
    highByte |= (getDayCounterCarry() << 7);

    return highByte;
}

void gbtest::CartridgeRTCPeripheralRegisters::setDayCounter(uint16_t dayCounter)
{
    m_dayCounter = dayCounter;

    // Check if the day counter has overflown
    if (m_dayCounter >= 512) {
        m_dayCounter %= 512;
        m_dayCounterCarry = true;
    }
}

uint16_t gbtest::CartridgeRTCPeripheralRegisters::getDayCounter() const
{
    return m_dayCounter;
}

void gbtest::CartridgeRTCPeripheralRegisters::setHalted(bool halted)
{
    m_halted = halted;
}

bool gbtest::CartridgeRTCPeripheralRegisters::isHalted() const
{
    return m_halted;
}

void gbtest::CartridgeRTCPeripheralRegisters::setDayCounterCarry(bool dayCounterCarry)
{
    m_dayCounterCarry = dayCounterCarry;
}

bool gbtest::CartridgeRTCPeripheralRegisters::getDayCounterCarry() const
{
    return m_dayCounterCarry;
}
