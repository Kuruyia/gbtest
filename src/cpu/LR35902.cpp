#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <cassert>

#include "LR35902.h"

gbtest::LR35902::LR35902(Bus& bus)
        : m_bus(bus)
        , m_opcodeLookup(
                {[this] { opcode00h(); }, [this] { opcode01h(); }, [this] { opcode02h(); }, [this] { opcode03h(); },
                 [this] { opcode04h(); }, [this] { opcode05h(); }, [this] { opcode06h(); }, [this] { opcode07h(); },
                 [this] { opcode08h(); }, [this] { opcode09h(); }, [this] { opcode0Ah(); }, [this] { opcode0Bh(); },
                 [this] { opcode0Ch(); }, [this] { opcode0Dh(); }, [this] { opcode0Eh(); }, [this] { opcode0Fh(); },
                 [this] { opcode10h(); }, [this] { opcode11h(); }, [this] { opcode12h(); }, [this] { opcode13h(); },
                 [this] { opcode14h(); }, [this] { opcode15h(); }, [this] { opcode16h(); }, [this] { opcode17h(); },
                 [this] { opcode18h(); }, [this] { opcode19h(); }, [this] { opcode1Ah(); }, [this] { opcode1Bh(); },
                 [this] { opcode1Ch(); }, [this] { opcode1Dh(); }, [this] { opcode1Eh(); }, [this] { opcode1Fh(); },
                 [this] { opcode20h(); }, [this] { opcode21h(); }, [this] { opcode22h(); }, [this] { opcode23h(); },
                 [this] { opcode24h(); }, [this] { opcode25h(); }, [this] { opcode26h(); }, [this] { opcode27h(); },
                 [this] { opcode28h(); }, [this] { opcode29h(); }, [this] { opcode2Ah(); }, [this] { opcode2Bh(); },
                 [this] { opcode2Ch(); }, [this] { opcode2Dh(); }, [this] { opcode2Eh(); }, [this] { opcode2Fh(); },
                 [this] { opcode30h(); }, [this] { opcode31h(); }, [this] { opcode32h(); }, [this] { opcode33h(); },
                 [this] { opcode34h(); }, [this] { opcode35h(); }, [this] { opcode36h(); }, [this] { opcode37h(); },
                 [this] { opcode38h(); }, [this] { opcode39h(); }, [this] { opcode3Ah(); }, [this] { opcode3Bh(); },
                 [this] { opcode3Ch(); }, [this] { opcode3Dh(); }, [this] { opcode3Eh(); }, [this] { opcode3Fh(); },
                 [this] { opcode40h(); }, [this] { opcode41h(); }, [this] { opcode42h(); }, [this] { opcode43h(); },
                 [this] { opcode44h(); }, [this] { opcode45h(); }, [this] { opcode46h(); }, [this] { opcode47h(); },
                 [this] { opcode48h(); }, [this] { opcode49h(); }, [this] { opcode4Ah(); }, [this] { opcode4Bh(); },
                 [this] { opcode4Ch(); }, [this] { opcode4Dh(); }, [this] { opcode4Eh(); }, [this] { opcode4Fh(); },
                 [this] { opcode50h(); }, [this] { opcode51h(); }, [this] { opcode52h(); }, [this] { opcode53h(); },
                 [this] { opcode54h(); }, [this] { opcode55h(); }, [this] { opcode56h(); }, [this] { opcode57h(); },
                 [this] { opcode58h(); }, [this] { opcode59h(); }, [this] { opcode5Ah(); }, [this] { opcode5Bh(); },
                 [this] { opcode5Ch(); }, [this] { opcode5Dh(); }, [this] { opcode5Eh(); }, [this] { opcode5Fh(); },
                 [this] { opcode60h(); }, [this] { opcode61h(); }, [this] { opcode62h(); }, [this] { opcode63h(); },
                 [this] { opcode64h(); }, [this] { opcode65h(); }, [this] { opcode66h(); }, [this] { opcode67h(); },
                 [this] { opcode68h(); }, [this] { opcode69h(); }, [this] { opcode6Ah(); }, [this] { opcode6Bh(); },
                 [this] { opcode6Ch(); }, [this] { opcode6Dh(); }, [this] { opcode6Eh(); }, [this] { opcode6Fh(); },
                 [this] { opcode70h(); }, [this] { opcode71h(); }, [this] { opcode72h(); }, [this] { opcode73h(); },
                 [this] { opcode74h(); }, [this] { opcode75h(); }, [this] { opcode76h(); }, [this] { opcode77h(); },
                 [this] { opcode78h(); }, [this] { opcode79h(); }, [this] { opcode7Ah(); }, [this] { opcode7Bh(); },
                 [this] { opcode7Ch(); }, [this] { opcode7Dh(); }, [this] { opcode7Eh(); }, [this] { opcode7Fh(); },
                 [this] { opcode80h(); }, [this] { opcode81h(); }, [this] { opcode82h(); }, [this] { opcode83h(); },
                 [this] { opcode84h(); }, [this] { opcode85h(); }, [this] { opcode86h(); }, [this] { opcode87h(); },
                 [this] { opcode88h(); }, [this] { opcode89h(); }, [this] { opcode8Ah(); }, [this] { opcode8Bh(); },
                 [this] { opcode8Ch(); }, [this] { opcode8Dh(); }, [this] { opcode8Eh(); }, [this] { opcode8Fh(); },
                 [this] { opcode90h(); }, [this] { opcode91h(); }, [this] { opcode92h(); }, [this] { opcode93h(); },
                 [this] { opcode94h(); }, [this] { opcode95h(); }, [this] { opcode96h(); }, [this] { opcode97h(); },
                 [this] { opcode98h(); }, [this] { opcode99h(); }, [this] { opcode9Ah(); }, [this] { opcode9Bh(); },
                 [this] { opcode9Ch(); }, [this] { opcode9Dh(); }, [this] { opcode9Eh(); }, [this] { opcode9Fh(); },
                 [this] { opcodeA0h(); }, [this] { opcodeA1h(); }, [this] { opcodeA2h(); }, [this] { opcodeA3h(); },
                 [this] { opcodeA4h(); }, [this] { opcodeA5h(); }, [this] { opcodeA6h(); }, [this] { opcodeA7h(); },
                 [this] { opcodeA8h(); }, [this] { opcodeA9h(); }, [this] { opcodeAAh(); }, [this] { opcodeABh(); },
                 [this] { opcodeACh(); }, [this] { opcodeADh(); }, [this] { opcodeAEh(); }, [this] { opcodeAFh(); },
                 [this] { opcodeB0h(); }, [this] { opcodeB1h(); }, [this] { opcodeB2h(); }, [this] { opcodeB3h(); },
                 [this] { opcodeB4h(); }, [this] { opcodeB5h(); }, [this] { opcodeB6h(); }, [this] { opcodeB7h(); },
                 [this] { opcodeB8h(); }, [this] { opcodeB9h(); }, [this] { opcodeBAh(); }, [this] { opcodeBBh(); },
                 [this] { opcodeBCh(); }, [this] { opcodeBDh(); }, [this] { opcodeBEh(); }, [this] { opcodeBFh(); },
                 [this] { opcodeC0h(); }, [this] { opcodeC1h(); }, [this] { opcodeC2h(); }, [this] { opcodeC3h(); },
                 [this] { opcodeC4h(); }, [this] { opcodeC5h(); }, [this] { opcodeC6h(); }, [this] { opcodeC7h(); },
                 [this] { opcodeC8h(); }, [this] { opcodeC9h(); }, [this] { opcodeCAh(); }, [this] { opcodeCBh(); },
                 [this] { opcodeCCh(); }, [this] { opcodeCDh(); }, [this] { opcodeCEh(); }, [this] { opcodeCFh(); },
                 [this] { opcodeD0h(); }, [this] { opcodeD1h(); }, [this] { opcodeD2h(); }, [this] { opcodeD3h(); },
                 [this] { opcodeD4h(); }, [this] { opcodeD5h(); }, [this] { opcodeD6h(); }, [this] { opcodeD7h(); },
                 [this] { opcodeD8h(); }, [this] { opcodeD9h(); }, [this] { opcodeDAh(); }, [this] { opcodeDBh(); },
                 [this] { opcodeDCh(); }, [this] { opcodeDDh(); }, [this] { opcodeDEh(); }, [this] { opcodeDFh(); },
                 [this] { opcodeE0h(); }, [this] { opcodeE1h(); }, [this] { opcodeE2h(); }, [this] { opcodeE3h(); },
                 [this] { opcodeE4h(); }, [this] { opcodeE5h(); }, [this] { opcodeE6h(); }, [this] { opcodeE7h(); },
                 [this] { opcodeE8h(); }, [this] { opcodeE9h(); }, [this] { opcodeEAh(); }, [this] { opcodeEBh(); },
                 [this] { opcodeECh(); }, [this] { opcodeEDh(); }, [this] { opcodeEEh(); }, [this] { opcodeEFh(); },
                 [this] { opcodeF0h(); }, [this] { opcodeF1h(); }, [this] { opcodeF2h(); }, [this] { opcodeF3h(); },
                 [this] { opcodeF4h(); }, [this] { opcodeF5h(); }, [this] { opcodeF6h(); }, [this] { opcodeF7h(); },
                 [this] { opcodeF8h(); }, [this] { opcodeF9h(); }, [this] { opcodeFAh(); }, [this] { opcodeFBh(); },
                 [this] { opcodeFCh(); }, [this] { opcodeFDh(); }, [this] { opcodeFEh(); }, [this] { opcodeFFh(); }})
        , m_interruptController(bus)
        , m_cyclesToWaste(0)
        , m_halted(false)
        , m_stopped(false)
        , m_tickCounter(0)
{

}

