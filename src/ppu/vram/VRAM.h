#ifndef GBTEST_VRAM_H
#define GBTEST_VRAM_H

#include "VRAMTileData.h"
#include "VRAMTileMaps.h"

#include "../../platform/bus/BusProvider.h"

namespace gbtest {

class VRAM
        : public BusProvider {

public:
    VRAM() = default;
    ~VRAM() override = default;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

private:
    VRAMTileData m_vramTileData;
    VRAMTileMaps m_vramTileMaps;

}; // class VRAM

} // namespace gbtest

#endif //GBTEST_VRAM_H
