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
}; // union ColorRGBA8888

static_assert(sizeof(ColorRGBA8888) == 4, "ColorRGBA8888 structure size is incorrect");

void dmgPaletteIndexToRGBA8888(const MonochromePaletteReg& palette, uint8_t index,
        ColorRGBA8888& pixel);

void cgbPaletteColorToRGBA8888(uint8_t lowColorByte, uint8_t highColorByte, ColorRGBA8888& pixel);

} // namespace gbtest::ColorUtils

#endif //GBTEST_COLORUTILS_H
