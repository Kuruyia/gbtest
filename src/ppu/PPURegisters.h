#ifndef GBTEST_PPUREGISTERS_H
#define GBTEST_PPUREGISTERS_H

#include <array>
#include <cstdint>

namespace gbtest {

// [LCDC] LCD Control register
union LCDControlReg {
    struct {
        uint8_t bgAndWindowEnable: 1;       // DMG: Display BG and Window tiles; CGB: BG and Window display priority
        uint8_t objEnable: 1;               // Enable/disable sprite drawing
        uint8_t objSize: 1;                 // Sprite size (0: 8x8; 1: 8x16)
        uint8_t bgTileMapArea: 1;           // Area to use for BG tile map  (0: 9800h to 9BFFh; 1: 9C00h to 9FFFh)
        uint8_t bgAndWindowTileDataArea: 1; // Area to use for BG tile data (0: 8800h to 97FFh; 1: 8000h to 8FFFh)
        uint8_t windowEnable: 1;            // Enable/disable window drawing
        uint8_t windowTileMapArea: 1;       // Area to use for Window tile map  (0: 9800h to 9BFFh; 1: 9C00h to 9FFFh)
        uint8_t lcdAndPpuEnable: 1;         // Enable/disable LCD and PPU
    };
    uint8_t raw;
}; // union LCDControlReg

static_assert(sizeof(LCDControlReg) == 1, "LCD Control register structure size is incorrect");

// [STAT] LCD Status register
union LCDStatusReg {
    struct {
        uint8_t mode: 2;                        // Current PPU mode
        uint8_t lycEqualsLy: 1;                 // Is LY == LYC? (0: No; 1: Yes)
        uint8_t mode0InterruptSource: 1;        // Request STAT interrupt when reaching mode 0
        uint8_t mode1InterruptSource: 1;        // Request STAT interrupt when reaching mode 1
        uint8_t mode2InterruptSource: 1;        // Request STAT interrupt when reaching mode 2
        uint8_t lycEqualsLyInterruptSource: 1;  // Request STAT interrupt when LY == LYC
        uint8_t unused: 1;
    };
    uint8_t raw;
}; // union LCDStatusReg

static_assert(sizeof(LCDStatusReg) == 1, "LCD Status register structure size is incorrect");

// LCD Position and Scrolling registers
struct LCDPositionAndScrollingRegs {
    uint8_t yScroll;            // [SCY] BG Y scroll coordinate
    uint8_t xScroll;            // [SCX] BG X scroll coordinate
    uint8_t yLcdCoordinate;     // [ LY] LCD Y coordinate
    uint8_t lyCompare;          // [LYC] LY compare
    uint8_t yWindowPosition;    // [ WY] Window Y position
    uint8_t xWindowPosition;    // [ WX] Window X position
}; // struct LCDPositionAndScrollingRegs

static_assert(sizeof(LCDPositionAndScrollingRegs) == 6, "LCD Position and Scrolling registers structure size is incorrect");

// Palette registers
union MonochromePaletteReg {
    struct {
        uint8_t colorIdx0: 2; // Color for index 0
        uint8_t colorIdx1: 2; // Color for index 1
        uint8_t colorIdx2: 2; // Color for index 2
        uint8_t colorIdx3: 2; // Color for index 3
    };
    uint8_t raw;
}; // union MonochromePaletteReg

static_assert(sizeof(MonochromePaletteReg) == 1, "Monochrome Palette register structure size is incorrect");

struct DMGPaletteRegs {
    MonochromePaletteReg bgPaletteData;        // [ BGP] Data for the BG palette
    MonochromePaletteReg objectPaletteData0;   // [OBP0] Data for the first OBJ palette
    MonochromePaletteReg objectPaletteData1;   // [OBP1] Data for the second OBJ palette
}; // struct DMGPaletteRegs

static_assert(sizeof(DMGPaletteRegs) == 3, "DMG Palette registers register structure size is incorrect");

union CGBPaletteIndex {
    struct {
        uint8_t address: 6;         // Address of the palette data register to expose
        uint8_t unused: 1;
        uint8_t autoIncrement: 1;   // Increment the address after writing the data register (0: Disabled; 1: Enabled)
    };
    uint8_t raw;
}; // union CGBPaletteIndex

static_assert(sizeof(CGBPaletteIndex) == 1, "CGB Palette Index register structure size is incorrect");

// CGB palette registers
using CGBPaletteRegs = std::array<uint8_t, 64>;

// Registers
struct PPURegisters {
    LCDControlReg lcdControl;
    LCDStatusReg lcdStatus;
    LCDPositionAndScrollingRegs lcdPositionAndScrolling;
    DMGPaletteRegs dmgPalettes;
    CGBPaletteIndex cgbBackgroundPaletteIndex;
    CGBPaletteRegs cgbBackgroundPalettes;
    CGBPaletteIndex cgbObjPaletteIndex;
    CGBPaletteRegs cgbObjPalettes;
}; // struct PPURegisters

} // namespace gbtest

#endif //GBTEST_PPUREGISTERS_H
