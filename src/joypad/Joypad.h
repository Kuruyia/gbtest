#ifndef GBTEST_JOYPAD_H
#define GBTEST_JOYPAD_H

#include <cstdint>

#include "JoypadState.h"

#include "../platform/bus/Bus.h"
#include "../platform/bus/BusProvider.h"
#include "../utils/Tickable.h"

namespace gbtest {

class Joypad
        : public BusProvider, public Tickable {

public:
    explicit Joypad(Bus& m_bus);
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

    void tick() override;

private:
    Bus& m_bus;

    JoypadState m_joypadState;
    SelectedJoypadButtons m_selectedJoypadButtons;

    bool m_directionButtonWasPressed;
    bool m_actionButtonWasPressed;

}; // class Joypad

} // namespace gbtest

#endif //GBTEST_JOYPAD_H