void gbtest::LR35902::setRegisters(const LR35902Registers& registers)
{
    m_registers = registers;
}

const gbtest::LR35902Registers& gbtest::LR35902::getRegisters() const
{
    return m_registers;
}

const gbtest::InterruptController& gbtest::LR35902::getInterruptController() const
{
    return m_interruptController;
}

gbtest::InterruptController& gbtest::LR35902::getInterruptController()
{
    return m_interruptController;
}

void gbtest::LR35902::setHalted(bool halted)
{
    m_halted = halted;
}

const bool& gbtest::LR35902::isHalted() const
{
    return m_halted;
}

void gbtest::LR35902::setStopped(bool stopped)
{
    m_stopped = stopped;
}

const bool& gbtest::LR35902::isStopped() const
{
    return m_stopped;
}

const uint8_t& gbtest::LR35902::getCyclesToWaste() const
{
    return m_cyclesToWaste;
}

const unsigned& gbtest::LR35902::getTickCounter() const
{
    return m_tickCounter;
}

void gbtest::LR35902::tick()
{
    // Tick the interrupt controller
    m_interruptController.tick();

    // Decrement cycles to waste if needed
    if (m_cyclesToWaste > 0) {
        --m_cyclesToWaste;
    }

    if (m_cyclesToWaste == 0) {
        // Execute current instruction
        const uint8_t opcode = fetch();
        try {
            m_opcodeLookup[opcode]();
        }
        catch (const std::runtime_error& e) {
            std::cerr << std::uppercase << std::hex
                      << "PC = 0x" << m_registers.pc << "; Opcode = 0x" << (int) opcode << std::endl
                      << "Caught exception: " << e.what() << std::endl;
        }

        // Handle delayed interrupt enable
        m_interruptController.handleDelayedInterrupt();
    }

    ++m_tickCounter;
}

void gbtest::LR35902::step()
{
    if (m_cyclesToWaste > 0) {
        // Simulate the waste of all cycles
        m_tickCounter += m_cyclesToWaste - 1;
        m_cyclesToWaste = 0;
    }

    // Execute the instruction
    tick();
}

uint8_t gbtest::LR35902::fetch()
{
    return m_bus.read(m_registers.pc++, gbtest::BusRequestSource::CPU);
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
    m_bus.write(m_registers.bc, m_registers.a, gbtest::BusRequestSource::CPU);
    m_cyclesToWaste = 8;
}

// INC BC
void gbtest::LR35902::opcode03h()
{
    ++m_registers.bc;

    m_cyclesToWaste = 8;
}

// INC B
void gbtest::LR35902::opcode04h()
{
    INC_r8(m_registers.b);
}

// DEC B
void gbtest::LR35902::opcode05h()
{
    DEC_r8(m_registers.b);
}

// LD B, d8
void gbtest::LR35902::opcode06h()
{
    m_registers.b = fetch();
    m_cyclesToWaste = 8;
}

// RLCA
void gbtest::LR35902::opcode07h()
{
    m_registers.f.c = (m_registers.a >> 7) & 0x1;

    m_registers.a = (m_registers.a << 1) | m_registers.f.c;

    m_registers.f.z = 0;
    m_registers.f.n = 0;
    m_registers.f.h = 0;

    m_cyclesToWaste = 4;
}

// LD (a16), SP
void gbtest::LR35902::opcode08h()
{
    uint16_t addr = fetch() | (fetch() << 8);
    m_bus.write(addr, m_registers.sp, gbtest::BusRequestSource::CPU);
    m_bus.write(addr + 1, m_registers.sp >> 8, gbtest::BusRequestSource::CPU);

    m_cyclesToWaste = 20;
}

// ADD HL, BC
void gbtest::LR35902::opcode09h()
{
    ADD_HL_r16(m_registers.bc);
}

// LD A, (BC)
void gbtest::LR35902::opcode0Ah()
{
    m_registers.a = m_bus.read(m_registers.bc, gbtest::BusRequestSource::CPU);
    m_cyclesToWaste = 8;
}

// DEC BC
void gbtest::LR35902::opcode0Bh()
{
    --m_registers.bc;

    m_cyclesToWaste = 8;
}

// INC C
void gbtest::LR35902::opcode0Ch()
{
    INC_r8(m_registers.c);
}

// DEC C
void gbtest::LR35902::opcode0Dh()
{
    DEC_r8(m_registers.c);
}

// LD C, d8
void gbtest::LR35902::opcode0Eh()
{
    m_registers.c = fetch();
    m_cyclesToWaste = 8;
}

// RRCA
void gbtest::LR35902::opcode0Fh()
{
    m_registers.f.c = m_registers.a & 0x1;

    m_registers.a = (m_registers.a >> 1) | (m_registers.f.c << 7);

    m_registers.f.z = 0;
    m_registers.f.n = 0;
    m_registers.f.h = 0;

    m_cyclesToWaste = 4;
}

// STOP
void gbtest::LR35902::opcode10h()
{
    // TODO: Implement that
    m_halted = true;
    m_stopped = true;

    m_cyclesToWaste = 4;
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
    m_bus.write(m_registers.de, m_registers.a, gbtest::BusRequestSource::CPU);
    m_cyclesToWaste = 8;
}

// INC DE
void gbtest::LR35902::opcode13h()
{
    ++m_registers.de;

    m_cyclesToWaste = 8;
}

// INC D
void gbtest::LR35902::opcode14h()
{
    INC_r8(m_registers.d);
}

// DEC D
void gbtest::LR35902::opcode15h()
{
    DEC_r8(m_registers.d);
}

// LD D, d8
void gbtest::LR35902::opcode16h()
{
    m_registers.d = fetch();
    m_cyclesToWaste = 8;
}

// RLA
void gbtest::LR35902::opcode17h()
{
    const uint8_t newCarry = (m_registers.a >> 7) & 0x1;

    m_registers.a = (m_registers.a << 1) | m_registers.f.c;

    m_registers.f.z = 0;
    m_registers.f.n = 0;
    m_registers.f.h = 0;
    m_registers.f.c = newCarry;

    m_cyclesToWaste = 4;
}

