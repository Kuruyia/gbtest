#include "GameBoy.h"

gbtest::GameBoy::GameBoy()
        : m_cpu(m_bus)
        , m_wholeMemory(0x8000, 0x8000)
        , m_ppu(m_bus)
        , m_timer(m_bus)
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
    const auto ticksToEmulate = static_cast<unsigned>(secondsToEmulate * GAMEBOY_FREQUENCY);
//    std::cout << "Emulating " << ticksToEmulate << " ticks" << std::endl;

    for (unsigned i = 0; i < ticksToEmulate; ++i) {
        tick();
    }
}

void gbtest::GameBoy::tick()
{
    m_timer.tick();
    m_cpu.tick();
    m_ppu.tick();
    m_apu.tick();
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

gbtest::Joypad& gbtest::GameBoy::getJoypad()
{
    return m_joypad;
}

const gbtest::Joypad& gbtest::GameBoy::getJoypad() const
{
    return m_joypad;
}

gbtest::APU& gbtest::GameBoy::getApu()
{
    return m_apu;
}

const gbtest::APU& gbtest::GameBoy::getApu() const
{
    return m_apu;
}

gbtest::Timer& gbtest::GameBoy::getTimer()
{
    return m_timer;
}

const gbtest::Timer& gbtest::GameBoy::getTimer() const
{
    return m_timer;
}

void gbtest::GameBoy::loadCartridge(std::unique_ptr<BaseCartridge> cartridge)
{
    // Unregister the old cartridge from the bus
    if (m_cartridge) {
        m_bus.unregisterBusProvider(m_cartridge.get());
    }

    // Move in the new cartridge
    m_cartridge = std::move(cartridge);

    // Register the new cartridge to the bus
    if (m_cartridge) {
        m_bus.registerBusProvider(m_cartridge.get());
    }
}

gbtest::BaseCartridge* gbtest::GameBoy::getCartridge()
{
    return m_cartridge.get();
}

const gbtest::BaseCartridge* gbtest::GameBoy::getCartridge() const
{
    return m_cartridge.get();
}

void gbtest::GameBoy::resetCpuRegisters()
{
    // DMG registers

    // CPU
    LR35902Registers registers{};
    registers.af = 0x0180;
    registers.bc = 0x0013;
    registers.de = 0x00D8;
    registers.hl = 0x014D;
    registers.pc = 0x0100;
    registers.sp = 0xFFFE;

    m_cpu.setRegisters(registers);

    // Timer
    m_timer.getTimerCounterRegister().raw = 0x00;
    m_timer.getTimerModuloRegister().raw = 0x00;
    m_timer.getTimerControlRegister().raw = 0xF8;

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

    // APU
    SoundControlRegisters& soundControlRegisters = m_apu.getSoundControlRegisters();

    soundControlRegisters.channelControl.raw = 0x77;
    soundControlRegisters.soundOutputTerminalSelection.raw = 0xF3;
    soundControlRegisters.soundOnOff.raw = 0xF1;

    // APU Channel 1
    Channel1Registers& channel1Registers = m_apu.getChannel1().getRegisters();

    channel1Registers.sweep.raw = 0x80;
    channel1Registers.soundLengthWavePatternDuty.raw = 0xBF;
    channel1Registers.volumeEnvelope.raw = 0xF3;
    channel1Registers.frequencyLow.raw = 0xFF;
    channel1Registers.frequencyHigh.raw = 0xBF;

    // APU Channel 2
    Channel2Registers& channel2Registers = m_apu.getChannel2().getRegisters();

    channel2Registers.soundLengthWavePatternDuty.raw = 0x3F;
    channel2Registers.volumeEnvelope.raw = 0x00;
    channel2Registers.frequencyLow.raw = 0xFF;
    channel2Registers.frequencyHigh.raw = 0xBF;

    // APU Channel 3
    Channel3Registers& channel3Registers = m_apu.getChannel3().getRegisters();

    channel3Registers.soundOnOff.raw = 0x7F;
    channel3Registers.soundLength.raw = 0xFF;
    channel3Registers.selectOutputLevel.raw = 0x9F;
    channel3Registers.frequencyLow.raw = 0xFF;
    channel3Registers.frequencyHigh.raw = 0xBF;

    // APU Channel 4
    Channel4Registers& channel4Registers = m_apu.getChannel4().getRegisters();

    channel4Registers.soundLength.raw = 0xFF;
    channel4Registers.volumeEnvelope.raw = 0x00;
    channel4Registers.polynomialCounter.raw = 0x00;
    channel4Registers.counterConsecutiveAndInitial.raw = 0xBF;
}

void gbtest::GameBoy::registerBusProviders()
{
    // TODO: Have the real memory layout
    m_bus.registerBusProvider(&(m_cpu.getInterruptController()));
    m_bus.registerBusProvider(&m_ppu);
    m_bus.registerBusProvider(&m_joypad);
    m_bus.registerBusProvider(&m_apu);
    m_bus.registerBusProvider(&m_timer);
    m_bus.registerBusProvider(&m_wholeMemory);
}

void gbtest::GameBoy::unregisterBusProviders()
{
    if (m_cartridge) {
        m_bus.unregisterBusProvider(m_cartridge.get());
    }

    m_bus.unregisterBusProvider(&m_wholeMemory);
    m_bus.unregisterBusProvider(&m_timer);
    m_bus.unregisterBusProvider(&m_apu);
    m_bus.unregisterBusProvider(&m_joypad);
    m_bus.unregisterBusProvider(&m_ppu);
    m_bus.unregisterBusProvider(&(m_cpu.getInterruptController()));
}
