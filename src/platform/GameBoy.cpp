#include "GameBoy.h"

gbtest::GameBoy::GameBoy()
        : m_cpu(m_bus)
        , m_wholeMemory(0x0000, 0x10000)
        , m_ppu(m_bus)
{

}

gbtest::GameBoy::~GameBoy()
{
    unregisterBusProviders();
}

void gbtest::GameBoy::init()
{
    // Reset CPU registers
    resetCpuRegisters();

    // Register bus providers
    registerBusProviders();
}

void gbtest::GameBoy::update(float secondsToEmulate)
{
    const int ticksToEmulate = static_cast<int>(secondsToEmulate * CLOCK_FREQUENCY_HZ);
//    std::cout << "Emulating " << ticksToEmulate << " ticks" << std::endl;

    for (unsigned i = 0; i < ticksToEmulate; ++i) {
        tick();
    }
}

void gbtest::GameBoy::tick()
{
    m_cpu.tick();
    m_ppu.tick();
}

gbtest::Bus& gbtest::GameBoy::getBus()
{
    return m_bus;
}

const gbtest::Bus& gbtest::GameBoy::getBus() const
{
    return m_bus;
}

gbtest::LR35902& gbtest::GameBoy::getCpu()
{
    return m_cpu;
}

const gbtest::LR35902& gbtest::GameBoy::getCpu() const
{
    return m_cpu;
}

gbtest::PPU& gbtest::GameBoy::getPpu()
{
    return m_ppu;
}

const gbtest::PPU& gbtest::GameBoy::getPpu() const
{
    return m_ppu;
}

void gbtest::GameBoy::resetCpuRegisters()
{
    // DMG registers

    // CPU
    gbtest::LR35902Registers registers{};
    registers.af = 0x0180;
    registers.bc = 0x0013;
    registers.de = 0x00D8;
    registers.hl = 0x014D;
    registers.pc = 0x0100;
    registers.sp = 0xFFFE;

    m_cpu.setRegisters(registers);

    // PPU
    PPURegisters& ppuRegisters = m_ppu.getPpuRegisters();

    ppuRegisters.lcdControl.raw = 0x91;
    ppuRegisters.lcdStatus.raw = 0x80;

    ppuRegisters.lcdPositionAndScrolling.xScroll = 0x00;
    ppuRegisters.lcdPositionAndScrolling.yScroll = 0x00;
    ppuRegisters.lcdPositionAndScrolling.lyCompare = 0x00;
    ppuRegisters.lcdPositionAndScrolling.xWindowPosition = 0x00;
    ppuRegisters.lcdPositionAndScrolling.yWindowPosition = 0x00;

    ppuRegisters.dmgPalettes.bgPaletteData.raw = 0xFC;
    ppuRegisters.dmgPalettes.objectPaletteData0.raw = 0xFF;
    ppuRegisters.dmgPalettes.objectPaletteData1.raw = 0xFF;
}

void gbtest::GameBoy::registerBusProviders()
{
    // TODO: Have the real memory layout
    m_bus.registerBusProvider(&(m_cpu.getInterruptController()));
    m_bus.registerBusProvider(&m_ppu);
    m_bus.registerBusProvider(&m_wholeMemory);
}

void gbtest::GameBoy::unregisterBusProviders()
{
    m_bus.unregisterBusProvider(&m_wholeMemory);
    m_bus.unregisterBusProvider(&m_ppu);
    m_bus.unregisterBusProvider(&(m_cpu.getInterruptController()));
}
