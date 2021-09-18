#include <array>

#include "ColorUtils.h"

static constexpr std::array<gbtest::ColorUtils::ColorRGB888, 4> s_dmgPaletteColors = {
        gbtest::ColorUtils::ColorRGB888(255, 255, 255), // White
        gbtest::ColorUtils::ColorRGB888(170, 170, 170), // Light gray
        gbtest::ColorUtils::ColorRGB888(85, 85, 85), // Dark gray
        gbtest::ColorUtils::ColorRGB888(0, 0, 0), // Black
};

gbtest::ColorUtils::ColorRGB888
gbtest::ColorUtils::dmgBGPaletteIndexToRGB888(const MonochromePalette& dmgBgPalette, const uint8_t colorIndex)
{
    switch (colorIndex) {
    case 0: // Index 0
        return s_dmgPaletteColors.at(dmgBgPalette.colorIdx0);

    case 1: // Index 1
        return s_dmgPaletteColors.at(dmgBgPalette.colorIdx1);

    case 2: // Index 2
        return s_dmgPaletteColors.at(dmgBgPalette.colorIdx2);

    default: // Index 3 or Invalid index
        return s_dmgPaletteColors.at(dmgBgPalette.colorIdx3);
    }
}
