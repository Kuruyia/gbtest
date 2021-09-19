#ifndef GBTEST_VRAMTILEMAPS_H
#define GBTEST_VRAMTILEMAPS_H

#include <array>
#include <cinttypes>

#include "../../platform/bus/BusProvider.h"

namespace gbtest {

class VRAMTileMaps
        : public BusProvider {

public:
    VRAMTileMaps();
    ~VRAMTileMaps() override = default;

    [[nodiscard]] uint8_t getTileNumberFromTileMap(size_t offset, uint8_t whichMap) const;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

private:
    std::array<uint8_t, 0x800> m_memory;

}; // class VRAMTileMaps

} // namespace gbtest

#endif //GBTEST_VRAMTILEMAPS_H
