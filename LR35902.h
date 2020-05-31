#ifndef GBTEST_LR35902_H
#define GBTEST_LR35902_H

#include <cinttypes>
#include <functional>
#include <vector>

#include "Bus.h"

namespace gbtest
{

class LR35902
{

public:
    struct LR35902Registers
    {
        union // Accumulator & Flags
        {
            uint16_t af;
            struct
            {
                struct // Flags
                {
                    uint8_t z      : 1; // Zero Flag
                    uint8_t n      : 1; // Add-Sub Flag
                    uint8_t h      : 1; // Half Carry Flag
                    uint8_t c      : 1; // Carry Flag
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
    };

    typedef void (LR35902::*fnOpcode)();

public:
    LR35902(Bus &bus);

    const LR35902Registers &getRegisters() const;

    void tick();

private:
    void resetRegisters();
    uint8_t fetch();

    Bus &m_bus;

    const std::array<std::function<void()>, 0x100> m_opcodeLookup;

    uint8_t m_cyclesToWaste;
    LR35902Registers m_registers;
    bool m_ime; // Interrupt Master Enable Flag

    // Opcodes
    void opcode00h();
    void opcode01h();
    void opcode02h();
    void opcode03h();
    void opcode04h();
    void opcode05h();
    void opcode06h();
    void opcode07h();
    void opcode08h();
    void opcode09h();
    void opcode0Ah();
    void opcode0Bh();
    void opcode0Ch();
    void opcode0Dh();
    void opcode0Eh();
    void opcode0Fh();
    void opcode10h();
    void opcode11h();
    void opcode12h();
    void opcode13h();
    void opcode14h();
    void opcode15h();
    void opcode16h();
    void opcode17h();
    void opcode18h();
    void opcode19h();
    void opcode1Ah();
    void opcode1Bh();
    void opcode1Ch();
    void opcode1Dh();
    void opcode1Eh();
    void opcode1Fh();
    void opcode20h();
    void opcode21h();
    void opcode22h();
    void opcode23h();
    void opcode24h();
    void opcode25h();
    void opcode26h();
    void opcode27h();
    void opcode28h();
    void opcode29h();
    void opcode2Ah();
    void opcode2Bh();
    void opcode2Ch();
    void opcode2Dh();
    void opcode2Eh();
    void opcode2Fh();
    void opcode30h();
    void opcode31h();
    void opcode32h();
    void opcode33h();
    void opcode34h();
    void opcode35h();
    void opcode36h();
    void opcode37h();
    void opcode38h();
    void opcode39h();
    void opcode3Ah();
    void opcode3Bh();
    void opcode3Ch();
    void opcode3Dh();
    void opcode3Eh();
    void opcode3Fh();
    void opcode40h();
    void opcode41h();
    void opcode42h();
    void opcode43h();
    void opcode44h();
    void opcode45h();
    void opcode46h();
    void opcode47h();
    void opcode48h();
    void opcode49h();
    void opcode4Ah();
    void opcode4Bh();
    void opcode4Ch();
    void opcode4Dh();
    void opcode4Eh();
    void opcode4Fh();
    void opcode50h();
    void opcode51h();
    void opcode52h();
    void opcode53h();
    void opcode54h();
    void opcode55h();
    void opcode56h();
    void opcode57h();
    void opcode58h();
    void opcode59h();
    void opcode5Ah();
    void opcode5Bh();
    void opcode5Ch();
    void opcode5Dh();
    void opcode5Eh();
    void opcode5Fh();
    void opcode60h();
    void opcode61h();
    void opcode62h();
    void opcode63h();
    void opcode64h();
    void opcode65h();
    void opcode66h();
    void opcode67h();
    void opcode68h();
    void opcode69h();
    void opcode6Ah();
    void opcode6Bh();
    void opcode6Ch();
    void opcode6Dh();
    void opcode6Eh();
    void opcode6Fh();
    void opcode70h();
    void opcode71h();
    void opcode72h();
    void opcode73h();
    void opcode74h();
    void opcode75h();
    void opcode76h();
    void opcode77h();
    void opcode78h();
    void opcode79h();
    void opcode7Ah();
    void opcode7Bh();
    void opcode7Ch();
    void opcode7Dh();
    void opcode7Eh();
    void opcode7Fh();
    void opcode80h();
    void opcode81h();
    void opcode82h();
    void opcode83h();
    void opcode84h();
    void opcode85h();
    void opcode86h();
    void opcode87h();
    void opcode88h();
    void opcode89h();
    void opcode8Ah();
    void opcode8Bh();
    void opcode8Ch();
    void opcode8Dh();
    void opcode8Eh();
    void opcode8Fh();
    void opcode90h();
    void opcode91h();
    void opcode92h();
    void opcode93h();
    void opcode94h();
    void opcode95h();
    void opcode96h();
    void opcode97h();
    void opcode98h();
    void opcode99h();
    void opcode9Ah();
    void opcode9Bh();
    void opcode9Ch();
    void opcode9Dh();
    void opcode9Eh();
    void opcode9Fh();
    void opcodeA0h();
    void opcodeA1h();
    void opcodeA2h();
    void opcodeA3h();
    void opcodeA4h();
    void opcodeA5h();
    void opcodeA6h();
    void opcodeA7h();
    void opcodeA8h();
    void opcodeA9h();
    void opcodeAAh();
    void opcodeABh();
    void opcodeACh();
    void opcodeADh();
    void opcodeAEh();
    void opcodeAFh();
    void opcodeB0h();
    void opcodeB1h();
    void opcodeB2h();
    void opcodeB3h();
    void opcodeB4h();
    void opcodeB5h();
    void opcodeB6h();
    void opcodeB7h();
    void opcodeB8h();
    void opcodeB9h();
    void opcodeBAh();
    void opcodeBBh();
    void opcodeBCh();
    void opcodeBDh();
    void opcodeBEh();
    void opcodeBFh();
    void opcodeC0h();
    void opcodeC1h();
    void opcodeC2h();
    void opcodeC3h();
    void opcodeC4h();
    void opcodeC5h();
    void opcodeC6h();
    void opcodeC7h();
    void opcodeC8h();
    void opcodeC9h();
    void opcodeCAh();
    void opcodeCBh();
    void opcodeCCh();
    void opcodeCDh();
    void opcodeCEh();
    void opcodeCFh();
    void opcodeD0h();
    void opcodeD1h();
    void opcodeD2h();
    void opcodeD3h();
    void opcodeD4h();
    void opcodeD5h();
    void opcodeD6h();
    void opcodeD7h();
    void opcodeD8h();
    void opcodeD9h();
    void opcodeDAh();
    void opcodeDBh();
    void opcodeDCh();
    void opcodeDDh();
    void opcodeDEh();
    void opcodeDFh();
    void opcodeE0h();
    void opcodeE1h();
    void opcodeE2h();
    void opcodeE3h();
    void opcodeE4h();
    void opcodeE5h();
    void opcodeE6h();
    void opcodeE7h();
    void opcodeE8h();
    void opcodeE9h();
    void opcodeEAh();
    void opcodeEBh();
    void opcodeECh();
    void opcodeEDh();
    void opcodeEEh();
    void opcodeEFh();
    void opcodeF0h();
    void opcodeF1h();
    void opcodeF2h();
    void opcodeF3h();
    void opcodeF4h();
    void opcodeF5h();
    void opcodeF6h();
    void opcodeF7h();
    void opcodeF8h();
    void opcodeF9h();
    void opcodeFAh();
    void opcodeFBh();
    void opcodeFCh();
    void opcodeFDh();
    void opcodeFEh();
    void opcodeFFh();


}; // class LR35902

} // namespace gbtest

#endif //GBTEST_LR35902_H