// JR r8
void gbtest::LR35902::opcode18h()
{
    m_registers.pc += (int8_t) fetch();
    m_cyclesToWaste = 12;
}

// ADD HL, DE
void gbtest::LR35902::opcode19h()
{
    ADD_HL_r16(m_registers.de);
}

// LD A, (DE)
void gbtest::LR35902::opcode1Ah()
{
    m_registers.a = m_bus.read(m_registers.de, gbtest::BusRequestSource::CPU);
    m_cyclesToWaste = 8;
}

// DEC DE
void gbtest::LR35902::opcode1Bh()
{
    --m_registers.de;

    m_cyclesToWaste = 8;
}

// INC E
void gbtest::LR35902::opcode1Ch()
{
    INC_r8(m_registers.e);
}

// DEC E
void gbtest::LR35902::opcode1Dh()
{
    DEC_r8(m_registers.e);
}

// LD E, d8
void gbtest::LR35902::opcode1Eh()
{
    m_registers.e = fetch();
    m_cyclesToWaste = 8;
}

// RRA
void gbtest::LR35902::opcode1Fh()
{
    const uint8_t newCarry = m_registers.a & 0x1;

    m_registers.a = (m_registers.a >> 1) | (m_registers.f.c << 7);

    m_registers.f.z = 0;
    m_registers.f.n = 0;
    m_registers.f.h = 0;
    m_registers.f.c = newCarry;

    m_cyclesToWaste = 4;
}

// JR NZ, r8
void gbtest::LR35902::opcode20h()
{
    const auto val = (int8_t) fetch();

    if (m_registers.f.z) {
        m_cyclesToWaste = 8;
        return;
    }

    m_registers.pc += val;
    m_cyclesToWaste = 12;
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
    m_bus.write(m_registers.hl++, m_registers.a, gbtest::BusRequestSource::CPU);
    m_cyclesToWaste = 8;
}

// INC HL
void gbtest::LR35902::opcode23h()
{
    ++m_registers.hl;

    m_cyclesToWaste = 8;
}

// INC H
void gbtest::LR35902::opcode24h()
{
    INC_r8(m_registers.h);
}

// DEC H
void gbtest::LR35902::opcode25h()
{
    DEC_r8(m_registers.h);
}

// LD H, d8
void gbtest::LR35902::opcode26h()
{
    m_registers.h = fetch();
    m_cyclesToWaste = 8;
}

// DAA
void gbtest::LR35902::opcode27h()
{
    if (m_registers.f.n == 0) {
        // Previous operation was an addition
        if (m_registers.f.c || m_registers.a > 0x99) {
            m_registers.a += 0x60;
            m_registers.f.c = 1;
        }

        if (m_registers.f.h || (m_registers.a & 0x0F) > 0x09) {
            m_registers.a += 0x06;
        }
    }
    else {
        // Previous operation was a subtraction
        if (m_registers.f.c) {
            m_registers.a -= 0x60;
        }

        if (m_registers.f.h) {
            m_registers.a -= 0x06;
        }
    }

    // Set the flags according to the result
    m_registers.f.z = (m_registers.a == 0x00);
    m_registers.f.h = 0;
}

// JR Z, r8
void gbtest::LR35902::opcode28h()
{
    const auto val = (int8_t) fetch();

    if (!m_registers.f.z) {
        m_cyclesToWaste = 8;
        return;
    }

    m_registers.pc += val;
    m_cyclesToWaste = 12;
}

// ADD HL, HL
void gbtest::LR35902::opcode29h()
{
    ADD_HL_r16(m_registers.hl);
}

// LD A, (HL+)
void gbtest::LR35902::opcode2Ah()
{
    m_registers.a = m_bus.read(m_registers.hl++, gbtest::BusRequestSource::CPU);
    m_cyclesToWaste = 8;
}

// DEC HL
void gbtest::LR35902::opcode2Bh()
{
    --m_registers.hl;

    m_cyclesToWaste = 8;
}

// INC L
void gbtest::LR35902::opcode2Ch()
{
    INC_r8(m_registers.l);
}

// DEC L
void gbtest::LR35902::opcode2Dh()
{
    DEC_r8(m_registers.l);
}

// LD L, d8
void gbtest::LR35902::opcode2Eh()
{
    m_registers.l = fetch();
    m_cyclesToWaste = 8;
}

// CPL
void gbtest::LR35902::opcode2Fh()
{
    m_registers.a = ~m_registers.a;

    m_registers.f.n = 1;
    m_registers.f.h = 1;

    m_cyclesToWaste = 4;
}

// JR NC, r8
void gbtest::LR35902::opcode30h()
{
    const auto val = (int8_t) fetch();

    if (m_registers.f.c) {
        m_cyclesToWaste = 8;
        return;
    }

    m_registers.pc += val;
    m_cyclesToWaste = 12;
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
    m_bus.write(m_registers.hl--, m_registers.a, gbtest::BusRequestSource::CPU);
    m_cyclesToWaste = 8;
}

// INC SP
void gbtest::LR35902::opcode33h()
{
    ++m_registers.sp;

    m_cyclesToWaste = 8;
}

// INC (HL)
void gbtest::LR35902::opcode34h()
{
    const uint8_t val = m_bus.read(m_registers.hl, gbtest::BusRequestSource::CPU) + 1;
    m_bus.write(m_registers.hl, val, gbtest::BusRequestSource::CPU);

    m_registers.f.z = val == 0;
    m_registers.f.n = 0;
    m_registers.f.h = (val == 0x00 || val == 0x10);

    m_cyclesToWaste = 12;
}

// DEC (HL)
void gbtest::LR35902::opcode35h()
{
    const uint8_t val = m_bus.read(m_registers.hl, gbtest::BusRequestSource::CPU) - 1;
    m_bus.write(m_registers.hl, val, gbtest::BusRequestSource::CPU);

    m_registers.f.z = val == 0;
    m_registers.f.n = 1;
    m_registers.f.h = val == 0xF;

    m_cyclesToWaste = 12;
}

// LD (HL), d8
void gbtest::LR35902::opcode36h()
{
    m_bus.write(m_registers.hl, fetch(), gbtest::BusRequestSource::CPU);
    m_cyclesToWaste = 12;
}

// SCF
void gbtest::LR35902::opcode37h()
{
    m_registers.f.n = 0;
    m_registers.f.h = 0;
    m_registers.f.c = 1;

    m_cyclesToWaste = 4;
}

// JR C, r8
void gbtest::LR35902::opcode38h()
{
    const auto val = (int8_t) fetch();

    if (!m_registers.f.c) {
        m_cyclesToWaste = 8;
        return;
    }

    m_registers.pc += val;
    m_cyclesToWaste = 12;
}

// ADD HL, SP
void gbtest::LR35902::opcode39h()
{
    ADD_HL_r16(m_registers.sp);
}

// LD A, (HL-)
void gbtest::LR35902::opcode3Ah()
{
    m_registers.a = m_bus.read(m_registers.hl--, gbtest::BusRequestSource::CPU);
    m_cyclesToWaste = 8;
}

// DEC SP
void gbtest::LR35902::opcode3Bh()
{
    --m_registers.sp;

    m_cyclesToWaste = 8;
}

// INC A
void gbtest::LR35902::opcode3Ch()
{
    INC_r8(m_registers.a);
}

// DEC A
void gbtest::LR35902::opcode3Dh()
{
    DEC_r8(m_registers.a);
}

// LD A, d8
void gbtest::LR35902::opcode3Eh()
{
    m_registers.a = fetch();
    m_cyclesToWaste = 8;
}

