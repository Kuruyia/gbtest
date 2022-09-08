#ifndef GBTEST_GAMEBOYSTARTUPREGISTERS_H
#define GBTEST_GAMEBOYSTARTUPREGISTERS_H

#include "../../apu/APU.h"
#include "../../cartridge/BaseCartridge.h"
#include "../../cpu/LR35902.h"
#include "../../joypad/Joypad.h"
#include "../../memory/Memory.h"
#include "../../ppu/PPU.h"
#include "../../timer/Divider.h"
#include "../../timer/Timer.h"
#include "GameBoyRevisionType.h"

namespace gbtest {

class GameBoyStartupRegisters {

public:
    explicit GameBoyStartupRegisters(GameBoyRevisionType revisionType);

    void loadCPURegisters(LR35902Registers& regs) const;
    void loadDividerRegisters(Divider& divider) const;
    void loadTimerRegisters(Timer& timer) const;
    void loadPPURegisters(PPU& ppu) const;
    void loadAPURegisters(APU& apu) const;

private:
    GameBoyRevisionType m_revisionType;

    // DMG
    static void loadCPURegistersDMG(LR35902Registers& regs);
    static void loadDividerRegistersDMG(Divider& divider);
    static void loadTimerRegistersDMG(Timer& timer);
    static void loadPPURegistersDMG(PPU& ppu);
    static void loadAPURegistersDMG(APU& apu);

    // CGB
    static void loadCPURegistersCGB(LR35902Registers& regs);
    static void loadDividerRegistersCGB(Divider& divider);
    static void loadTimerRegistersCGB(Timer& timer);
    static void loadPPURegistersCGB(PPU& ppu);
    static void loadAPURegistersCGB(APU& apu);

}; // class GameBoyStartupRegisters

} // namespace gbtest

#endif //GBTEST_GAMEBOYSTARTUPREGISTERS_H
