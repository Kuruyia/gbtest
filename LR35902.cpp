#include "LR35902.h"

gbtest::LR35902::LR35902(Bus &bus)
: m_bus(bus)
, m_cyclesToWaste(0)
, m_registers({})
{
    resetRegisters();
}

const gbtest::LR35902::LR35902Registers &gbtest::LR35902::getRegisters() const
{
    return m_registers;
}

void gbtest::LR35902::processOpcode(const uint16_t &opcode)
{

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

void gbtest::LR35902::opcode01h()
{

}

// LD (BC), A
void gbtest::LR35902::opcode02h()
{
    m_bus.write(m_registers.bc, m_registers.a);
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode03h()
{

}

void gbtest::LR35902::opcode04h()
{

}

void gbtest::LR35902::opcode05h()
{

}

// LD B, d8
void gbtest::LR35902::opcode06h()
{
    m_registers.b = fetch();
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode07h()
{

}

void gbtest::LR35902::opcode08h()
{

}

void gbtest::LR35902::opcode09h()
{

}

// LD A, (BC)
void gbtest::LR35902::opcode0Ah()
{
    m_registers.a = m_bus.read(m_registers.bc);
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode0Bh()
{

}

void gbtest::LR35902::opcode0Ch()
{

}

void gbtest::LR35902::opcode0Dh()
{

}

// LD C, d8
void gbtest::LR35902::opcode0Eh()
{
    m_registers.c = fetch();
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode0Fh()
{

}

void gbtest::LR35902::opcode10h()
{

}

void gbtest::LR35902::opcode11h()
{

}

// LD (DE), A
void gbtest::LR35902::opcode12h()
{
    m_bus.write(m_registers.de, m_registers.a);
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode13h()
{

}

void gbtest::LR35902::opcode14h()
{

}

void gbtest::LR35902::opcode15h()
{

}

// LD D, d8
void gbtest::LR35902::opcode16h()
{
    m_registers.d = fetch();
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode17h()
{

}

void gbtest::LR35902::opcode18h()
{

}

void gbtest::LR35902::opcode19h()
{

}

// LD A, (DE)
void gbtest::LR35902::opcode1Ah()
{
    m_registers.a = m_bus.read(m_registers.de);
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode1Bh()
{

}

void gbtest::LR35902::opcode1Ch()
{

}

void gbtest::LR35902::opcode1Dh()
{

}

// LD E, d8
void gbtest::LR35902::opcode1Eh()
{
    m_registers.e = fetch();
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode1Fh()
{

}

void gbtest::LR35902::opcode20h()
{

}

void gbtest::LR35902::opcode21h()
{

}

// LD (HL+), A
void gbtest::LR35902::opcode22h()
{
    m_bus.write(m_registers.hl++, m_registers.a);
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode23h()
{

}

void gbtest::LR35902::opcode24h()
{

}

void gbtest::LR35902::opcode25h()
{

}

// LD H, d8
void gbtest::LR35902::opcode26h()
{
    m_registers.h = fetch();
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode27h()
{

}

void gbtest::LR35902::opcode28h()
{

}

void gbtest::LR35902::opcode29h()
{

}

// LD A, (HL+)
void gbtest::LR35902::opcode2Ah()
{
    m_registers.a = m_bus.read(m_registers.hl++);
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode2Bh()
{

}

void gbtest::LR35902::opcode2Ch()
{

}

void gbtest::LR35902::opcode2Dh()
{

}

// LD L, d8
void gbtest::LR35902::opcode2Eh()
{
    m_registers.l = fetch();
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode2Fh()
{

}

void gbtest::LR35902::opcode30h()
{

}

void gbtest::LR35902::opcode31h()
{

}

// LD (HL-), A
void gbtest::LR35902::opcode32h()
{
    m_bus.write(m_registers.hl--, m_registers.a);
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode33h()
{

}

void gbtest::LR35902::opcode34h()
{

}

void gbtest::LR35902::opcode35h()
{

}

// LD (HL), d8
void gbtest::LR35902::opcode36h()
{
    m_bus.write(m_registers.hl, fetch());
    m_cyclesToWaste = 12;
}

void gbtest::LR35902::opcode37h()
{

}

void gbtest::LR35902::opcode38h()
{

}

void gbtest::LR35902::opcode39h()
{

}

// LD A, (HL-)
void gbtest::LR35902::opcode3Ah()
{
    m_registers.a = m_bus.read(m_registers.hl--);
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode3Bh()
{

}

void gbtest::LR35902::opcode3Ch()
{

}

void gbtest::LR35902::opcode3Dh()
{

}

// LD A, d8
void gbtest::LR35902::opcode3Eh()
{
    m_registers.a = fetch();
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcode3Fh()
{

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

}

void gbtest::LR35902::opcode81h()
{

}

void gbtest::LR35902::opcode82h()
{

}

void gbtest::LR35902::opcode83h()
{

}

void gbtest::LR35902::opcode84h()
{

}

void gbtest::LR35902::opcode85h()
{

}

void gbtest::LR35902::opcode86h()
{

}

void gbtest::LR35902::opcode87h()
{

}

void gbtest::LR35902::opcode88h()
{

}

void gbtest::LR35902::opcode89h()
{

}

void gbtest::LR35902::opcode8Ah()
{

}

void gbtest::LR35902::opcode8Bh()
{

}

void gbtest::LR35902::opcode8Ch()
{

}

void gbtest::LR35902::opcode8Dh()
{

}

void gbtest::LR35902::opcode8Eh()
{

}

void gbtest::LR35902::opcode8Fh()
{

}

void gbtest::LR35902::opcode90h()
{

}

void gbtest::LR35902::opcode91h()
{

}

void gbtest::LR35902::opcode92h()
{

}

void gbtest::LR35902::opcode93h()
{

}

void gbtest::LR35902::opcode94h()
{

}

void gbtest::LR35902::opcode95h()
{

}

void gbtest::LR35902::opcode96h()
{

}

void gbtest::LR35902::opcode97h()
{

}

void gbtest::LR35902::opcode98h()
{

}

void gbtest::LR35902::opcode99h()
{

}

void gbtest::LR35902::opcode9Ah()
{

}

void gbtest::LR35902::opcode9Bh()
{

}

void gbtest::LR35902::opcode9Ch()
{

}

void gbtest::LR35902::opcode9Dh()
{

}

void gbtest::LR35902::opcode9Eh()
{

}

void gbtest::LR35902::opcode9Fh()
{

}

void gbtest::LR35902::opcodeA0h()
{

}

void gbtest::LR35902::opcodeA1h()
{

}

void gbtest::LR35902::opcodeA2h()
{

}

void gbtest::LR35902::opcodeA3h()
{

}

void gbtest::LR35902::opcodeA4h()
{

}

void gbtest::LR35902::opcodeA5h()
{

}

void gbtest::LR35902::opcodeA6h()
{

}

void gbtest::LR35902::opcodeA7h()
{

}

void gbtest::LR35902::opcodeA8h()
{

}

void gbtest::LR35902::opcodeA9h()
{

}

void gbtest::LR35902::opcodeAAh()
{

}

void gbtest::LR35902::opcodeABh()
{

}

void gbtest::LR35902::opcodeACh()
{

}

void gbtest::LR35902::opcodeADh()
{

}

void gbtest::LR35902::opcodeAEh()
{

}

void gbtest::LR35902::opcodeAFh()
{

}

void gbtest::LR35902::opcodeB0h()
{

}

void gbtest::LR35902::opcodeB1h()
{

}

void gbtest::LR35902::opcodeB2h()
{

}

void gbtest::LR35902::opcodeB3h()
{

}

void gbtest::LR35902::opcodeB4h()
{

}

void gbtest::LR35902::opcodeB5h()
{

}

void gbtest::LR35902::opcodeB6h()
{

}

void gbtest::LR35902::opcodeB7h()
{

}

void gbtest::LR35902::opcodeB8h()
{

}

void gbtest::LR35902::opcodeB9h()
{

}

void gbtest::LR35902::opcodeBAh()
{

}

void gbtest::LR35902::opcodeBBh()
{

}

void gbtest::LR35902::opcodeBCh()
{

}

void gbtest::LR35902::opcodeBDh()
{

}

void gbtest::LR35902::opcodeBEh()
{

}

void gbtest::LR35902::opcodeBFh()
{

}

void gbtest::LR35902::opcodeC0h()
{

}

void gbtest::LR35902::opcodeC1h()
{

}

void gbtest::LR35902::opcodeC2h()
{

}

void gbtest::LR35902::opcodeC3h()
{

}

void gbtest::LR35902::opcodeC4h()
{

}

void gbtest::LR35902::opcodeC5h()
{

}

void gbtest::LR35902::opcodeC6h()
{

}

void gbtest::LR35902::opcodeC7h()
{

}

void gbtest::LR35902::opcodeC8h()
{

}

void gbtest::LR35902::opcodeC9h()
{

}

void gbtest::LR35902::opcodeCAh()
{

}

void gbtest::LR35902::opcodeCBh()
{

}

void gbtest::LR35902::opcodeCCh()
{

}

void gbtest::LR35902::opcodeCDh()
{

}

void gbtest::LR35902::opcodeCEh()
{

}

void gbtest::LR35902::opcodeCFh()
{

}

void gbtest::LR35902::opcodeD0h()
{

}

void gbtest::LR35902::opcodeD1h()
{

}

void gbtest::LR35902::opcodeD2h()
{

}

void gbtest::LR35902::opcodeD3h()
{

}

void gbtest::LR35902::opcodeD4h()
{

}

void gbtest::LR35902::opcodeD5h()
{

}

void gbtest::LR35902::opcodeD6h()
{

}

void gbtest::LR35902::opcodeD7h()
{

}

void gbtest::LR35902::opcodeD8h()
{

}

void gbtest::LR35902::opcodeD9h()
{

}

void gbtest::LR35902::opcodeDAh()
{

}

void gbtest::LR35902::opcodeDBh()
{

}

void gbtest::LR35902::opcodeDCh()
{

}

void gbtest::LR35902::opcodeDDh()
{

}

void gbtest::LR35902::opcodeDEh()
{

}

void gbtest::LR35902::opcodeDFh()
{

}

// LDH (a8), A
void gbtest::LR35902::opcodeE0h()
{
    m_bus.write(0xFF00 | fetch(), m_registers.a);
    m_cyclesToWaste = 12;
}

void gbtest::LR35902::opcodeE1h()
{

}

// LD (C), A
void gbtest::LR35902::opcodeE2h()
{
    m_bus.write(m_registers.c, m_registers.a);
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcodeE3h()
{

}

void gbtest::LR35902::opcodeE4h()
{

}

void gbtest::LR35902::opcodeE5h()
{

}

void gbtest::LR35902::opcodeE6h()
{

}

void gbtest::LR35902::opcodeE7h()
{

}

void gbtest::LR35902::opcodeE8h()
{

}

void gbtest::LR35902::opcodeE9h()
{

}

// LD (a16), A
void gbtest::LR35902::opcodeEAh()
{
    m_bus.write(fetch() | (fetch() << 8), m_registers.a);
    m_cyclesToWaste = 16;
}

void gbtest::LR35902::opcodeEBh()
{

}

void gbtest::LR35902::opcodeECh()
{

}

void gbtest::LR35902::opcodeEDh()
{

}

void gbtest::LR35902::opcodeEEh()
{

}

void gbtest::LR35902::opcodeEFh()
{

}

// LDH A, (a8)
void gbtest::LR35902::opcodeF0h()
{
    m_registers.a = m_bus.read(0xFF00 | fetch());
    m_cyclesToWaste = 12;
}

void gbtest::LR35902::opcodeF1h()
{

}

// LD A, (C)
void gbtest::LR35902::opcodeF2h()
{
    m_registers.a = m_bus.read(m_registers.c);
    m_cyclesToWaste = 8;
}

void gbtest::LR35902::opcodeF3h()
{

}

void gbtest::LR35902::opcodeF4h()
{

}

void gbtest::LR35902::opcodeF5h()
{

}

void gbtest::LR35902::opcodeF6h()
{

}

void gbtest::LR35902::opcodeF7h()
{

}

void gbtest::LR35902::opcodeF8h()
{

}

void gbtest::LR35902::opcodeF9h()
{

}

// LD A, (a16)
void gbtest::LR35902::opcodeFAh()
{
    m_registers.a = m_bus.read(fetch() | (fetch() << 8));
    m_cyclesToWaste = 16;
}

void gbtest::LR35902::opcodeFBh()
{

}

void gbtest::LR35902::opcodeFCh()
{

}

void gbtest::LR35902::opcodeFDh()
{

}

void gbtest::LR35902::opcodeFEh()
{

}

void gbtest::LR35902::opcodeFFh()
{

}
