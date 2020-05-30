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

// NOP
void gbtest::LR35902::opcode00h()
{
    m_cyclesToWaste = 4;
}

void gbtest::LR35902::opcode01h()
{

}

void gbtest::LR35902::opcode02h()
{

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

void gbtest::LR35902::opcode06h()
{

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

void gbtest::LR35902::opcodeAh()
{

}

void gbtest::LR35902::opcodeBh()
{

}

void gbtest::LR35902::opcodeCh()
{

}

void gbtest::LR35902::opcodeDh()
{

}

void gbtest::LR35902::opcodeEh()
{

}

void gbtest::LR35902::opcodeFh()
{

}

void gbtest::LR35902::opcode10h()
{

}

void gbtest::LR35902::opcode11h()
{

}

void gbtest::LR35902::opcode12h()
{

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

void gbtest::LR35902::opcode16h()
{

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

void gbtest::LR35902::opcode1Ah()
{

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

void gbtest::LR35902::opcode1Eh()
{

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

void gbtest::LR35902::opcode22h()
{

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

void gbtest::LR35902::opcode26h()
{

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

void gbtest::LR35902::opcode2Ah()
{

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

void gbtest::LR35902::opcode2Eh()
{

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

void gbtest::LR35902::opcode32h()
{

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

void gbtest::LR35902::opcode36h()
{

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

void gbtest::LR35902::opcode3Ah()
{

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

void gbtest::LR35902::opcode3Eh()
{

}

void gbtest::LR35902::opcode3Fh()
{

}

void gbtest::LR35902::opcode40h()
{

}

void gbtest::LR35902::opcode41h()
{

}

void gbtest::LR35902::opcode42h()
{

}

void gbtest::LR35902::opcode43h()
{

}

void gbtest::LR35902::opcode44h()
{

}

void gbtest::LR35902::opcode45h()
{

}

void gbtest::LR35902::opcode46h()
{

}

void gbtest::LR35902::opcode47h()
{

}

void gbtest::LR35902::opcode48h()
{

}

void gbtest::LR35902::opcode49h()
{

}

void gbtest::LR35902::opcode4Ah()
{

}

void gbtest::LR35902::opcode4Bh()
{

}

void gbtest::LR35902::opcode4Ch()
{

}

void gbtest::LR35902::opcode4Dh()
{

}

void gbtest::LR35902::opcode4Eh()
{

}

void gbtest::LR35902::opcode4Fh()
{

}

void gbtest::LR35902::opcode50h()
{

}

void gbtest::LR35902::opcode51h()
{

}

void gbtest::LR35902::opcode52h()
{

}

void gbtest::LR35902::opcode53h()
{

}

void gbtest::LR35902::opcode54h()
{

}

void gbtest::LR35902::opcode55h()
{

}

void gbtest::LR35902::opcode56h()
{

}

void gbtest::LR35902::opcode57h()
{

}

void gbtest::LR35902::opcode58h()
{

}

void gbtest::LR35902::opcode59h()
{

}

void gbtest::LR35902::opcode5Ah()
{

}

void gbtest::LR35902::opcode5Bh()
{

}

void gbtest::LR35902::opcode5Ch()
{

}

void gbtest::LR35902::opcode5Dh()
{

}

void gbtest::LR35902::opcode5Eh()
{

}

void gbtest::LR35902::opcode5Fh()
{

}

void gbtest::LR35902::opcode60h()
{

}

void gbtest::LR35902::opcode61h()
{

}

void gbtest::LR35902::opcode62h()
{

}

void gbtest::LR35902::opcode63h()
{

}

void gbtest::LR35902::opcode64h()
{

}

void gbtest::LR35902::opcode65h()
{

}

void gbtest::LR35902::opcode66h()
{

}

void gbtest::LR35902::opcode67h()
{

}

void gbtest::LR35902::opcode68h()
{

}

void gbtest::LR35902::opcode69h()
{

}

void gbtest::LR35902::opcode6Ah()
{

}

void gbtest::LR35902::opcode6Bh()
{

}

void gbtest::LR35902::opcode6Ch()
{

}

void gbtest::LR35902::opcode6Dh()
{

}

void gbtest::LR35902::opcode6Eh()
{

}

void gbtest::LR35902::opcode6Fh()
{

}

void gbtest::LR35902::opcode70h()
{

}

void gbtest::LR35902::opcode71h()
{

}

void gbtest::LR35902::opcode72h()
{

}

void gbtest::LR35902::opcode73h()
{

}

void gbtest::LR35902::opcode74h()
{

}

void gbtest::LR35902::opcode75h()
{

}

void gbtest::LR35902::opcode76h()
{

}

void gbtest::LR35902::opcode77h()
{

}

void gbtest::LR35902::opcode78h()
{

}

void gbtest::LR35902::opcode79h()
{

}

void gbtest::LR35902::opcode7Ah()
{

}

void gbtest::LR35902::opcode7Bh()
{

}

void gbtest::LR35902::opcode7Ch()
{

}

void gbtest::LR35902::opcode7Dh()
{

}

void gbtest::LR35902::opcode7Eh()
{

}

void gbtest::LR35902::opcode7Fh()
{

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

void gbtest::LR35902::opcodeE0h()
{

}

void gbtest::LR35902::opcodeE1h()
{

}

void gbtest::LR35902::opcodeE2h()
{

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

void gbtest::LR35902::opcodeEAh()
{

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

void gbtest::LR35902::opcodeF0h()
{

}

void gbtest::LR35902::opcodeF1h()
{

}

void gbtest::LR35902::opcodeF2h()
{

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

void gbtest::LR35902::opcodeFAh()
{

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
