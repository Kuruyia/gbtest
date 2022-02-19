#ifndef GBTEST_PPUMODETYPE_H
#define GBTEST_PPUMODETYPE_H

namespace gbtest {

enum class PPUModeType {
    HBlank,     // [Mode 0] PPU is in the Horizontal Blanking interval
    VBlank,     // [Mode 1] PPU is in the Vertical Blanking interval
    OAM_Search, // [Mode 2] PPU is searching the OAM for sprites on the current scanline
    Drawing,    // [Mode 3] PPU is drawing pixels to the LCD
}; // enum class PPUModeType

} // namespace gbtest

#endif //GBTEST_PPUMODETYPE_H