// CCF
void gbtest::LR35902::opcode3Fh()
{
    m_registers.f.n = 0;
    m_registers.f.h = 0;
    m_registers.f.c = ~m_registers.f.c;

    m_cyclesToWaste = 4;
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
    m_registers.b = m_bus.read(m_registers.hl, gbtest::BusRequestSource::CPU);
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
    m_registers.c = m_bus.read(m_registers.hl, gbtest::BusRequestSource::CPU);
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
    m_registers.d = m_bus.read(m_registers.hl, gbtest::BusRequestSource::CPU);
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
    m_registers.e = m_bus.read(m_registers.hl, gbtest::BusRequestSource::CPU);
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
    m_registers.h = m_bus.read(m_registers.hl, gbtest::BusRequestSource::CPU);
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
    m_registers.l = m_bus.read(m_registers.hl, gbtest::BusRequestSource::CPU);
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
    m_bus.write(m_registers.hl, m_registers.b, gbtest::BusRequestSource::CPU);
    m_cyclesToWaste = 8;
}

// LD (HL), C
void gbtest::LR35902::opcode71h()
{
    m_bus.write(m_registers.hl, m_registers.c, gbtest::BusRequestSource::CPU);
    m_cyclesToWaste = 8;
}

// LD (HL), D
void gbtest::LR35902::opcode72h()
{
    m_bus.write(m_registers.hl, m_registers.d, gbtest::BusRequestSource::CPU);
    m_cyclesToWaste = 8;
}

// LD (HL), E
void gbtest::LR35902::opcode73h()
{
    m_bus.write(m_registers.hl, m_registers.e, gbtest::BusRequestSource::CPU);
    m_cyclesToWaste = 8;
}

// LD (HL), H
void gbtest::LR35902::opcode74h()
{
    m_bus.write(m_registers.hl, m_registers.h, gbtest::BusRequestSource::CPU);
    m_cyclesToWaste = 8;
}

// LD (HL), L
void gbtest::LR35902::opcode75h()
{
    m_bus.write(m_registers.hl, m_registers.l, gbtest::BusRequestSource::CPU);
    m_cyclesToWaste = 8;
}

// HALT
void gbtest::LR35902::opcode76h()
{
    // TODO: Implement that
    m_halted = true;
    m_cyclesToWaste = 4;
}

// LD (HL), A
void gbtest::LR35902::opcode77h()
{
    m_bus.write(m_registers.hl, m_registers.a, gbtest::BusRequestSource::CPU);
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
    m_registers.a = m_bus.read(m_registers.hl, gbtest::BusRequestSource::CPU);
    m_cyclesToWaste = 8;
}

// LD A, A
void gbtest::LR35902::opcode7Fh()
{
    m_cyclesToWaste = 4;
}

// ADD A, B
void gbtest::LR35902::opcode80h()
{
    ADD_A(m_registers.b);
}

// ADD A, C
void gbtest::LR35902::opcode81h()
{
    ADD_A(m_registers.c);
}

// ADD A, D
void gbtest::LR35902::opcode82h()
{
    ADD_A(m_registers.d);
}

// ADD A, E
void gbtest::LR35902::opcode83h()
{
    ADD_A(m_registers.e);
}

// ADD A, H
void gbtest::LR35902::opcode84h()
{
    ADD_A(m_registers.h);
}

// ADD A, L
void gbtest::LR35902::opcode85h()
{
    ADD_A(m_registers.l);
}

// ADD A, (HL)
void gbtest::LR35902::opcode86h()
{
    ADD_A(m_bus.read(m_registers.hl, gbtest::BusRequestSource::CPU));
    m_cyclesToWaste += 4;
}

// ADD A, A
void gbtest::LR35902::opcode87h()
{
    ADD_A(m_registers.a);
}

// ADC A, B
void gbtest::LR35902::opcode88h()
{
    ADC_A(m_registers.b);
}

// ADC A, C
void gbtest::LR35902::opcode89h()
{
    ADC_A(m_registers.c);
}

// ADC A, D
void gbtest::LR35902::opcode8Ah()
{
    ADC_A(m_registers.d);
}

// ADC A, E
void gbtest::LR35902::opcode8Bh()
{
    ADC_A(m_registers.e);
}

// ADC A, H
void gbtest::LR35902::opcode8Ch()
{
    ADC_A(m_registers.h);
}

// ADC A, L
void gbtest::LR35902::opcode8Dh()
{
    ADC_A(m_registers.l);
}

// ADC A, (HL)
void gbtest::LR35902::opcode8Eh()
{
    ADC_A(m_bus.read(m_registers.hl, gbtest::BusRequestSource::CPU));
    m_cyclesToWaste += 4;
}

// ADC A, A
void gbtest::LR35902::opcode8Fh()
{
    ADC_A(m_registers.a);
}

// SUB A, B
void gbtest::LR35902::opcode90h()
{
    SUB_A(m_registers.b);
}

// SUB A, C
void gbtest::LR35902::opcode91h()
{
    SUB_A(m_registers.c);
}

// SUB A, D
void gbtest::LR35902::opcode92h()
{
    SUB_A(m_registers.d);
}

// SUB A, E
void gbtest::LR35902::opcode93h()
{
    SUB_A(m_registers.e);
}

// SUB A, H
void gbtest::LR35902::opcode94h()
{
    SUB_A(m_registers.h);
}

// SUB A, L
void gbtest::LR35902::opcode95h()
{
    SUB_A(m_registers.l);
}

// SUB A, (HL)
void gbtest::LR35902::opcode96h()
{
    SUB_A(m_bus.read(m_registers.hl, gbtest::BusRequestSource::CPU));
    m_cyclesToWaste += 4;
}

// SUB A, A
void gbtest::LR35902::opcode97h()
{
    // No need to compute the values at runtime here
    m_registers.a = 0;

    m_registers.f.z = 1;
    m_registers.f.n = 1;
    m_registers.f.h = 0;
    m_registers.f.c = 0;

    m_cyclesToWaste = 4;
}

// SBC A, B
void gbtest::LR35902::opcode98h()
{
    SBC_A(m_registers.b);
}

// SBC A, C
void gbtest::LR35902::opcode99h()
{
    SBC_A(m_registers.c);
}

// SBC A, D
void gbtest::LR35902::opcode9Ah()
{
    SBC_A(m_registers.d);
}

// SBC A, E
void gbtest::LR35902::opcode9Bh()
{
    SBC_A(m_registers.e);
}

// SBC A, H
void gbtest::LR35902::opcode9Ch()
{
    SBC_A(m_registers.h);
}

// SBC A, L
void gbtest::LR35902::opcode9Dh()
{
    SBC_A(m_registers.l);
}

// SBC A, (HL)
void gbtest::LR35902::opcode9Eh()
{
    SBC_A(m_bus.read(m_registers.hl, gbtest::BusRequestSource::CPU));
    m_cyclesToWaste += 4;
}

// SBC A, A
void gbtest::LR35902::opcode9Fh()
{
    SBC_A(m_registers.a);
}

// AND A, B
void gbtest::LR35902::opcodeA0h()
{
    AND_A(m_registers.b);
}

// AND A, C
void gbtest::LR35902::opcodeA1h()
{
    AND_A(m_registers.c);
}

// AND A, D
void gbtest::LR35902::opcodeA2h()
{
    AND_A(m_registers.d);
}

// AND A, E
void gbtest::LR35902::opcodeA3h()
{
    AND_A(m_registers.e);
}

// AND A, H
void gbtest::LR35902::opcodeA4h()
{
    AND_A(m_registers.h);
}

// AND A, L
void gbtest::LR35902::opcodeA5h()
{
    AND_A(m_registers.l);
}

// AND A, (HL)
void gbtest::LR35902::opcodeA6h()
{
    AND_A(m_bus.read(m_registers.hl, gbtest::BusRequestSource::CPU));
    m_cyclesToWaste += 4;
}

