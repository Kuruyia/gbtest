#include "CGBSpeedSwitchRegister.h"

#include <iostream>

gbtest::CGBSpeedSwitchRegister::CGBSpeedSwitchRegister()
        : m_cgbMode(false)
        , m_doubleSpeed(false)
        , m_prepareSpeedSwitch(false)
{

}

void gbtest::CGBSpeedSwitchRegister::setCGBMode(bool cgbMode)
{
    m_cgbMode = cgbMode;

    if (!m_cgbMode) {
        m_doubleSpeed = false;
    }
}

bool gbtest::CGBSpeedSwitchRegister::isCGBMode() const
{
    return m_cgbMode;
}

void gbtest::CGBSpeedSwitchRegister::setDoubleSpeed(bool doubleSpeed)
{
    m_doubleSpeed = doubleSpeed;
}

bool gbtest::CGBSpeedSwitchRegister::isDoubleSpeed() const
{
    return m_doubleSpeed;
}

void gbtest::CGBSpeedSwitchRegister::setPrepareSpeedSwitch(bool prepareSpeedSwitch)
{
    m_prepareSpeedSwitch = prepareSpeedSwitch;
}

bool gbtest::CGBSpeedSwitchRegister::isPreparingSpeedSwitch() const
{
    return m_prepareSpeedSwitch;
}

bool gbtest::CGBSpeedSwitchRegister::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // Don't do anything when not in CGB mode
    if (!m_cgbMode) {
        return false;
    }

    // Speed Switch register is in memory area FF4Dh
    if (addr != 0xFF4D) {
        return false;
    }

    // Return the register value
    val = 0x7E;

    if (m_prepareSpeedSwitch) {
        val |= 0x01;
    }

    if (m_doubleSpeed) {
        val |= 0x80;
    }

    return true;
}

bool gbtest::CGBSpeedSwitchRegister::busWrite(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // Don't do anything when not in CGB mode
    if (!m_cgbMode) {
        return false;
    }

    // Speed Switch register is in memory area FF4Dh
    if (addr != 0xFF4D) {
        return false;
    }

    // Set the prepare switch value
    m_prepareSpeedSwitch = ((val & 0x01) == 0x01);

    // Check if the CPU requested a speed switch
    if (!m_prepareSpeedSwitch && requestSource == gbtest::BusRequestSource::CPUSpeedSwitch) {
        m_doubleSpeed = !m_doubleSpeed;

        if (m_doubleSpeed) {
            std::cout << "Switching to double speed" << std::endl;
        }
        else {
            std::cout << "Switching to normal speed" << std::endl;
        }
    }

    return true;
}

bool gbtest::CGBSpeedSwitchRegister::busReadOverride(uint16_t addr, uint8_t& val,
        gbtest::BusRequestSource requestSource) const
{
    // Speed Switch register never overrides read requests
    return false;
}

bool
gbtest::CGBSpeedSwitchRegister::busWriteOverride(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // Speed Switch register never overrides write requests
    return false;
}
