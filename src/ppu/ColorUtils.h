#ifndef GBTEST_COLORUTILS_H
#define GBTEST_COLORUTILS_H

#include <cstdint>

#include "PPURegisters.h"

namespace gbtest::ColorUtils {

union ColorRGBA8888 {
    struct {
        uint8_t r; // Red component
        uint8_t g; // Green component
        uint8_t b; // Blue component
        uint8_t a; // Alpha component
    };
    uint32_t raw;

    ColorRGBA8888()
            : r(0xFF)
            , g(0xFF)
            , b(0xFF)
            , a(0xFF)
    {

    }

    constexpr ColorRGBA8888(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF)
            : r(r)
            , g(g)
            , b(b)
            , a(a)
    {

    }
}; // union ColorRGBA8888

static_assert(sizeof(ColorRGBA8888) == 4, "ColorRGBA8888 structure size is incorrect");

[[nodiscard]] ColorRGBA8888 dmgBGPaletteIndexToRGBA8888(const MonochromePalette& dmgBgPalette, uint8_t colorIndex);

} // namespace gbtest::ColorUtils

#endif //GBTEST_COLORUTILS_H
