#ifndef GBTEST_VRAMMAPATTRIBUTESDATA_H
#define GBTEST_VRAMMAPATTRIBUTESDATA_H

#include <cstdint>

namespace gbtest {

// BG Map Attributes (CGB Mode only)
union VRAMMapAttributesData {
    struct {
        uint8_t backgroundPaletteNumber: 3; // Number of the background palette to use (BGP0-7)
        uint8_t tileVRAMBankNumber: 1;      // Bank number of the VRAM tile (0: Bank 0; 1: Bank 1)
        uint8_t unused: 1;
        uint8_t xFlip: 1;                   // Horizontal mirroring of the tile (0: No; 1: Yes)
        uint8_t yFlip: 1;                   // Vertical mirroring of the tile (0: No; 1: Yes)
        uint8_t bgToOAMPriority: 1;         // Priority (0: Normal priority; 1: Priority over all OBJs)
    };
    uint8_t raw;
}; // union VRAMMapAttributesData

static_assert(sizeof(VRAMMapAttributesData) == 1, "VRAM Map Attributes data structure size is incorrect");

} // namespace gbtest

#endif //GBTEST_VRAMMAPATTRIBUTESDATA_H
