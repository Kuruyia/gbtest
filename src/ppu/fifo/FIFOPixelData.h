#ifndef GBTEST_FIFOPIXELDATA_H
#define GBTEST_FIFOPIXELDATA_H

namespace gbtest {

// Data of a pixel in the FIFO
struct FIFOPixelData {
    uint8_t colorIndex;         // Color index of this pixel
    uint8_t palette;            // Palette to use for this pixel (DMG: Sprite only; CGB: Palette 0 to 7)
    uint8_t spriteOamIndex;     // Index of the sprite in the OAM (CGB only)
    bool backgroundPriority;    // For sprites: Priority of the sprite over the background
    // (False: Sprite above BG; True: BG colors 1 to 3 above sprite)
}; // struct FIFOPixelData

} // namespace gbtest

#endif //GBTEST_FIFOPIXELDATA_H
