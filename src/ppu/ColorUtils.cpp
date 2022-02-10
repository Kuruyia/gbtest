#include <array>

#include "ColorUtils.h"

void gbtest::ColorUtils::dmgBGPaletteIndexToRGBA8888(const MonochromePalette& dmgBgPalette, uint8_t colorIndex,
                                                     gbtest::ColorUtils::ColorRGBA8888& pixel)
{
    switch (colorIndex) {
    case 0: // Index 0
        pixel.raw = 0xFFFFFFFF; // White
        break;

    case 1: // Index 1
        pixel.raw = 0xFFAAAAAA; // Light gray
        break;

    case 2: // Index 2
        pixel.raw = 0xFF555555; // Dark gray
        break;

    default: // Index 3 or Invalid index
        pixel.raw = 0xFF000000; // Black
        break;
    }
}
