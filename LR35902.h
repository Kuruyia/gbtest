#ifndef GBTEST_LR35902_H
#define GBTEST_LR35902_H

#include <cinttypes>

namespace gbtest
{

class LR35902
{

public:
    LR35902();

    void resetRegisters();

    struct
    {
        union // Accumulator & Flags
        {
            uint16_t af;
            struct
            {
                struct // Flags
                {
                    uint8_t zf     : 1; // Zero Flag
                    uint8_t n      : 1; // Add-Sub Flag
                    uint8_t h      : 1; // Half Carry Flag
                    uint8_t cy     : 1; // Carry Flag
                    uint8_t unused : 4; // Unused
                } f;

                uint8_t a;
            };
        };

        union // BC registers
        {
            uint16_t bc;
            struct
            {
                uint8_t c;
                uint8_t b;
            };
        };

        union // DE registers
        {
            uint16_t de;
            struct
            {
                uint8_t e;
                uint8_t d;
            };
        };

        union // HL registers
        {
            uint16_t hl;
            struct
            {
                uint8_t l;
                uint8_t h;
            };
        };

        uint16_t sp; // Stack Pointer
        uint16_t pc; // Program Counter
    } m_registers;

}; // class LR35902

} // namespace gbtest

#endif //GBTEST_LR35902_H
