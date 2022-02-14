#include "Joypad.h"

gbtest::Joypad::Joypad(Bus& bus)
        : m_bus(bus)
        , m_joypadState()
        , m_selectedJoypadButtons(SelectedJoypadButtons::Joypad_Action)
{
    m_joypadState.raw = 0xFF;
}

void gbtest::Joypad::setRightButtonPressed(bool pressed)
{
    m_joypadState.inputRight = (pressed ? 0 : 1);

    // Check if we have to request an interrupt
    if (pressed && m_selectedJoypadButtons == SelectedJoypadButtons::Joypad_Direction) {
        m_bus.setInterruptLineHigh(InterruptType::Joypad, true);
    }
}

bool gbtest::Joypad::isRightButtonPressed() const
{
    return m_joypadState.inputRight == 0;
}

void gbtest::Joypad::setLeftButtonPressed(bool pressed)
{
    m_joypadState.inputLeft = (pressed ? 0 : 1);

    // Check if we have to request an interrupt
    if (pressed && m_selectedJoypadButtons == SelectedJoypadButtons::Joypad_Direction) {
        m_bus.setInterruptLineHigh(InterruptType::Joypad, true);
    }
}

bool gbtest::Joypad::isLeftButtonPressed() const
{
    return m_joypadState.inputLeft == 0;
}

void gbtest::Joypad::setUpButtonPressed(bool pressed)
{
    m_joypadState.inputUp = (pressed ? 0 : 1);

    // Check if we have to request an interrupt
    if (pressed && m_selectedJoypadButtons == SelectedJoypadButtons::Joypad_Direction) {
        m_bus.setInterruptLineHigh(InterruptType::Joypad, true);
    }
}

bool gbtest::Joypad::isUpButtonPressed() const
{
    return m_joypadState.inputUp == 0;
}

void gbtest::Joypad::setDownButtonPressed(bool pressed)
{
    m_joypadState.inputDown = (pressed ? 0 : 1);

    // Check if we have to request an interrupt
    if (pressed && m_selectedJoypadButtons == SelectedJoypadButtons::Joypad_Direction) {
        m_bus.setInterruptLineHigh(InterruptType::Joypad, true);
    }
}

bool gbtest::Joypad::isDownButtonPressed() const
{
    return m_joypadState.inputDown == 0;
}

void gbtest::Joypad::setAButtonPressed(bool pressed)
{
    m_joypadState.inputA = (pressed ? 0 : 1);

    // Check if we have to request an interrupt
    if (pressed && m_selectedJoypadButtons == SelectedJoypadButtons::Joypad_Action) {
        m_bus.setInterruptLineHigh(InterruptType::Joypad, true);
    }
}

bool gbtest::Joypad::isAButtonPressed() const
{
    return m_joypadState.inputA == 0;
}

void gbtest::Joypad::setBButtonPressed(bool pressed)
{
    m_joypadState.inputB = (pressed ? 0 : 1);

    // Check if we have to request an interrupt
    if (pressed && m_selectedJoypadButtons == SelectedJoypadButtons::Joypad_Action) {
        m_bus.setInterruptLineHigh(InterruptType::Joypad, true);
    }
}

bool gbtest::Joypad::isBButtonPressed() const
{
    return m_joypadState.inputB == 0;
}

void gbtest::Joypad::setSelectButtonPressed(bool pressed)
{
    m_joypadState.inputSelect = (pressed ? 0 : 1);

    // Check if we have to request an interrupt
    if (pressed && m_selectedJoypadButtons == SelectedJoypadButtons::Joypad_Action) {
        m_bus.setInterruptLineHigh(InterruptType::Joypad, true);
    }
}

bool gbtest::Joypad::isSelectButtonPressed() const
{
    return m_joypadState.inputSelect == 0;
}

void gbtest::Joypad::setStartButtonPressed(bool pressed)
{
    m_joypadState.inputStart = (pressed ? 0 : 1);

    // Check if we have to request an interrupt
    if (pressed && m_selectedJoypadButtons == SelectedJoypadButtons::Joypad_Action) {
        m_bus.setInterruptLineHigh(InterruptType::Joypad, true);
    }
}

bool gbtest::Joypad::isStartButtonPressed() const
{
    return m_joypadState.inputStart == 0;
}

void
gbtest::Joypad::updateJoypadState(bool rightPressed, bool leftPressed, bool upPressed, bool downPressed, bool aPressed,
        bool bPressed, bool selectPressed, bool startPressed)
{
    // Update the joypad state
    m_joypadState = {{
                             !rightPressed,
                             !leftPressed,
                             !upPressed,
                             !downPressed,
                             !aPressed,
                             !bPressed,
                             !selectPressed,
                             !startPressed,
                     }};

    // Check if we have to request an interrupt
    const bool directionPressed = (rightPressed || leftPressed || upPressed || downPressed);
    const bool actionPressed = (aPressed || bPressed || selectPressed || startPressed);

    if ((directionPressed && m_selectedJoypadButtons == SelectedJoypadButtons::Joypad_Direction) ||
            (actionPressed && m_selectedJoypadButtons == SelectedJoypadButtons::Joypad_Action)) {
        m_bus.setInterruptLineHigh(InterruptType::Joypad, true);
    }
}

const gbtest::JoypadState& gbtest::Joypad::getJoypadState() const
{
    return m_joypadState;
}

const gbtest::SelectedJoypadButtons& gbtest::Joypad::getSelectedJoypadButtons() const
{
    return m_selectedJoypadButtons;
}

bool gbtest::Joypad::busRead(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // Joypad only handles memory address FF00h
    if (addr != 0xFF00) { return false; }

    // Initialize the value
    val = 0xF0;

    if (m_selectedJoypadButtons == SelectedJoypadButtons::Joypad_Direction) {
        // Return direction buttons state
        val |= (m_joypadState.raw & 0x0F);
    }
    else {
        // Return action buttons state
        val |= (m_joypadState.raw >> 4);
    }

    return true;
}

bool gbtest::Joypad::busWrite(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // Joypad only handles memory address FF00h
    if (addr != 0xFF00) { return false; }

    // Check the value written (either the game wants to know about action or direction buttons)
    const uint8_t selectedButtons = (val & 0x30);

    if (selectedButtons == 0x20) {
        // Bit 4 == 0; Direction buttons selected
        m_selectedJoypadButtons = SelectedJoypadButtons::Joypad_Direction;
    }
    else if (selectedButtons == 0x10) {
        // Bit 5 == 0; Action buttons selected
        m_selectedJoypadButtons = SelectedJoypadButtons::Joypad_Action;
    }

    return true;
}

bool gbtest::Joypad::busReadOverride(uint16_t addr, uint8_t& val, gbtest::BusRequestSource requestSource) const
{
    // Joypad never overrides read requests
    return false;
}

bool gbtest::Joypad::busWriteOverride(uint16_t addr, uint8_t val, gbtest::BusRequestSource requestSource)
{
    // Joypad never overrides write requests
    return false;
}