// AND A, A
void gbtest::LR35902::opcodeA7h()
{
    AND_A(m_registers.a);
}

// XOR A, B
void gbtest::LR35902::opcodeA8h()
{
    XOR_A(m_registers.b);
}

// XOR A, C
void gbtest::LR35902::opcodeA9h()
{
    XOR_A(m_registers.c);
}

// XOR A, D
void gbtest::LR35902::opcodeAAh()
{
    XOR_A(m_registers.d);
}

// XOR A, E
void gbtest::LR35902::opcodeABh()
{
    XOR_A(m_registers.e);
}

// XOR A, H
void gbtest::LR35902::opcodeACh()
{
    XOR_A(m_registers.h);
}

// XOR A, L
void gbtest::LR35902::opcodeADh()
{
    XOR_A(m_registers.l);
}

// XOR A, (HL)
void gbtest::LR35902::opcodeAEh()
{
    XOR_A(m_bus.read(m_registers.hl, gbtest::BusRequestSource::CPU));
    m_cyclesToWaste += 4;
}

// XOR A, A
void gbtest::LR35902::opcodeAFh()
{
    XOR_A(m_registers.a);
}

// OR A, B
void gbtest::LR35902::opcodeB0h()
{
    OR_A(m_registers.b);
}

// OR A, C
void gbtest::LR35902::opcodeB1h()
{
    OR_A(m_registers.c);
}

// OR A, D
void gbtest::LR35902::opcodeB2h()
{
    OR_A(m_registers.d);
}

// OR A, E
void gbtest::LR35902::opcodeB3h()
{
    OR_A(m_registers.e);
}

// OR A, H
void gbtest::LR35902::opcodeB4h()
{
    OR_A(m_registers.h);
}

// OR A, L
void gbtest::LR35902::opcodeB5h()
{
    OR_A(m_registers.l);
}

// OR A, (HL)
void gbtest::LR35902::opcodeB6h()
{
    OR_A(m_bus.read(m_registers.hl, gbtest::BusRequestSource::CPU));
    m_cyclesToWaste += 4;
}

// OR A, A
void gbtest::LR35902::opcodeB7h()
{
    OR_A(m_registers.a);
}

// CP A, B
void gbtest::LR35902::opcodeB8h()
{
    CP_A(m_registers.b);
}

// CP A, C
void gbtest::LR35902::opcodeB9h()
{
    CP_A(m_registers.c);
}

// CP A, D
void gbtest::LR35902::opcodeBAh()
{
    CP_A(m_registers.d);
}

// CP A, E
void gbtest::LR35902::opcodeBBh()
{
    CP_A(m_registers.e);
}

// CP A, H
void gbtest::LR35902::opcodeBCh()
{
    CP_A(m_registers.h);
}

// CP A, L
void gbtest::LR35902::opcodeBDh()
{
    CP_A(m_registers.l);
}

// CP A, (HL)
void gbtest::LR35902::opcodeBEh()
{
    const uint8_t val = m_bus.read(m_registers.hl, gbtest::BusRequestSource::CPU);
    CP_A(val);

    m_cyclesToWaste += 4;
}

// CP A, A
void gbtest::LR35902::opcodeBFh()
{
    m_registers.f.z = 1;
    m_registers.f.n = 1;
    m_registers.f.h = 0;
    m_registers.f.c = 0;

    m_cyclesToWaste = 4;
}

// RET NZ
void gbtest::LR35902::opcodeC0h()
{
    if (m_registers.f.z) {
        m_cyclesToWaste = 8;
        return;
    }

    m_registers.pc = m_bus.read(m_registers.sp++, gbtest::BusRequestSource::CPU)
            | (m_bus.read(m_registers.sp++, gbtest::BusRequestSource::CPU) << 8);
    m_cyclesToWaste = 20;
}

// POP BC
void gbtest::LR35902::opcodeC1h()
{
    m_registers.bc = m_bus.read(m_registers.sp++, gbtest::BusRequestSource::CPU)
            | (m_bus.read(m_registers.sp++, gbtest::BusRequestSource::CPU) << 8);
    m_cyclesToWaste = 12;
}

// JP NZ, a16
void gbtest::LR35902::opcodeC2h()
{
    const uint16_t val = fetch() | (fetch() << 8);

    if (m_registers.f.z) {
        m_cyclesToWaste = 12;
        return;
    }

    m_registers.pc = val;
    m_cyclesToWaste = 16;
}

// JP a16
void gbtest::LR35902::opcodeC3h()
{
    m_registers.pc = fetch() | (fetch() << 8);
    m_cyclesToWaste = 16;
}

// CALL NZ, a16
void gbtest::LR35902::opcodeC4h()
{
    const uint16_t val = fetch() | (fetch() << 8);

    if (m_registers.f.z) {
        m_cyclesToWaste = 12;
        return;
    }

    m_bus.write(--m_registers.sp, m_registers.pc >> 8, gbtest::BusRequestSource::CPU);
    m_bus.write(--m_registers.sp, m_registers.pc, gbtest::BusRequestSource::CPU);

    m_registers.pc = val;

    m_cyclesToWaste = 24;
}

// PUSH BC
void gbtest::LR35902::opcodeC5h()
{
    m_bus.write(--m_registers.sp, m_registers.b, gbtest::BusRequestSource::CPU);
    m_bus.write(--m_registers.sp, m_registers.c, gbtest::BusRequestSource::CPU);

    m_cyclesToWaste = 16;
}

// ADD A, d8
void gbtest::LR35902::opcodeC6h()
{
    ADD_A(fetch());
    m_cyclesToWaste += 4;
}

// RST 00H
void gbtest::LR35902::opcodeC7h()
{
    m_bus.write(--m_registers.sp, m_registers.pc >> 8, gbtest::BusRequestSource::CPU);
    m_bus.write(--m_registers.sp, m_registers.pc, gbtest::BusRequestSource::CPU);

    m_registers.pc = 0x00;

    m_cyclesToWaste = 16;
}

// RET Z
void gbtest::LR35902::opcodeC8h()
{
    if (!m_registers.f.z) {
        m_cyclesToWaste = 8;
        return;
    }

    m_registers.pc = m_bus.read(m_registers.sp++, gbtest::BusRequestSource::CPU)
            | (m_bus.read(m_registers.sp++, gbtest::BusRequestSource::CPU) << 8);
    m_cyclesToWaste = 20;
}

// RET
void gbtest::LR35902::opcodeC9h()
{
    m_registers.pc = m_bus.read(m_registers.sp++, gbtest::BusRequestSource::CPU)
            | (m_bus.read(m_registers.sp++, gbtest::BusRequestSource::CPU) << 8);
    m_cyclesToWaste = 16;
}

// JP Z, a16
void gbtest::LR35902::opcodeCAh()
{
    const uint16_t val = fetch() | (fetch() << 8);

    if (!m_registers.f.z) {
        m_cyclesToWaste = 12;
        return;
    }

    m_registers.pc = val;
    m_cyclesToWaste = 16;
}

