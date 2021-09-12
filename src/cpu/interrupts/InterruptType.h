#ifndef GBTEST_INTERRUPTTYPE_H
#define GBTEST_INTERRUPTTYPE_H

namespace gbtest {

enum class InterruptType {
    VBlank = 0, // LCD VBlank interrupt
    LCDSTAT,    // LCD STAT register interrupt
    Timer,      // Timer overflow interrupt
    Serial,     // Serial transfer complete interrupt
    Joypad,     // Joypad button press interrupt
}; // enum class InterruptType

} // namespace gbtest

#endif //GBTEST_INTERRUPTTYPE_H
