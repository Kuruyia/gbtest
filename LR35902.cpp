#include <iostream>
#include <stdexcept>

#include "LR35902.h"

gbtest::LR35902::LR35902(Bus &bus)
: m_bus(bus)
, m_opcodeLookup({[this] { opcode00h(); }, [this] { opcode01h(); }, [this] { opcode02h(); }, [this] { opcode03h(); }, [this] { opcode04h(); }, [this] { opcode05h(); }, [this] { opcode06h(); }, [this] { opcode07h(); }, [this] { opcode08h(); }, [this] { opcode09h(); }, [this] { opcode0Ah(); }, [this] { opcode0Bh(); }, [this] { opcode0Ch(); }, [this] { opcode0Dh(); }, [this] { opcode0Eh(); }, [this] { opcode0Fh(); },
                  [this] { opcode10h(); }, [this] { opcode11h(); }, [this] { opcode12h(); }, [this] { opcode13h(); }, [this] { opcode14h(); }, [this] { opcode15h(); }, [this] { opcode16h(); }, [this] { opcode17h(); }, [this] { opcode18h(); }, [this] { opcode19h(); }, [this] { opcode1Ah(); }, [this] { opcode1Bh(); }, [this] { opcode1Ch(); }, [this] { opcode1Dh(); }, [this] { opcode1Eh(); }, [this] { opcode1Fh(); },
                  [this] { opcode20h(); }, [this] { opcode21h(); }, [this] { opcode22h(); }, [this] { opcode23h(); }, [this] { opcode24h(); }, [this] { opcode25h(); }, [this] { opcode26h(); }, [this] { opcode27h(); }, [this] { opcode28h(); }, [this] { opcode29h(); }, [this] { opcode2Ah(); }, [this] { opcode2Bh(); }, [this] { opcode2Ch(); }, [this] { opcode2Dh(); }, [this] { opcode2Eh(); }, [this] { opcode2Fh(); },
                  [this] { opcode30h(); }, [this] { opcode31h(); }, [this] { opcode32h(); }, [this] { opcode33h(); }, [this] { opcode34h(); }, [this] { opcode35h(); }, [this] { opcode36h(); }, [this] { opcode37h(); }, [this] { opcode38h(); }, [this] { opcode39h(); }, [this] { opcode3Ah(); }, [this] { opcode3Bh(); }, [this] { opcode3Ch(); }, [this] { opcode3Dh(); }, [this] { opcode3Eh(); }, [this] { opcode3Fh(); },
                  [this] { opcode40h(); }, [this] { opcode41h(); }, [this] { opcode42h(); }, [this] { opcode43h(); }, [this] { opcode44h(); }, [this] { opcode45h(); }, [this] { opcode46h(); }, [this] { opcode47h(); }, [this] { opcode48h(); }, [this] { opcode49h(); }, [this] { opcode4Ah(); }, [this] { opcode4Bh(); }, [this] { opcode4Ch(); }, [this] { opcode4Dh(); }, [this] { opcode4Eh(); }, [this] { opcode4Fh(); },
                  [this] { opcode50h(); }, [this] { opcode51h(); }, [this] { opcode52h(); }, [this] { opcode53h(); }, [this] { opcode54h(); }, [this] { opcode55h(); }, [this] { opcode56h(); }, [this] { opcode57h(); }, [this] { opcode58h(); }, [this] { opcode59h(); }, [this] { opcode5Ah(); }, [this] { opcode5Bh(); }, [this] { opcode5Ch(); }, [this] { opcode5Dh(); }, [this] { opcode5Eh(); }, [this] { opcode5Fh(); },
                  [this] { opcode60h(); }, [this] { opcode61h(); }, [this] { opcode62h(); }, [this] { opcode63h(); }, [this] { opcode64h(); }, [this] { opcode65h(); }, [this] { opcode66h(); }, [this] { opcode67h(); }, [this] { opcode68h(); }, [this] { opcode69h(); }, [this] { opcode6Ah(); }, [this] { opcode6Bh(); }, [this] { opcode6Ch(); }, [this] { opcode6Dh(); }, [this] { opcode6Eh(); }, [this] { opcode6Fh(); },
                  [this] { opcode70h(); }, [this] { opcode71h(); }, [this] { opcode72h(); }, [this] { opcode73h(); }, [this] { opcode74h(); }, [this] { opcode75h(); }, [this] { opcode76h(); }, [this] { opcode77h(); }, [this] { opcode78h(); }, [this] { opcode79h(); }, [this] { opcode7Ah(); }, [this] { opcode7Bh(); }, [this] { opcode7Ch(); }, [this] { opcode7Dh(); }, [this] { opcode7Eh(); }, [this] { opcode7Fh(); },
                  [this] { opcode80h(); }, [this] { opcode81h(); }, [this] { opcode82h(); }, [this] { opcode83h(); }, [this] { opcode84h(); }, [this] { opcode85h(); }, [this] { opcode86h(); }, [this] { opcode87h(); }, [this] { opcode88h(); }, [this] { opcode89h(); }, [this] { opcode8Ah(); }, [this] { opcode8Bh(); }, [this] { opcode8Ch(); }, [this] { opcode8Dh(); }, [this] { opcode8Eh(); }, [this] { opcode8Fh(); },
                  [this] { opcode90h(); }, [this] { opcode91h(); }, [this] { opcode92h(); }, [this] { opcode93h(); }, [this] { opcode94h(); }, [this] { opcode95h(); }, [this] { opcode96h(); }, [this] { opcode97h(); }, [this] { opcode98h(); }, [this] { opcode99h(); }, [this] { opcode9Ah(); }, [this] { opcode9Bh(); }, [this] { opcode9Ch(); }, [this] { opcode9Dh(); }, [this] { opcode9Eh(); }, [this] { opcode9Fh(); },
                  [this] { opcodeA0h(); }, [this] { opcodeA1h(); }, [this] { opcodeA2h(); }, [this] { opcodeA3h(); }, [this] { opcodeA4h(); }, [this] { opcodeA5h(); }, [this] { opcodeA6h(); }, [this] { opcodeA7h(); }, [this] { opcodeA8h(); }, [this] { opcodeA9h(); }, [this] { opcodeAAh(); }, [this] { opcodeABh(); }, [this] { opcodeACh(); }, [this] { opcodeADh(); }, [this] { opcodeAEh(); }, [this] { opcodeAFh(); },
                  [this] { opcodeB0h(); }, [this] { opcodeB1h(); }, [this] { opcodeB2h(); }, [this] { opcodeB3h(); }, [this] { opcodeB4h(); }, [this] { opcodeB5h(); }, [this] { opcodeB6h(); }, [this] { opcodeB7h(); }, [this] { opcodeB8h(); }, [this] { opcodeB9h(); }, [this] { opcodeBAh(); }, [this] { opcodeBBh(); }, [this] { opcodeBCh(); }, [this] { opcodeBDh(); }, [this] { opcodeBEh(); }, [this] { opcodeBFh(); },
                  [this] { opcodeC0h(); }, [this] { opcodeC1h(); }, [this] { opcodeC2h(); }, [this] { opcodeC3h(); }, [this] { opcodeC4h(); }, [this] { opcodeC5h(); }, [this] { opcodeC6h(); }, [this] { opcodeC7h(); }, [this] { opcodeC8h(); }, [this] { opcodeC9h(); }, [this] { opcodeCAh(); }, [this] { opcodeCBh(); }, [this] { opcodeCCh(); }, [this] { opcodeCDh(); }, [this] { opcodeCEh(); }, [this] { opcodeCFh(); },
                  [this] { opcodeD0h(); }, [this] { opcodeD1h(); }, [this] { opcodeD2h(); }, [this] { opcodeD3h(); }, [this] { opcodeD4h(); }, [this] { opcodeD5h(); }, [this] { opcodeD6h(); }, [this] { opcodeD7h(); }, [this] { opcodeD8h(); }, [this] { opcodeD9h(); }, [this] { opcodeDAh(); }, [this] { opcodeDBh(); }, [this] { opcodeDCh(); }, [this] { opcodeDDh(); }, [this] { opcodeDEh(); }, [this] { opcodeDFh(); },
                  [this] { opcodeE0h(); }, [this] { opcodeE1h(); }, [this] { opcodeE2h(); }, [this] { opcodeE3h(); }, [this] { opcodeE4h(); }, [this] { opcodeE5h(); }, [this] { opcodeE6h(); }, [this] { opcodeE7h(); }, [this] { opcodeE8h(); }, [this] { opcodeE9h(); }, [this] { opcodeEAh(); }, [this] { opcodeEBh(); }, [this] { opcodeECh(); }, [this] { opcodeEDh(); }, [this] { opcodeEEh(); }, [this] { opcodeEFh(); },
                  [this] { opcodeF0h(); }, [this] { opcodeF1h(); }, [this] { opcodeF2h(); }, [this] { opcodeF3h(); }, [this] { opcodeF4h(); }, [this] { opcodeF5h(); }, [this] { opcodeF6h(); }, [this] { opcodeF7h(); }, [this] { opcodeF8h(); }, [this] { opcodeF9h(); }, [this] { opcodeFAh(); }, [this] { opcodeFBh(); }, [this] { opcodeFCh(); }, [this] { opcodeFDh(); }, [this] { opcodeFEh(); }, [this] { opcodeFFh(); }})
