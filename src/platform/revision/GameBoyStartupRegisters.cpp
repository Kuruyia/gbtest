#include "GameBoyStartupRegisters.h"

#include "../../exceptions/platform/UnsupportedRevisionException.h"

gbtest::GameBoyStartupRegisters::GameBoyStartupRegisters(gbtest::GameBoyRevisionType revisionType)
        : m_revisionType(revisionType)
{

}

void gbtest::GameBoyStartupRegisters::loadCPURegisters(gbtest::LR35902Registers& regs) const
{
    // Load the correct registers for the revision
    switch (m_revisionType) {
    case GameBoyRevisionType::DMG:
        loadCPURegistersDMG(regs);
        break;

    case GameBoyRevisionType::CGB:
        loadCPURegistersCGB(regs);
        break;

    default:
        throw gbtest::UnsupportedRevisionException(m_revisionType);
    }
}

void gbtest::GameBoyStartupRegisters::loadDividerRegisters(gbtest::Divider& divider) const
{
    // Load the correct registers for the revision
    switch (m_revisionType) {
    case GameBoyRevisionType::DMG:
        loadDividerRegistersDMG(divider);
        break;

    case GameBoyRevisionType::CGB:
        loadDividerRegistersCGB(divider);
        break;

    default:
        throw gbtest::UnsupportedRevisionException(m_revisionType);
    }
}

void gbtest::GameBoyStartupRegisters::loadTimerRegisters(gbtest::Timer& timer) const
{
    // Load the correct registers for the revision
    switch (m_revisionType) {
    case GameBoyRevisionType::DMG:
        loadTimerRegistersDMG(timer);
        break;

    case GameBoyRevisionType::CGB:
        loadTimerRegistersCGB(timer);
        break;

    default:
        throw gbtest::UnsupportedRevisionException(m_revisionType);
    }
}

void gbtest::GameBoyStartupRegisters::loadPPURegisters(gbtest::PPU& ppu) const
{
    // Load the correct registers for the revision
    switch (m_revisionType) {
    case GameBoyRevisionType::DMG:
        loadPPURegistersDMG(ppu);
        break;

    case GameBoyRevisionType::CGB:
        loadPPURegistersCGB(ppu);
        break;

    default:
        throw gbtest::UnsupportedRevisionException(m_revisionType);
    }
}

void gbtest::GameBoyStartupRegisters::loadAPURegisters(gbtest::APU& apu) const
{
    // Load the correct registers for the revision
    switch (m_revisionType) {
    case GameBoyRevisionType::DMG:
        loadAPURegistersDMG(apu);
        break;

    case GameBoyRevisionType::CGB:
        loadAPURegistersCGB(apu);
        break;

    default:
        throw gbtest::UnsupportedRevisionException(m_revisionType);
    }

    // Commit the registers
    apu.getChannel1().commitRegisters();
    apu.getChannel2().commitRegisters();
    apu.getChannel3().commitRegisters();
    apu.getChannel4().commitRegisters();
}

void gbtest::GameBoyStartupRegisters::loadCPURegistersDMG(gbtest::LR35902Registers& regs)
{
    // DMG - CPU
    regs.af = 0x0180;
    regs.bc = 0x0013;
    regs.de = 0x00D8;
    regs.hl = 0x014D;
    regs.pc = 0x0100;
    regs.sp = 0xFFFE;
}

void gbtest::GameBoyStartupRegisters::loadDividerRegistersDMG(gbtest::Divider& divider)
{
    // DMG - Divider
    divider.getRegister().value = 0xAB;
}

void gbtest::GameBoyStartupRegisters::loadTimerRegistersDMG(gbtest::Timer& timer)
{
    // DMG - Timer
    timer.getTimerCounterRegister().raw = 0x00;
    timer.getTimerModuloRegister().raw = 0x00;
    timer.getTimerControlRegister().raw = 0xF8;
}

void gbtest::GameBoyStartupRegisters::loadPPURegistersDMG(gbtest::PPU& ppu)
{
    // DMG - PPU
    PPURegisters& ppuRegisters = ppu.getPpuRegisters();

    ppuRegisters.lcdControl.raw = 0x91;
    ppuRegisters.lcdStatus.raw = 0x85;

    ppuRegisters.lcdPositionAndScrolling.xScroll = 0x00;
    ppuRegisters.lcdPositionAndScrolling.yScroll = 0x00;
    ppuRegisters.lcdPositionAndScrolling.lyCompare = 0x00;
    ppuRegisters.lcdPositionAndScrolling.xWindowPosition = 0x00;
    ppuRegisters.lcdPositionAndScrolling.yWindowPosition = 0x00;

    ppuRegisters.dmgPalettes.bgPaletteData.raw = 0xFC;
    ppuRegisters.dmgPalettes.objectPaletteData0.raw = 0xFF;
    ppuRegisters.dmgPalettes.objectPaletteData1.raw = 0xFF;
}

