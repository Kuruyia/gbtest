#ifndef GBTEST_COLORUTILS_H
#define GBTEST_COLORUTILS_H

#include <cstdint>

#include "PPURegisters.h"

namespace gbtest::ColorUtils {

struct ColorRGB888 {
    uint8_t r; // Red component
    uint8_t g; // Green component
    uint8_t b; // Blue component

    constexpr ColorRGB888(uint8_t r, uint8_t g, uint8_t b)
            : r(r)
            , g(g)
            , b(b)
    {

    }
}; // struct ColorRGB888

[[nodiscard]] ColorRGB888 dmgBGPaletteIndexToRGB888(const MonochromePalette& dmgBgPalette, uint8_t colorIndex);

} // namespace gbtest::ColorUtils

#endif //GBTEST_COLORUTILS_H
