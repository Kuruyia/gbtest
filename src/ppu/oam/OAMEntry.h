#ifndef GBTEST_OAMENTRY_H
#define GBTEST_OAMENTRY_H

#include <cinttypes>

namespace gbtest {

// Flags for an OAM entry
union OAMEntryFlags {
    struct {
        uint8_t cgbPaletteNumber: 3;    // Palette number (CGB only)
        uint8_t tileVramBank: 1;        // VRAM bank containing the tile (CGB only)
        uint8_t dmgPaletteNumber: 1;    // Palette number (DMG only)
        uint8_t xFlip: 1;               // Horizontal mirroring of the sprite (0: No; 1: Yes)
        uint8_t yFlip: 1;               // Vertical mirroring of the sprite (0: No; 1: Yes)
        uint8_t bgAndWindowsOverObj: 1; // BG and Window colors 1 to 3 over the sprite (0: No; 1: Yes)
    };
    uint8_t raw;
}; // union OAMEntryFlags

static_assert(sizeof(OAMEntryFlags) == 1, "OAM Entry Flags structure size is incorrect");

// Single entry in the OAM memory area
struct OAMEntry {
    uint8_t yPosition;      // Sprite Y position
    uint8_t xPosition;      // Sprite X position
    uint8_t tileIndex;      // Index of the tile to use for drawing the sprite
    OAMEntryFlags flags;    // Sprite flags
}; // struct OAMEntry

} // namespace gbtest

#endif //GBTEST_OAMENTRY_H
