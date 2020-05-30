#include "LR35902.h"

gbtest::LR35902::LR35902()
{
    resetRegisters();
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