// Prefixed instructions
void gbtest::LR35902::opcodeCBh()
{
    // Get the real opcode and the destination register/memory
    const uint8_t opcode = fetch();
    uint8_t lowOpcode = opcode & 0x7;

    auto getRegisterByLowerBits = [&](const uint8_t& lowerBits, uint8_t& defaultDest) -> uint8_t& {
      switch (lowerBits) {
      case 0x00:
          return m_registers.b;
      case 0x01:
          return m_registers.c;
      case 0x02:
          return m_registers.d;
      case 0x03:
          return m_registers.e;
      case 0x04:
          return m_registers.h;
      case 0x05:
          return m_registers.l;
      case 0x07:
          return m_registers.a;
      default:
          return defaultDest;
      }
    };

    uint8_t memValue = m_bus.read(m_registers.hl, gbtest::BusRequestSource::CPU);
    uint8_t& dest = getRegisterByLowerBits(lowOpcode, memValue);

    // Apply the right operation
    if (opcode >= 0x00 && opcode <= 0x07) {
        RLC(dest);
    }
    else if (opcode >= 0x08 && opcode <= 0x0F) {
        RRC(dest);
    }
    else if (opcode >= 0x10 && opcode <= 0x17) {
        RL(dest);
    }
    else if (opcode >= 0x18 && opcode <= 0x1F) {
        RR(dest);
    }
    else if (opcode >= 0x20 && opcode <= 0x27) {
        SLA(dest);
    }
    else if (opcode >= 0x28 && opcode <= 0x2F) {
        SRA(dest);
    }
    else if (opcode >= 0x30 && opcode <= 0x37) {
        SWAP(dest);
    }
    else if (opcode >= 0x38 && opcode <= 0x3F) {
        SRL(dest);
    }
    else if (opcode >= 0x40 && opcode <= 0x7F) {
        BIT((opcode - 0x40) / 0x8, dest);
    }
    else if (opcode >= 0x80 && opcode <= 0xBF) {
        RES((opcode - 0x80) / 0x8, dest);
    }
    else if (opcode >= 0xC0 && opcode <= 0xFF) {
        SET((opcode - 0xC0) / 0x8, dest);
    }

    // If the low opcode was equal to 6, then the destination was the memory
    if (lowOpcode == 0x06) {
        if (opcode < 0x40 || opcode > 0x7F) {
            // Only write the result if the operation was not BIT
            m_bus.write(m_registers.hl, memValue, gbtest::BusRequestSource::CPU);
        }

        m_cyclesToWaste += 8;
    }
}

// CALL Z, a16
void gbtest::LR35902::opcodeCCh()
{
    const uint16_t val = fetch() | (fetch() << 8);

    if (!m_registers.f.z) {
        m_cyclesToWaste = 12;
        return;
    }

    m_bus.write(--m_registers.sp, m_registers.pc >> 8, gbtest::BusRequestSource::CPU);
    m_bus.write(--m_registers.sp, m_registers.pc, gbtest::BusRequestSource::CPU);

    m_registers.pc = val;

    m_cyclesToWaste = 24;
}

// CALL a16
void gbtest::LR35902::opcodeCDh()
{
    const uint16_t val = fetch() | (fetch() << 8);

    m_bus.write(--m_registers.sp, m_registers.pc >> 8, gbtest::BusRequestSource::CPU);
    m_bus.write(--m_registers.sp, m_registers.pc, gbtest::BusRequestSource::CPU);

    m_registers.pc = val;

    m_cyclesToWaste = 24;
}

// ADC A, d8
void gbtest::LR35902::opcodeCEh()
{
    ADC_A(fetch());
    m_cyclesToWaste += 4;
}

// RST 08H
void gbtest::LR35902::opcodeCFh()
{
    m_bus.write(--m_registers.sp, m_registers.pc >> 8, gbtest::BusRequestSource::CPU);
    m_bus.write(--m_registers.sp, m_registers.pc, gbtest::BusRequestSource::CPU);

    m_registers.pc = 0x08;

    m_cyclesToWaste = 16;
}

// RET NC
void gbtest::LR35902::opcodeD0h()
{
    if (m_registers.f.c) {
        m_cyclesToWaste = 8;
        return;
    }

    m_registers.pc = m_bus.read(m_registers.sp++, gbtest::BusRequestSource::CPU)
            | (m_bus.read(m_registers.sp++, gbtest::BusRequestSource::CPU) << 8);
    m_cyclesToWaste = 20;
}

// POP DE
void gbtest::LR35902::opcodeD1h()
{
    m_registers.de = m_bus.read(m_registers.sp++, gbtest::BusRequestSource::CPU)
            | (m_bus.read(m_registers.sp++, gbtest::BusRequestSource::CPU) << 8);
    m_cyclesToWaste = 12;
}

// JP NC, a16
void gbtest::LR35902::opcodeD2h()
{
    const uint16_t val = fetch() | (fetch() << 8);

    if (m_registers.f.c) {
        m_cyclesToWaste = 12;
        return;
    }

    m_registers.pc = val;
    m_cyclesToWaste = 16;
}

void gbtest::LR35902::opcodeD3h()
{
    throw std::runtime_error("Opcode not implemented!");
}

// CALL NC, a16
void gbtest::LR35902::opcodeD4h()
{
    const uint16_t val = fetch() | (fetch() << 8);

    if (m_registers.f.c) {
        m_cyclesToWaste = 12;
        return;
    }

    m_bus.write(--m_registers.sp, m_registers.pc >> 8, gbtest::BusRequestSource::CPU);
    m_bus.write(--m_registers.sp, m_registers.pc, gbtest::BusRequestSource::CPU);

    m_registers.pc = val;

    m_cyclesToWaste = 24;
}

// PUSH DE
void gbtest::LR35902::opcodeD5h()
{
    m_bus.write(--m_registers.sp, m_registers.d, gbtest::BusRequestSource::CPU);
    m_bus.write(--m_registers.sp, m_registers.e, gbtest::BusRequestSource::CPU);

    m_cyclesToWaste = 16;
}

// SUB A, d8
void gbtest::LR35902::opcodeD6h()
{
    SUB_A(fetch());
    m_cyclesToWaste += 4;
}

// RST 10H
void gbtest::LR35902::opcodeD7h()
{
    m_bus.write(--m_registers.sp, m_registers.pc >> 8, gbtest::BusRequestSource::CPU);
    m_bus.write(--m_registers.sp, m_registers.pc, gbtest::BusRequestSource::CPU);

    m_registers.pc = 0x10;

    m_cyclesToWaste = 16;
}

// RET C
void gbtest::LR35902::opcodeD8h()
{
    if (!m_registers.f.c) {
        m_cyclesToWaste = 8;
        return;
    }

    m_registers.pc = m_bus.read(m_registers.sp++, gbtest::BusRequestSource::CPU)
            | (m_bus.read(m_registers.sp++, gbtest::BusRequestSource::CPU) << 8);
    m_cyclesToWaste = 20;
}

// RETI
void gbtest::LR35902::opcodeD9h()
{
    m_interruptController.setInterruptMasterEnable(true);
    m_registers.pc = m_bus.read(m_registers.sp++, gbtest::BusRequestSource::CPU)
            | (m_bus.read(m_registers.sp++, gbtest::BusRequestSource::CPU) << 8);

    m_cyclesToWaste = 16;
}

// JP C, a16
void gbtest::LR35902::opcodeDAh()
{
    const uint16_t val = fetch() | (fetch() << 8);

    if (!m_registers.f.c) {
        m_cyclesToWaste = 12;
        return;
    }

    m_registers.pc = val;
    m_cyclesToWaste = 16;
}

void gbtest::LR35902::opcodeDBh()
{
    throw std::runtime_error("Opcode not implemented!");
}

// CALL C, a16
void gbtest::LR35902::opcodeDCh()
{
    const uint16_t val = fetch() | (fetch() << 8);

    if (!m_registers.f.c) {
        m_cyclesToWaste = 12;
        return;
    }

    m_bus.write(--m_registers.sp, m_registers.pc >> 8, gbtest::BusRequestSource::CPU);
    m_bus.write(--m_registers.sp, m_registers.pc, gbtest::BusRequestSource::CPU);

    m_registers.pc = val;

    m_cyclesToWaste = 24;
}

void gbtest::LR35902::opcodeDDh()
{
    throw std::runtime_error("Opcode not implemented!");
}

// SBC A, d8
void gbtest::LR35902::opcodeDEh()
{
    SBC_A(fetch());
    m_cyclesToWaste += 4;
}

