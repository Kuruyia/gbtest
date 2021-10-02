#ifndef GBTEST_JOYPADSTATE_H
#define GBTEST_JOYPADSTATE_H

#include <cstdint>

namespace gbtest {

// State of each button of the emulated GameBoy (0: Pressed; 1: Released)
union JoypadState {
    struct {
        uint8_t inputRight: 1;  // [Direction] State of the Right button
        uint8_t inputLeft: 1;   // [Direction] State of the Left button
        uint8_t inputUp: 1;     // [Direction] State of the Up button
        uint8_t inputDown: 1;   // [Direction] State of the Down button
        uint8_t inputA: 1;      //    [Action] State of the A button
        uint8_t inputB: 1;      //    [Action] State of the B button
        uint8_t inputSelect: 1; //    [Action] State of the Select button
        uint8_t inputStart: 1;  //    [Action] State of the Start button
    };
    uint8_t raw;
}; // union JoypadState

enum class SelectedJoypadButtons {
    Joypad_Direction,
    Joypad_Action,
}; // enum class SelectedJoypadButtons

} // namespace gbtest

#endif //GBTEST_JOYPADSTATE_H
