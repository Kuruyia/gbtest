#ifndef GBTEST_OAMENTRY_H
#define GBTEST_OAMENTRY_H

#include <cinttypes>

namespace gbtest {

union OAMEntryFlags {
    struct {
        uint8_t cgbPaletteNumber: 3;
        uint8_t tileVramBank: 1;
        uint8_t dmgPaletteNumber: 1;
        uint8_t xFlip: 1;
        uint8_t yFlip: 1;
        uint8_t bgAndWindowsOverObj: 1;
    };
    uint8_t raw;
}; // union OAMEntryFlags

static_assert(sizeof(OAMEntryFlags) == 1, "OAM Entry Flags size is incorrect");

struct OAMEntry {
    uint8_t yPosition;
    uint8_t xPosition;
    uint8_t tileIndex;
    OAMEntryFlags flags;
}; // struct OAMEntry

} // namespace gbtest

#endif //GBTEST_OAMENTRY_H