// RST 18H
void gbtest::LR35902::opcodeDFh()
{
    m_bus.write(--m_registers.sp, m_registers.pc >> 8, gbtest::BusRequestSource::CPU);
    m_bus.write(--m_registers.sp, m_registers.pc, gbtest::BusRequestSource::CPU);

    m_registers.pc = 0x18;

    m_cyclesToWaste = 16;
}

// LDH (a8), A
void gbtest::LR35902::opcodeE0h()
{
    m_bus.write(0xFF00 | fetch(), m_registers.a, gbtest::BusRequestSource::CPU);
    m_cyclesToWaste = 12;
}

// POP HL
void gbtest::LR35902::opcodeE1h()
{
    m_registers.hl = m_bus.read(m_registers.sp++, gbtest::BusRequestSource::CPU)
            | (m_bus.read(m_registers.sp++, gbtest::BusRequestSource::CPU) << 8);
    m_cyclesToWaste = 12;
}

// LD (C), A
void gbtest::LR35902::opcodeE2h()
{
    m_bus.write(0xFF00 + m_registers.c, m_registers.a, gbtest::BusRequestSource::CPU);
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
    m_bus.write(--m_registers.sp, m_registers.h, gbtest::BusRequestSource::CPU);
    m_bus.write(--m_registers.sp, m_registers.l, gbtest::BusRequestSource::CPU);

    m_cyclesToWaste = 16;
}

// AND A, d8
void gbtest::LR35902::opcodeE6h()
{
    m_registers.a &= fetch();

    m_registers.f.z = m_registers.a == 0;
    m_registers.f.n = 0;
    m_registers.f.h = 1;
    m_registers.f.c = 0;

    m_cyclesToWaste = 8;
}

// RST 20H
void gbtest::LR35902::opcodeE7h()
{
    m_bus.write(--m_registers.sp, m_registers.pc >> 8, gbtest::BusRequestSource::CPU);
    m_bus.write(--m_registers.sp, m_registers.pc, gbtest::BusRequestSource::CPU);

    m_registers.pc = 0x20;

    m_cyclesToWaste = 16;
}

// ADD SP, r8
void gbtest::LR35902::opcodeE8h()
{
    // First compute the final result
    const int8_t immediateValue = (int8_t) fetch();
    const uint32_t res = m_registers.sp + immediateValue;

    // Set the half-carry before doing anything as we need the current value in register A
    m_registers.f.h = ((((m_registers.sp & 0x000F) + (immediateValue & 0x0F)) & 0x0010) == 0x0010);
    m_registers.f.c = ((((m_registers.sp & 0x00FF) + (immediateValue & 0xFF)) & 0x0100) == 0x0100);

    // Set the accumulator to the result
    m_registers.sp = (res & 0xFFFF);

    // Set the flags according to the result
    m_registers.f.z = 0;
    m_registers.f.n = 0;

    m_cyclesToWaste = 4;
}

// JP HL
void gbtest::LR35902::opcodeE9h()
{
    m_registers.pc = m_registers.hl;
    m_cyclesToWaste = 4;
}

