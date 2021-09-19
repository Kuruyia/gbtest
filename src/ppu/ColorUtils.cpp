#include <array>

#include "ColorUtils.h"

static constexpr std::array<gbtest::ColorUtils::ColorRGBA8888, 4> s_dmgPaletteColors = {
        gbtest::ColorUtils::ColorRGBA8888(255, 255, 255), // White
        gbtest::ColorUtils::ColorRGBA8888(170, 170, 170), // Light gray
        gbtest::ColorUtils::ColorRGBA8888(85, 85, 85), // Dark gray
        gbtest::ColorUtils::ColorRGBA8888(0, 0, 0), // Black
};

gbtest::ColorUtils::ColorRGBA8888
gbtest::ColorUtils::dmgBGPaletteIndexToRGBA8888(const MonochromePalette& dmgBgPalette, uint8_t colorIndex)
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