void gbtest::GameBoyStartupRegisters::loadAPURegistersDMG(gbtest::APU& apu)
{
    // DMG - APU
    SoundControlRegisters& soundControlRegisters = apu.getSoundControlRegisters();

    soundControlRegisters.channelControl.raw = 0x77;
    soundControlRegisters.soundOutputTerminalSelection.raw = 0xF3;
    soundControlRegisters.soundOnOff.raw = 0xF1;

    // DMG - APU Channel 1
    Channel1Registers& channel1Registers = apu.getChannel1().getRegisters();

    channel1Registers.sweep.raw = 0x80;
    channel1Registers.soundLengthWavePatternDuty.raw = 0xBF;
    channel1Registers.volumeEnvelope.raw = 0xF3;
    channel1Registers.frequencyLow.raw = 0xFF;
    channel1Registers.frequencyHigh.raw = 0xBF;

    // DMG - APU Channel 2
    Channel2Registers& channel2Registers = apu.getChannel2().getRegisters();

    channel2Registers.soundLengthWavePatternDuty.raw = 0x3F;
    channel2Registers.volumeEnvelope.raw = 0x00;
    channel2Registers.frequencyLow.raw = 0xFF;
    channel2Registers.frequencyHigh.raw = 0xBF;

    // DMG - APU Channel 3
    Channel3Registers& channel3Registers = apu.getChannel3().getRegisters();

    channel3Registers.soundOnOff.raw = 0x7F;
    channel3Registers.soundLength.raw = 0xFF;
    channel3Registers.selectOutputLevel.raw = 0x9F;
    channel3Registers.frequencyLow.raw = 0xFF;
    channel3Registers.frequencyHigh.raw = 0xBF;

    // DMG - APU Channel 4
    Channel4Registers& channel4Registers = apu.getChannel4().getRegisters();

    channel4Registers.soundLength.raw = 0xFF;
    channel4Registers.volumeEnvelope.raw = 0x00;
    channel4Registers.polynomialCounter.raw = 0x00;
    channel4Registers.counterConsecutiveAndInitial.raw = 0xBF;
}

void gbtest::GameBoyStartupRegisters::loadCPURegistersCGB(gbtest::LR35902Registers& regs)
{
    // DMG - CPU
    regs.af = 0x1180;
    regs.bc = 0x0000;
    regs.de = 0xFF56;
    regs.hl = 0x000D;
    regs.pc = 0x0100;
    regs.sp = 0xFFFE;
}

void gbtest::GameBoyStartupRegisters::loadDividerRegistersCGB(gbtest::Divider& divider)
{
    // DMG - Divider
    divider.getRegister().value = 0xAB;
}

void gbtest::GameBoyStartupRegisters::loadTimerRegistersCGB(gbtest::Timer& timer)
{
    // DMG - Timer
    timer.getTimerCounterRegister().raw = 0x00;
    timer.getTimerModuloRegister().raw = 0x00;
    timer.getTimerControlRegister().raw = 0xF8;
}

void gbtest::GameBoyStartupRegisters::loadPPURegistersCGB(gbtest::PPU& ppu)
{
    // DMG - PPU
    PPURegisters& ppuRegisters = ppu.getPpuRegisters();

    ppuRegisters.lcdControl.raw = 0x91;
    ppuRegisters.lcdStatus.raw = 0x85;

    ppuRegisters.lcdPositionAndScrolling.xScroll = 0x00;
    ppuRegisters.lcdPositionAndScrolling.yScroll = 0x00;
    ppuRegisters.lcdPositionAndScrolling.lyCompare = 0x00;
    ppuRegisters.lcdPositionAndScrolling.xWindowPosition = 0x00;
    ppuRegisters.lcdPositionAndScrolling.yWindowPosition = 0x00;

    ppuRegisters.dmgPalettes.bgPaletteData.raw = 0xFC;
    ppuRegisters.dmgPalettes.objectPaletteData0.raw = 0xFF;
    ppuRegisters.dmgPalettes.objectPaletteData1.raw = 0xFF;
}

void gbtest::GameBoyStartupRegisters::loadAPURegistersCGB(gbtest::APU& apu)
{
    // DMG - APU
    SoundControlRegisters& soundControlRegisters = apu.getSoundControlRegisters();

    soundControlRegisters.channelControl.raw = 0x77;
    soundControlRegisters.soundOutputTerminalSelection.raw = 0xF3;
    soundControlRegisters.soundOnOff.raw = 0xF1;

    // DMG - APU Channel 1
    Channel1Registers& channel1Registers = apu.getChannel1().getRegisters();

    channel1Registers.sweep.raw = 0x80;
    channel1Registers.soundLengthWavePatternDuty.raw = 0xBF;
    channel1Registers.volumeEnvelope.raw = 0xF3;
    channel1Registers.frequencyLow.raw = 0xFF;
    channel1Registers.frequencyHigh.raw = 0xBF;

    // DMG - APU Channel 2
    Channel2Registers& channel2Registers = apu.getChannel2().getRegisters();

    channel2Registers.soundLengthWavePatternDuty.raw = 0x3F;
    channel2Registers.volumeEnvelope.raw = 0x00;
    channel2Registers.frequencyLow.raw = 0xFF;
    channel2Registers.frequencyHigh.raw = 0xBF;

    // DMG - APU Channel 3
    Channel3Registers& channel3Registers = apu.getChannel3().getRegisters();

    channel3Registers.soundOnOff.raw = 0x7F;
    channel3Registers.soundLength.raw = 0xFF;
    channel3Registers.selectOutputLevel.raw = 0x9F;
    channel3Registers.frequencyLow.raw = 0xFF;
    channel3Registers.frequencyHigh.raw = 0xBF;

    // DMG - APU Channel 4
    Channel4Registers& channel4Registers = apu.getChannel4().getRegisters();

    channel4Registers.soundLength.raw = 0xFF;
    channel4Registers.volumeEnvelope.raw = 0x00;
    channel4Registers.polynomialCounter.raw = 0x00;
    channel4Registers.counterConsecutiveAndInitial.raw = 0xBF;
}
