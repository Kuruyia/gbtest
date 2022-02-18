#ifndef GBTEST_LR35902REGISTERS_H
#define GBTEST_LR35902REGISTERS_H

namespace gbtest {

struct LR35902Registers {
    union // Accumulator & Flags
    {
        uint16_t af;
        struct {
            struct // Flags
            {
                uint8_t unused: 4; // Unused
                uint8_t c: 1; // Carry Flag
                uint8_t h: 1; // Half Carry Flag
                uint8_t n: 1; // Add-Sub Flag
                uint8_t z: 1; // Zero Flag
            } f;

            uint8_t a;
        };
    };

    union // BC registers
    {
        uint16_t bc;
        struct {
            uint8_t c;
            uint8_t b;
        };
    };

    union // DE registers
    {
        uint16_t de;
        struct {
            uint8_t e;
            uint8_t d;
        };
    };

    union // HL registers
    {
        uint16_t hl;
        struct {
            uint8_t l;
            uint8_t h;
        };
    };

    uint16_t sp; // Stack Pointer
    uint16_t pc; // Program Counter
}; // struct LR35902Registers

} // namespace gbtest

#endif //GBTEST_LR35902REGISTERS_H
