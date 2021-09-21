#ifndef GBTEST_INTERRUPTTYPE_H
#define GBTEST_INTERRUPTTYPE_H

namespace gbtest {

enum class InterruptType {
    VBlank = 1 << 0,    // LCD VBlank interrupt
    LCDSTAT = 1 << 1,   // LCD STAT register interrupt
    Timer = 1 << 2,     // Timer overflow interrupt
    Serial = 1 << 3,    // Serial transfer complete interrupt
    Joypad = 1 << 4,    // Joypad button press interrupt
}; // enum class InterruptType

} // namespace gbtest

#endif //GBTEST_INTERRUPTTYPE_H