, m_cyclesToWaste(0)
, m_registers({})
{
    resetRegisters();
}

const gbtest::LR35902::LR35902Registers &gbtest::LR35902::getRegisters() const
{
    return m_registers;
}

void gbtest::LR35902::tick()
{
    // Decrement cycles to waste if needed
    if (m_cyclesToWaste > 0)
        --m_cyclesToWaste;

    if (m_cyclesToWaste == 0)
    {
        // Execute current instruction
        const uint8_t opcode = fetch();
        try
        {
            m_opcodeLookup[opcode]();
        } catch (const std::runtime_error &e)
        {
            std::cerr << std::hex << "PC = 0x" << m_registers.pc << "; Opcode = 0x" << (int)opcode << std::endl
                << "Caught exception: " << e.what() << std::endl;
        }
    }
}

void gbtest::LR35902::resetRegisters()
{
    m_registers.af = 0;
    m_registers.bc = 0;
    m_registers.de = 0;
    m_registers.hl = 0;
    m_registers.sp = 0;
    m_registers.pc = 0;
}

uint8_t gbtest::LR35902::fetch()
{
    return m_bus.read(m_registers.pc++);
}

// NOP
void gbtest::LR35902::opcode00h()
{
    m_cyclesToWaste = 4;
}

// LD BC, d16
void gbtest::LR35902::opcode01h()
{
    m_registers.c = fetch();
    m_registers.b = fetch();
    m_cyclesToWaste = 12;
}

