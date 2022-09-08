#include "GameBoy.h"

#include <memory>

#include "../cartridge/CartridgeNoMBC.h"
#include "../cartridge/CartridgeMBC1.h"
#include "../cartridge/CartridgeMBC3.h"
#include "../exceptions/cartridge/UnsupportedCartridgeTypeException.h"
#include "revision/GameBoyStartupRegisters.h"

gbtest::GameBoy::GameBoy(gbtest::GameBoyRevisionType&& revisionType)
        : m_cpu(m_bus)
        , m_wholeMemory(0xC000, 0x4000)
        , m_ppu(m_bus)
        , m_joypad(m_bus)
        , m_divider(m_cpu.getHaltState())
        , m_timer(m_bus)
        , m_revision(revisionType)
        , m_running(false)
{

}

gbtest::GameBoy::~GameBoy()
{
    unregisterBusProviders();
}

void gbtest::GameBoy::init()
{
    // Reset the emulator
    reset();

    // Register bus providers
    registerBusProviders();
}

void gbtest::GameBoy::reset()
{
    // Stop emulation
    stop();

    // Reset CPU registers
    resetRegisters();
}

void gbtest::GameBoy::reset(gbtest::GameBoyRevisionType&& revisionType)
{
    // Set the new revision
    m_revision = GameBoyRevision(revisionType);

    // Reset the emulator
    reset();
}

void gbtest::GameBoy::update(float secondsToEmulate)
{
    // Check if the emulator is running
    if (!m_running) {
        return;
    }

    // Compute how many ticks there are to emulate
    const auto ticksToEmulate = static_cast<unsigned>(secondsToEmulate * GAMEBOY_FREQUENCY);
//    std::cout << "Emulating " << ticksToEmulate << " ticks" << std::endl;

    // Tick the emulator
    for (unsigned i = 0; i < ticksToEmulate; ++i) {
        tickEmulator();
    }
}

void gbtest::GameBoy::tick(bool force)
{
    // Check if the emulator is running
    if (!m_running && !force) {
        return;
    }

    // Tick the emulator
    tickEmulator();
}

void gbtest::GameBoy::start()
{
    m_running = true;
}

void gbtest::GameBoy::stop()
{
    m_running = false;
}

bool gbtest::GameBoy::isRunning() const
{
    return m_running;
}

const gbtest::GameBoyRevision& gbtest::GameBoy::getRevision() const
{
    return m_revision;
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

void gbtest::GameBoy::loadCartridgeFromDataSource(std::unique_ptr<gbtest::CartridgeDataSource> dataSource)
{
    // Get the MBC type from the data source
    uint8_t rawMBCType;
    dataSource->read(0x0147, rawMBCType);

    auto mbcType = CartridgeHeaderCartridgeType(rawMBCType);

    // Instantiate the correct class according to the MBC type
    switch (mbcType) {
    case CartridgeHeaderCartridgeType::ROMOnly:
        // No MBC
        loadCartridge(std::make_unique<gbtest::CartridgeNoMBC>(std::move(dataSource)));
        break;

    case CartridgeHeaderCartridgeType::MBC1:
    case CartridgeHeaderCartridgeType::MBC1AndRAM:
    case CartridgeHeaderCartridgeType::MBC1AndRAMAndBattery:
        // MBC1
        loadCartridge(std::make_unique<gbtest::CartridgeMBC1>(std::move(dataSource)));
        break;

    case CartridgeHeaderCartridgeType::MBC3:
    case CartridgeHeaderCartridgeType::MBC3AndRAM:
    case CartridgeHeaderCartridgeType::MBC3AndRAMAndBattery:
    case CartridgeHeaderCartridgeType::MBC3AndTimerAndBattery:
    case CartridgeHeaderCartridgeType::MBC3AndTimerAndRAMAndBattery:
        // MBC3
        loadCartridge(std::make_unique<gbtest::CartridgeMBC3>(std::move(dataSource)));
        break;

    default:
        // Unsupported cartridge type
        throw gbtest::UnsupportedCartridgeTypeException(mbcType);
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

void gbtest::GameBoy::resetRegisters()
{
    // Load the startup registers
    GameBoyStartupRegisters startupRegisters(m_revision.getRevisionType());

    // CPU
    LR35902Registers registers{};
    startupRegisters.loadCPURegisters(registers);

    m_cpu.setRegisters(registers);

    // Peripherals
    startupRegisters.loadDividerRegisters(m_divider);
    startupRegisters.loadTimerRegisters(m_timer);
    startupRegisters.loadPPURegisters(m_ppu);
    startupRegisters.loadAPURegisters(m_apu);
}

void gbtest::GameBoy::registerBusProviders()
{
    // TODO: Have the real memory layout
    m_bus.registerBusProvider(&(m_cpu.getInterruptController()));
    m_bus.registerBusProvider(&m_ppu);
    m_bus.registerBusProvider(&m_joypad);
    m_bus.registerBusProvider(&m_apu);
    m_bus.registerBusProvider(&m_divider);
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
    m_bus.unregisterBusProvider(&m_divider);
    m_bus.unregisterBusProvider(&m_apu);
    m_bus.unregisterBusProvider(&m_joypad);
    m_bus.unregisterBusProvider(&m_ppu);
    m_bus.unregisterBusProvider(&(m_cpu.getInterruptController()));
}

void gbtest::GameBoy::tickEmulator()
{
    // Tick everything
    m_timer.tick();
    m_divider.tick();
    m_joypad.tick();
    m_cpu.tick();
    m_ppu.tick();
    m_apu.tick();

    if (m_cartridge) {
        m_cartridge->tick();
    }
}