// LD (a16), A
void gbtest::LR35902::opcodeEAh()
{
    m_bus.write(fetch() | (fetch() << 8), m_registers.a, gbtest::BusRequestSource::CPU);
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

// XOR A, d8
void gbtest::LR35902::opcodeEEh()
{
    m_registers.a ^= fetch();

    m_registers.f.z = m_registers.a == 0;
    m_registers.f.n = 0;
    m_registers.f.h = 0;
    m_registers.f.c = 0;

    m_cyclesToWaste = 8;
}

// RST 28H
void gbtest::LR35902::opcodeEFh()
{
    m_bus.write(--m_registers.sp, m_registers.pc >> 8, gbtest::BusRequestSource::CPU);
    m_bus.write(--m_registers.sp, m_registers.pc, gbtest::BusRequestSource::CPU);

    m_registers.pc = 0x28;

    m_cyclesToWaste = 16;
}

// LDH A, (a8)
void gbtest::LR35902::opcodeF0h()
{
    m_registers.a = m_bus.read(0xFF00 | fetch(), gbtest::BusRequestSource::CPU);
    m_cyclesToWaste = 12;
}

// POP AF
void gbtest::LR35902::opcodeF1h()
{
    m_registers.af = (m_bus.read(m_registers.sp++, gbtest::BusRequestSource::CPU) & 0xF0)
            | (m_bus.read(m_registers.sp++, gbtest::BusRequestSource::CPU) << 8);
    m_cyclesToWaste = 12;
}

// LD A, (C)
void gbtest::LR35902::opcodeF2h()
{
    m_registers.a = m_bus.read(0xFF00 + m_registers.c, gbtest::BusRequestSource::CPU);
    m_cyclesToWaste = 8;
}

// DI
void gbtest::LR35902::opcodeF3h()
{
    m_interruptController.setInterruptMasterEnable(false);
    m_cyclesToWaste = 4;
}

void gbtest::LR35902::opcodeF4h()
{
    throw std::runtime_error("Opcode not implemented!");
}

// PUSH AF
void gbtest::LR35902::opcodeF5h()
{
    m_bus.write(--m_registers.sp, m_registers.af >> 8, gbtest::BusRequestSource::CPU);
    m_bus.write(--m_registers.sp, m_registers.af, gbtest::BusRequestSource::CPU);

    m_cyclesToWaste = 16;
}

// OR A, d8
void gbtest::LR35902::opcodeF6h()
{
    m_registers.a |= fetch();

    m_registers.f.z = m_registers.a == 0;
    m_registers.f.n = 0;
    m_registers.f.h = 0;
    m_registers.f.c = 0;

    m_cyclesToWaste = 8;
}

// RST 30H
void gbtest::LR35902::opcodeF7h()
{
    m_bus.write(--m_registers.sp, m_registers.pc >> 8, gbtest::BusRequestSource::CPU);
    m_bus.write(--m_registers.sp, m_registers.pc, gbtest::BusRequestSource::CPU);

    m_registers.pc = 0x30;

    m_cyclesToWaste = 16;
}

// LD HL, SP + r8
void gbtest::LR35902::opcodeF8h()
{
    auto a = (int8_t) fetch();
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
    m_registers.a = m_bus.read(fetch() | (fetch() << 8), gbtest::BusRequestSource::CPU);
    m_cyclesToWaste = 16;
}

// EI
void gbtest::LR35902::opcodeFBh()
{
    // Interrupt enable is delayed
    m_interruptController.setDelayedInterruptEnableCountdown(2);
    m_cyclesToWaste = 4;
}

void gbtest::LR35902::opcodeFCh()
{
    throw std::runtime_error("Opcode not implemented!");
}

void gbtest::LR35902::opcodeFDh()
{
    throw std::runtime_error("Opcode not implemented!");
}

// CP A, d8
void gbtest::LR35902::opcodeFEh()
{
    const uint8_t val = fetch();
    CP_A(val);

    m_cyclesToWaste += 4;
}

// RST 38H
void gbtest::LR35902::opcodeFFh()
{
    m_bus.write(--m_registers.sp, m_registers.pc >> 8, gbtest::BusRequestSource::CPU);
    m_bus.write(--m_registers.sp, m_registers.pc, gbtest::BusRequestSource::CPU);

    m_registers.pc = 0x38;

    m_cyclesToWaste = 16;
}

// 0xCB-prefixed instructions
void gbtest::LR35902::RLC(uint8_t& dest)
{
    m_registers.f.c = (dest >> 7) & 0x1;

    dest = (dest << 1) | m_registers.f.c;

    m_registers.f.z = dest == 0;
    m_registers.f.n = 0;
    m_registers.f.h = 0;

    m_cyclesToWaste = 8;
}

void gbtest::LR35902::RRC(uint8_t& dest)
{
    m_registers.f.c = dest & 0x1;

    dest = (dest >> 1) | (m_registers.f.c << 7);

    m_registers.f.z = dest == 0;
    m_registers.f.n = 0;
    m_registers.f.h = 0;

    m_cyclesToWaste = 8;
}

void gbtest::LR35902::RL(uint8_t& dest)
{
    const uint8_t newCarry = (dest >> 7) & 0x1;

    dest = (dest << 1) | (m_registers.f.c & 0x1);

    m_registers.f.z = (dest == 0);
    m_registers.f.n = 0;
    m_registers.f.h = 0;
    m_registers.f.c = newCarry;

    m_cyclesToWaste = 8;
}

void gbtest::LR35902::RR(uint8_t& dest)
{
    const uint8_t newCarry = dest & 0x1;

    dest = (dest >> 1) | (m_registers.f.c << 7);

    m_registers.f.z = (dest == 0);
    m_registers.f.n = 0;
    m_registers.f.h = 0;
    m_registers.f.c = newCarry;

    m_cyclesToWaste = 8;
}

void gbtest::LR35902::SLA(uint8_t& dest)
{
    m_registers.f.c = (dest >> 7) & 0x1;

    dest <<= 1;

    m_registers.f.z = dest == 0;
    m_registers.f.n = 0;
    m_registers.f.h = 0;

    m_cyclesToWaste = 8;
}

void gbtest::LR35902::SRA(uint8_t& dest)
{
    m_registers.f.c = dest & 0x1;

    dest >>= 1;
    dest |= (dest & 0x40) << 1;

    m_registers.f.z = dest == 0;
    m_registers.f.n = 0;
    m_registers.f.h = 0;

    m_cyclesToWaste = 8;
}

void gbtest::LR35902::SWAP(uint8_t& dest)
{
    const uint8_t newUpper = dest << 4;
    dest = (dest >> 4) | newUpper;

    m_registers.f.z = dest == 0;
    m_registers.f.n = 0;
    m_registers.f.h = 0;
    m_registers.f.c = 0;

    m_cyclesToWaste = 8;
}

void gbtest::LR35902::SRL(uint8_t& dest)
{
    m_registers.f.c = dest & 0x1;

    dest >>= 1;

    m_registers.f.z = dest == 0;
    m_registers.f.n = 0;
    m_registers.f.h = 0;

    m_cyclesToWaste = 8;
}

void gbtest::LR35902::BIT(const uint8_t& bitToTest, const uint8_t& src)
{
    m_registers.f.z = (src & (1 << bitToTest)) == 0;
    m_registers.f.n = 0;
    m_registers.f.h = 1;

    m_cyclesToWaste = 8;
}

void gbtest::LR35902::RES(const uint8_t& bitToClear, uint8_t& dest)
{
    dest &= ~(1 << bitToClear);
}

void gbtest::LR35902::SET(const uint8_t& bitToSet, uint8_t& dest)
{
    dest |= 1 << bitToSet;
}

void gbtest::LR35902::ADD_A(const uint8_t& src)
{
    // First compute the final result
    const uint16_t res = m_registers.a + src;

    // Set the half-carry before doing anything as we need the current value in register A
    m_registers.f.h = ((((m_registers.a & 0x0F) + (src & 0x0F)) & 0x10) == 0x10);

    // Set the accumulator to the result
    m_registers.a = res;

    // Set the flags according to the result
    m_registers.f.z = (m_registers.a == 0);
    m_registers.f.n = 0;
    m_registers.f.c = (res > 0xFF);

    m_cyclesToWaste = 4;
}

void gbtest::LR35902::ADC_A(const uint8_t& src)
{
    // First compute the final result
    const uint16_t res = m_registers.a + src + m_registers.f.c;

    // We must compute the operation separately to set the half-carry properly
    m_registers.f.h = ((((m_registers.a & 0x0F) + (src & 0x0F) + (m_registers.f.c & 0x0F)) & 0x10) == 0x10);

    // Set the accumulator to the result
    m_registers.a = res;

    // Set the flags according to the result
    m_registers.f.z = (m_registers.a == 0);
    m_registers.f.n = 0;
    m_registers.f.c = (res > 0xFF);

    m_cyclesToWaste = 4;
}

void gbtest::LR35902::SUB_A(const uint8_t& src)
{
    // Set (half-)carry flags before the operation takes place
    m_registers.f.h = (src & 0x0F) > (m_registers.a & 0x0F);
    m_registers.f.c = (src > m_registers.a);

    // Set the accumulator to the result
    m_registers.a -= src;

    // Set the flags according to the result
    m_registers.f.z = (m_registers.a == 0);
    m_registers.f.n = 1;

    m_cyclesToWaste = 4;
}

void gbtest::LR35902::SBC_A(const uint8_t& src)
{
    // Set the (half-)carry before doing anything as we need the current value in register A
    const uint8_t oldCarry = m_registers.f.c;
    m_registers.f.h = (((src & 0x0F) + (oldCarry & 0x0F))) > (m_registers.a & 0x0F);
    m_registers.f.c = ((src + oldCarry) > m_registers.a);

    // Set the accumulator to the result
    m_registers.a -= src + oldCarry;

    // Set the flags according to the result
    m_registers.f.z = (m_registers.a == 0);
    m_registers.f.n = 1;

    m_cyclesToWaste = 4;
}

void gbtest::LR35902::AND_A(const uint8_t& src)
{
    // Perform the operation
    m_registers.a &= src;

    // Set the flags according to the result
    m_registers.f.z = (m_registers.a == 0);
    m_registers.f.n = 0;
    m_registers.f.h = 1;
    m_registers.f.c = 0;

    m_cyclesToWaste = 4;
}

void gbtest::LR35902::XOR_A(const uint8_t& src)
{
    // Perform the operation
    m_registers.a ^= src;

    // Set the flags according to the result
    m_registers.f.z = (m_registers.a == 0);
    m_registers.f.n = 0;
    m_registers.f.h = 0;
    m_registers.f.c = 0;

    m_cyclesToWaste = 4;
}

void gbtest::LR35902::OR_A(const uint8_t& src)
{
    // Perform the operation
    m_registers.a |= src;

    // Set the flags according to the result
    m_registers.f.z = (m_registers.a == 0);
    m_registers.f.n = 0;
    m_registers.f.h = 0;
    m_registers.f.c = 0;

    m_cyclesToWaste = 4;
}

void gbtest::LR35902::CP_A(const uint8_t& src)
{
    // Set the flags according to the result
    m_registers.f.z = (m_registers.a == src);
    m_registers.f.n = 1;
    m_registers.f.h = ((src & 0x0F) > (m_registers.a & 0x0F));
    m_registers.f.c = (src > m_registers.a);

    m_cyclesToWaste = 4;
}

void gbtest::LR35902::INC_r8(uint8_t& reg)
{
    // Increment the register
    uint8_t oldVal = reg++;

    // Set the flags according to the result
    m_registers.f.z = (reg == 0);
    m_registers.f.n = 0;
    m_registers.f.h = ((oldVal & 0x08) && !(reg & 0x08));

    m_cyclesToWaste = 4;
}

void gbtest::LR35902::DEC_r8(uint8_t& reg)
{
    // Decrement the register
    uint8_t oldVal = reg--;

    // Set the flags according to the result
    m_registers.f.z = (reg == 0);
    m_registers.f.n = 1;
    m_registers.f.h = ((oldVal & 0x10) != (reg & 0x10));

    m_cyclesToWaste = 4;
}

void gbtest::LR35902::ADD_HL_r16(uint16_t& reg)
{
    // Add the value of the specified register to HL
    uint16_t oldVal = m_registers.hl;
    m_registers.hl += reg;

    // Set the flags according to the result
    m_registers.f.n = 0;
    m_registers.f.h = ((((oldVal & 0x0FFF) + (reg & 0x0FFF)) & 0x1000) == 0x1000);
    m_registers.f.c = ((((oldVal & 0xFFFF) + (reg & 0xFFFF)) & 0x10000) == 0x10000);

    m_cyclesToWaste = 8;
}