// LD (BC), A
void gbtest::LR35902::opcode02h()
{
    m_bus.write(m_registers.bc, m_registers.a);
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode03h()
{
    throw std::runtime_error("Opcode not implemented!");
}

// INC B
void gbtest::LR35902::opcode04h()
{
    ++m_registers.b;

    m_registers.f.z = m_registers.b == 0;
    m_registers.f.n = 0;
    m_registers.f.h = m_registers.b == 0x10;

    m_cyclesToWaste = 4;
}

// DEC B
void gbtest::LR35902::opcode05h()
{
    --m_registers.b;

    m_registers.f.z = m_registers.b == 0;
    m_registers.f.n = 1;
    m_registers.f.h = m_registers.b == 0xF;

    m_cyclesToWaste = 4;
}

// LD B, d8
void gbtest::LR35902::opcode06h()
{
    m_registers.b = fetch();
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode07h()
{
    throw std::runtime_error("Opcode not implemented!");
}

// LD (a16), SP
void gbtest::LR35902::opcode08h()
{
    uint16_t addr = fetch() | (fetch() << 8);
    m_bus.write(addr, m_registers.sp);
    m_bus.write(addr + 1, m_registers.sp >> 8);

    m_cyclesToWaste = 20;
}

void gbtest::LR35902::opcode09h()
{
    throw std::runtime_error("Opcode not implemented!");
}

// LD A, (BC)
void gbtest::LR35902::opcode0Ah()
{
    m_registers.a = m_bus.read(m_registers.bc);
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode0Bh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode0Ch()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode0Dh()
{
    throw std::runtime_error("Opcode not implemented!");
}

// LD C, d8
void gbtest::LR35902::opcode0Eh()
{
    m_registers.c = fetch();
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode0Fh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode10h()
{
    throw std::runtime_error("Opcode not implemented!");
}

// LD DE, d16
void gbtest::LR35902::opcode11h()
{
    m_registers.e = fetch();
    m_registers.d = fetch();
    m_cyclesToWaste = 12;
}

// LD (DE), A
void gbtest::LR35902::opcode12h()
{
    m_bus.write(m_registers.de, m_registers.a);
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode13h()
{
    throw std::runtime_error("Opcode not implemented!");
}

// INC D
void gbtest::LR35902::opcode14h()
{
    ++m_registers.d;

    m_registers.f.z = m_registers.d == 0;
    m_registers.f.n = 0;
    m_registers.f.h = m_registers.d == 0x10;

    m_cyclesToWaste = 4;
}

// DEC D
void gbtest::LR35902::opcode15h()
{
    --m_registers.d;

    m_registers.f.z = m_registers.d == 0;
    m_registers.f.n = 1;
    m_registers.f.h = m_registers.d == 0xF;

    m_cyclesToWaste = 4;
}

// LD D, d8
void gbtest::LR35902::opcode16h()
{
    m_registers.d = fetch();
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode17h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode18h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode19h()
{
    throw std::runtime_error("Opcode not implemented!");
}

// LD A, (DE)
void gbtest::LR35902::opcode1Ah()
{
    m_registers.a = m_bus.read(m_registers.de);
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode1Bh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode1Ch()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode1Dh()
{
    throw std::runtime_error("Opcode not implemented!");
}

// LD E, d8
void gbtest::LR35902::opcode1Eh()
{
    m_registers.e = fetch();
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode1Fh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode20h()
{
    throw std::runtime_error("Opcode not implemented!");
}

// LD HL, d16
void gbtest::LR35902::opcode21h()
{
    m_registers.l = fetch();
    m_registers.h = fetch();
    m_cyclesToWaste = 12;
}

// LD (HL+), A
void gbtest::LR35902::opcode22h()
{
    m_bus.write(m_registers.hl++, m_registers.a);
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode23h()
{
    throw std::runtime_error("Opcode not implemented!");
}

// INC H
void gbtest::LR35902::opcode24h()
{
    ++m_registers.h;

    m_registers.f.z = m_registers.h == 0;
    m_registers.f.n = 0;
    m_registers.f.h = m_registers.h == 0x10;

    m_cyclesToWaste = 4;
}

// DEC H
void gbtest::LR35902::opcode25h()
{
    --m_registers.h;

    m_registers.f.z = m_registers.h == 0;
    m_registers.f.n = 1;
    m_registers.f.h = m_registers.h == 0xF;

    m_cyclesToWaste = 4;
}

// LD H, d8
void gbtest::LR35902::opcode26h()
{
    m_registers.h = fetch();
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode27h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode28h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode29h()
{
    throw std::runtime_error("Opcode not implemented!");
}

// LD A, (HL+)
void gbtest::LR35902::opcode2Ah()
{
    m_registers.a = m_bus.read(m_registers.hl++);
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode2Bh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode2Ch()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode2Dh()
{
    throw std::runtime_error("Opcode not implemented!");
}

// LD L, d8
void gbtest::LR35902::opcode2Eh()
{
    m_registers.l = fetch();
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode2Fh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode30h()
{
    throw std::runtime_error("Opcode not implemented!");
}

// LD SP, d16
void gbtest::LR35902::opcode31h()
{
    m_registers.sp = fetch() | (fetch() << 8);
    m_cyclesToWaste = 12;
}

// LD (HL-), A
void gbtest::LR35902::opcode32h()
{
    m_bus.write(m_registers.hl--, m_registers.a);
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode33h()
{
    throw std::runtime_error("Opcode not implemented!");
}

// INC (HL)
void gbtest::LR35902::opcode34h()
{
    const uint8_t val = m_bus.read(m_registers.hl) + 1;
    m_bus.write(m_registers.hl, val);

    m_registers.f.z = val == 0;
    m_registers.f.n = 0;
    m_registers.f.h = val == 0x10;

    m_cyclesToWaste = 12;
}

// DEC (HL)
void gbtest::LR35902::opcode35h()
{
    const uint8_t val = m_bus.read(m_registers.hl) - 1;
    m_bus.write(m_registers.hl, val);

    m_registers.f.z = val == 0;
    m_registers.f.n = 1;
    m_registers.f.h = val == 0xF;

    m_cyclesToWaste = 12;
}

// LD (HL), d8
void gbtest::LR35902::opcode36h()
{
    m_bus.write(m_registers.hl, fetch());
    m_cyclesToWaste = 12;
}

void gbtest::LR35902::opcode37h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode38h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode39h()
{
    throw std::runtime_error("Opcode not implemented!");
}

// LD A, (HL-)
void gbtest::LR35902::opcode3Ah()
{
    m_registers.a = m_bus.read(m_registers.hl--);
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode3Bh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode3Ch()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode3Dh()
{
    throw std::runtime_error("Opcode not implemented!");
}

// LD A, d8
void gbtest::LR35902::opcode3Eh()
{
    m_registers.a = fetch();
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode3Fh()
{
    throw std::runtime_error("Opcode not implemented!");
}

// LD B, B
void gbtest::LR35902::opcode40h()
{
    m_registers.b = m_registers.b;
    m_cyclesToWaste = 4;
}

// LD B, C
void gbtest::LR35902::opcode41h()
{
    m_registers.b = m_registers.c;
    m_cyclesToWaste = 4;
}

// LD B, D
void gbtest::LR35902::opcode42h()
{
    m_registers.b = m_registers.d;
    m_cyclesToWaste = 4;
}

// LD B, E
void gbtest::LR35902::opcode43h()
{
    m_registers.b = m_registers.e;
    m_cyclesToWaste = 4;
}

// LD B, H
void gbtest::LR35902::opcode44h()
{
    m_registers.b = m_registers.h;
    m_cyclesToWaste = 4;
}

// LD B, L
void gbtest::LR35902::opcode45h()
{
    m_registers.b = m_registers.l;
    m_cyclesToWaste = 4;
}

// LD B, (HL)
void gbtest::LR35902::opcode46h()
{
    m_registers.b = m_bus.read(m_registers.hl);
    m_cyclesToWaste = 8;
}

// LD B, A
void gbtest::LR35902::opcode47h()
{
    m_registers.b = m_registers.a;
    m_cyclesToWaste = 4;
}

// LD C, B
void gbtest::LR35902::opcode48h()
{
    m_registers.c = m_registers.b;
    m_cyclesToWaste = 4;
}

// LD C, C
void gbtest::LR35902::opcode49h()
{
    m_registers.c = m_registers.c;
    m_cyclesToWaste = 4;
}

// LD C, D
void gbtest::LR35902::opcode4Ah()
{
    m_registers.c = m_registers.d;
    m_cyclesToWaste = 4;
}

// LD C, E
void gbtest::LR35902::opcode4Bh()
{
    m_registers.c = m_registers.e;
    m_cyclesToWaste = 4;
}

// LD C, H
void gbtest::LR35902::opcode4Ch()
{
    m_registers.c = m_registers.h;
    m_cyclesToWaste = 4;
}

// LD C, L
void gbtest::LR35902::opcode4Dh()
{
    m_registers.c = m_registers.l;
    m_cyclesToWaste = 4;
}

// LD C, (HL)
void gbtest::LR35902::opcode4Eh()
{
    m_registers.c = m_bus.read(m_registers.hl);
    m_cyclesToWaste = 8;
}

// LD C, A
void gbtest::LR35902::opcode4Fh()
{
    m_registers.c = m_registers.a;
    m_cyclesToWaste = 4;
}

// LD D, B
void gbtest::LR35902::opcode50h()
{
    m_registers.d = m_registers.b;
    m_cyclesToWaste = 4;
}

// LD D, C
void gbtest::LR35902::opcode51h()
{
    m_registers.d = m_registers.c;
    m_cyclesToWaste = 4;
}

// LD D, D
void gbtest::LR35902::opcode52h()
{
    m_registers.d = m_registers.d;
    m_cyclesToWaste = 4;
}

// LD D, E
void gbtest::LR35902::opcode53h()
{
    m_registers.d = m_registers.e;
    m_cyclesToWaste = 4;
}

// LD D, H
void gbtest::LR35902::opcode54h()
{
    m_registers.d = m_registers.h;
    m_cyclesToWaste = 4;
}

// LD D, L
void gbtest::LR35902::opcode55h()
{
    m_registers.d = m_registers.l;
    m_cyclesToWaste = 4;
}

// LD D, (HL)
void gbtest::LR35902::opcode56h()
{
    m_registers.d = m_bus.read(m_registers.hl);
    m_cyclesToWaste = 8;
}

// LD D, A
void gbtest::LR35902::opcode57h()
{
    m_registers.d = m_registers.a;
    m_cyclesToWaste = 4;
}

// LD E, B
void gbtest::LR35902::opcode58h()
{
    m_registers.e = m_registers.b;
    m_cyclesToWaste = 4;
}

// LD E, C
void gbtest::LR35902::opcode59h()
{
    m_registers.e = m_registers.c;
    m_cyclesToWaste = 4;
}

// LD E, D
void gbtest::LR35902::opcode5Ah()
{
    m_registers.e = m_registers.d;
    m_cyclesToWaste = 4;
}

// LD E, E
void gbtest::LR35902::opcode5Bh()
{
    m_registers.e = m_registers.e;
    m_cyclesToWaste = 4;
}

// LD E, H
void gbtest::LR35902::opcode5Ch()
{
    m_registers.e = m_registers.h;
    m_cyclesToWaste = 4;
}

// LD E, L
void gbtest::LR35902::opcode5Dh()
{
    m_registers.e = m_registers.l;
    m_cyclesToWaste = 4;
}

// LD E, (HL)
void gbtest::LR35902::opcode5Eh()
{
    m_registers.e = m_bus.read(m_registers.hl);
    m_cyclesToWaste = 8;
}

// LD E, A
void gbtest::LR35902::opcode5Fh()
{
    m_registers.e = m_registers.a;
    m_cyclesToWaste = 4;
}

// LD H, B
void gbtest::LR35902::opcode60h()
{
    m_registers.h = m_registers.b;
    m_cyclesToWaste = 4;
}

// LD H, C
void gbtest::LR35902::opcode61h()
{
    m_registers.h = m_registers.c;
    m_cyclesToWaste = 4;
}

// LD H, D
void gbtest::LR35902::opcode62h()
{
    m_registers.h = m_registers.d;
    m_cyclesToWaste = 4;
}

// LD H, E
void gbtest::LR35902::opcode63h()
{
    m_registers.h = m_registers.e;
    m_cyclesToWaste = 4;
}

// LD H, H
void gbtest::LR35902::opcode64h()
{
    m_registers.h = m_registers.h;
    m_cyclesToWaste = 4;
}

// LD H, L
void gbtest::LR35902::opcode65h()
{
    m_registers.h = m_registers.l;
    m_cyclesToWaste = 4;
}

// LD H, (HL)
void gbtest::LR35902::opcode66h()
{
    m_registers.h = m_bus.read(m_registers.hl);
    m_cyclesToWaste = 8;
}

// LD H, A
void gbtest::LR35902::opcode67h()
{
    m_registers.h = m_registers.a;
    m_cyclesToWaste = 4;
}

// LD L, B
void gbtest::LR35902::opcode68h()
{
    m_registers.l = m_registers.b;
    m_cyclesToWaste = 4;
}

// LD L, C
void gbtest::LR35902::opcode69h()
{
    m_registers.l = m_registers.c;
    m_cyclesToWaste = 4;
}

// LD L, D
void gbtest::LR35902::opcode6Ah()
{
    m_registers.l = m_registers.d;
    m_cyclesToWaste = 4;
}

// LD L, E
void gbtest::LR35902::opcode6Bh()
{
    m_registers.l = m_registers.e;
    m_cyclesToWaste = 4;
}

// LD L, H
void gbtest::LR35902::opcode6Ch()
{
    m_registers.l = m_registers.h;
    m_cyclesToWaste = 4;
}

// LD L, L
void gbtest::LR35902::opcode6Dh()
{
    m_registers.l = m_registers.l;
    m_cyclesToWaste = 4;
}

// LD L, (HL)
void gbtest::LR35902::opcode6Eh()
{
    m_registers.l = m_bus.read(m_registers.hl);
    m_cyclesToWaste = 4;
}

// LD L, A
void gbtest::LR35902::opcode6Fh()
{
    m_registers.l = m_registers.a;
    m_cyclesToWaste = 4;
}

// LD (HL), B
void gbtest::LR35902::opcode70h()
{
    m_bus.write(m_registers.hl, m_registers.b);
    m_cyclesToWaste = 8;
}

// LD (HL), C
void gbtest::LR35902::opcode71h()
{
    m_bus.write(m_registers.hl, m_registers.c);
    m_cyclesToWaste = 8;
}

// LD (HL), D
void gbtest::LR35902::opcode72h()
{
    m_bus.write(m_registers.hl, m_registers.d);
    m_cyclesToWaste = 8;
}

// LD (HL), E
void gbtest::LR35902::opcode73h()
{
    m_bus.write(m_registers.hl, m_registers.e);
    m_cyclesToWaste = 8;
}

// LD (HL), H
void gbtest::LR35902::opcode74h()
{
    m_bus.write(m_registers.hl, m_registers.h);
    m_cyclesToWaste = 8;
}

// LD (HL), L
void gbtest::LR35902::opcode75h()
{
    m_bus.write(m_registers.hl, m_registers.l);
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode76h()
{
    throw std::runtime_error("Opcode not implemented!");
}

// LD (HL), A
void gbtest::LR35902::opcode77h()
{
    m_bus.write(m_registers.hl, m_registers.a);
    m_cyclesToWaste = 8;
}

// LD A, B
void gbtest::LR35902::opcode78h()
{
    m_registers.a = m_registers.b;
    m_cyclesToWaste = 4;
}

// LD A, C
void gbtest::LR35902::opcode79h()
{
    m_registers.a = m_registers.c;
    m_cyclesToWaste = 4;
}

// LD A, D
void gbtest::LR35902::opcode7Ah()
{
    m_registers.a = m_registers.d;
    m_cyclesToWaste = 4;
}

// LD A, E
void gbtest::LR35902::opcode7Bh()
{
    m_registers.a = m_registers.e;
    m_cyclesToWaste = 4;
}

// LD A, H
void gbtest::LR35902::opcode7Ch()
{
    m_registers.a = m_registers.h;
    m_cyclesToWaste = 4;
}

// LD A, L
void gbtest::LR35902::opcode7Dh()
{
    m_registers.a = m_registers.l;
    m_cyclesToWaste = 4;
}

// LD A, (HL)
void gbtest::LR35902::opcode7Eh()
{
    m_registers.a = m_bus.read(m_registers.hl);
    m_cyclesToWaste = 8;
}

// LD A, A
void gbtest::LR35902::opcode7Fh()
{
    m_registers.a = m_registers.a;
    m_cyclesToWaste = 4;
}

void gbtest::LR35902::opcode80h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode81h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode82h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode83h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode84h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode85h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode86h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode87h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode88h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode89h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode8Ah()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode8Bh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode8Ch()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode8Dh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode8Eh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode8Fh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode90h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode91h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode92h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode93h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode94h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode95h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode96h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode97h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode98h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode99h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode9Ah()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode9Bh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode9Ch()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode9Dh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode9Eh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcode9Fh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeA0h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeA1h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeA2h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeA3h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeA4h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeA5h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeA6h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeA7h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeA8h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeA9h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeAAh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeABh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeACh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeADh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeAEh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeAFh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeB0h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeB1h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeB2h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeB3h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeB4h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeB5h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeB6h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeB7h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeB8h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeB9h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeBAh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeBBh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeBCh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeBDh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeBEh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeBFh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeC0h()
{
    throw std::runtime_error("Opcode not implemented!");
}

// POP BC
void gbtest::LR35902::opcodeC1h()
{
    m_registers.bc = m_bus.read(m_registers.sp++) | (m_bus.read(m_registers.sp++) << 8);
    m_cyclesToWaste = 12;
}

void gbtest::LR35902::opcodeC2h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeC3h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeC4h()
{
    throw std::runtime_error("Opcode not implemented!");
}

// PUSH BC
void gbtest::LR35902::opcodeC5h()
{
    m_bus.write(--m_registers.sp, m_registers.b);
    m_bus.write(--m_registers.sp, m_registers.c);

    m_cyclesToWaste = 16;
}

void gbtest::LR35902::opcodeC6h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeC7h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeC8h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeC9h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeCAh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeCBh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeCCh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeCDh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeCEh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeCFh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeD0h()
{
    throw std::runtime_error("Opcode not implemented!");
}

// POP DE
void gbtest::LR35902::opcodeD1h()
{
    m_registers.de = m_bus.read(m_registers.sp++) | (m_bus.read(m_registers.sp++) << 8);
    m_cyclesToWaste = 12;
}

void gbtest::LR35902::opcodeD2h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeD3h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeD4h()
{
    throw std::runtime_error("Opcode not implemented!");
}

// PUSH DE
void gbtest::LR35902::opcodeD5h()
{
    m_bus.write(--m_registers.sp, m_registers.d);
    m_bus.write(--m_registers.sp, m_registers.e);

    m_cyclesToWaste = 16;
}

void gbtest::LR35902::opcodeD6h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeD7h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeD8h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeD9h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeDAh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeDBh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeDCh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeDDh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeDEh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeDFh()
{
    throw std::runtime_error("Opcode not implemented!");
}

// LDH (a8), A
void gbtest::LR35902::opcodeE0h()
{
    m_bus.write(0xFF00 | fetch(), m_registers.a);
    m_cyclesToWaste = 12;
}

// POP HL
void gbtest::LR35902::opcodeE1h()
{
    m_registers.hl = m_bus.read(m_registers.sp++) | (m_bus.read(m_registers.sp++) << 8);
    m_cyclesToWaste = 12;
}

// LD (C), A
void gbtest::LR35902::opcodeE2h()
{
    m_bus.write(m_registers.c, m_registers.a);
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcodeE3h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeE4h()
{
    throw std::runtime_error("Opcode not implemented!");
}

// PUSH HL
void gbtest::LR35902::opcodeE5h()
{
    m_bus.write(--m_registers.sp, m_registers.h);
    m_bus.write(--m_registers.sp, m_registers.l);

    m_cyclesToWaste = 16;
}

void gbtest::LR35902::opcodeE6h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeE7h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeE8h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeE9h()
{
    throw std::runtime_error("Opcode not implemented!");
}

// LD (a16), A
void gbtest::LR35902::opcodeEAh()
{
    m_bus.write(fetch() | (fetch() << 8), m_registers.a);
    m_cyclesToWaste = 16;
}

void gbtest::LR35902::opcodeEBh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeECh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeEDh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeEEh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeEFh()
{
    throw std::runtime_error("Opcode not implemented!");
}

// LDH A, (a8)
void gbtest::LR35902::opcodeF0h()
{
    m_registers.a = m_bus.read(0xFF00 | fetch());
    m_cyclesToWaste = 12;
}

// POP AF
void gbtest::LR35902::opcodeF1h()
{
    m_registers.af = m_bus.read(m_registers.sp++) | (m_bus.read(m_registers.sp++) << 8);
    m_cyclesToWaste = 12;
}

// LD A, (C)
void gbtest::LR35902::opcodeF2h()
{
    m_registers.a = m_bus.read(m_registers.c);
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcodeF3h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeF4h()
{
    throw std::runtime_error("Opcode not implemented!");
}

// PUSH AF
void gbtest::LR35902::opcodeF5h()
{
    m_bus.write(--m_registers.sp, m_registers.af >> 8);
    m_bus.write(--m_registers.sp, m_registers.af);

    m_cyclesToWaste = 16;
}

void gbtest::LR35902::opcodeF6h()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeF7h()
{
    throw std::runtime_error("Opcode not implemented!");
}

// LD HL, SP + r8
void gbtest::LR35902::opcodeF8h()
{
    auto a = (int8_t)fetch();
    m_registers.hl = m_registers.sp + a;

    m_registers.f.z = 0;
    m_registers.f.n = 0;
    m_registers.f.h = (((m_registers.sp & 0xF) + (a & 0xF)) & 0x10) == 0x10;
    m_registers.f.c = (((m_registers.sp & 0xFF) + (a & 0xFF)) & 0x100) == 0x100;

    m_cyclesToWaste = 12;
}

// LD SP, HL
void gbtest::LR35902::opcodeF9h()
{
    m_registers.sp = m_registers.hl;
    m_cyclesToWaste = 8;
}

// LD A, (a16)
void gbtest::LR35902::opcodeFAh()
{
    m_registers.a = m_bus.read(fetch() | (fetch() << 8));
    m_cyclesToWaste = 16;
}

void gbtest::LR35902::opcodeFBh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeFCh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeFDh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeFEh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeFFh()
{
    throw std::runtime_error("Opcode not implemented!");
}
