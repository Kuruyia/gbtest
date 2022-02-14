#ifndef GBTEST_LR35902HALTSTATE_H
#define GBTEST_LR35902HALTSTATE_H

namespace gbtest {

enum class LR35902HaltState {
    Running,    // The CPU is running normally
    Halted,     // The CPU has been halted by the "halt" instruction
    Stopped     // The CPU has been stopped by the "stop" instruction
}; // enum class LR35902HaltState

enum class LR35902HaltBug {
    NoBug,      // No halt bug is happening
    RegularBug, // The next fetch will not increment the PC register
    EIBug       // The "halt" instruction will be executed twice
}; // enum class LR35902HaltBug

} // namespace gbtest

#endif //GBTEST_LR35902HALTSTATE_H
