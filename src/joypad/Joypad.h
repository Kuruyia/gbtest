#ifndef GBTEST_JOYPAD_H
#define GBTEST_JOYPAD_H

#include <cstdint>

#include "JoypadState.h"

#include "../platform/bus/BusProvider.h"

namespace gbtest {

class Joypad
        : public BusProvider {

public:
    Joypad();

    ~Joypad() override = default;

    void setRightButtonPressed(bool pressed);
    [[nodiscard]] bool isRightButtonPressed() const;

    void setLeftButtonPressed(bool pressed);
    [[nodiscard]] bool isLeftButtonPressed() const;

    void setUpButtonPressed(bool pressed);
    [[nodiscard]] bool isUpButtonPressed() const;

    void setDownButtonPressed(bool pressed);
    [[nodiscard]] bool isDownButtonPressed() const;

    void setAButtonPressed(bool pressed);
    [[nodiscard]] bool isAButtonPressed() const;

    void setBButtonPressed(bool pressed);
    [[nodiscard]] bool isBButtonPressed() const;

    void setSelectButtonPressed(bool pressed);
    [[nodiscard]] bool isSelectButtonPressed() const;

    void setStartButtonPressed(bool pressed);
    [[nodiscard]] bool isStartButtonPressed() const;

    void
    updateJoypadState(bool rightPressed, bool leftPressed, bool upPressed, bool downPressed, bool aPressed,
            bool bPressed,
            bool selectPressed, bool startPressed);

    [[nodiscard]] const JoypadState& getJoypadState() const;
    [[nodiscard]] const SelectedJoypadButtons& getSelectedJoypadButtons() const;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

private:
    JoypadState m_joypadState;
    SelectedJoypadButtons m_selectedJoypadButtons;

}; // class Joypad

} // namespace gbtest

#endif //GBTEST_JOYPAD_H
