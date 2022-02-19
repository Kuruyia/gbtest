#include <array>

#include "ColorUtils.h"

void gbtest::ColorUtils::dmgPaletteIndexToRGBA8888(const MonochromePaletteReg& palette, uint8_t index,
                                                     gbtest::ColorUtils::ColorRGBA8888& pixel)
{
    // Lookup table for colors
    static const uint32_t colors[] = {
            0xFFFFFFFF,
            0xFFAAAAAA,
            0xFF555555,
            0xFF000000
    };

    // Set the correct color
    pixel.raw = colors[(palette.raw >> (index * 2)) & 0x3];
}
