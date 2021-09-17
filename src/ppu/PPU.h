#ifndef GBTEST_PPU_H
#define GBTEST_PPU_H

#include "modes/PPUModeManager.h"
#include "oam/OAM.h"
#include "oam/OAMDMA.h"
#include "vram/VRAM.h"

#include "../platform/bus/BusProvider.h"
#include "../platform/bus/Bus.h"
#include "../utils/Tickable.h"

namespace gbtest {

class PPU
        : public BusProvider, public Tickable {

public:
    explicit PPU(Bus& bus);
    ~PPU() override = default;

    [[nodiscard]] PPUModeManager& getModeManager();
    [[nodiscard]] const PPUModeManager& getModeManager() const;

    [[nodiscard]] OAM& getOam();
    [[nodiscard]] const OAM& getOam() const;

    [[nodiscard]] OAMDMA& getOamDma();
    [[nodiscard]] const OAMDMA& getOamDma() const;

    [[nodiscard]] VRAM& getVram();
    [[nodiscard]] const VRAM& getVram() const;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    void tick() override;

private:
    PPUModeManager m_modeManager;

    OAM m_oam;
    OAMDMA m_oamDma;

    VRAM m_vram;

}; // class PPU

} // namespace gbtest

#endif //GBTEST_PPU_H
