#ifndef GBTEST_VRAMTILEDATA_H
#define GBTEST_VRAMTILEDATA_H

#include <array>
#include <cinttypes>

#include "../../platform/bus/BusProvider.h"

namespace gbtest {

class VRAMTileData
        : public BusProvider {

public:
    VRAMTileData() = default;
    ~VRAMTileData() override = default;

    [[nodiscard]] uint16_t getTileLineUsingFirstMethod(uint8_t tileNumber, uint8_t lineNumber) const;
    [[nodiscard]] uint16_t getTileLineUsingSecondMethod(int8_t tileNumber, uint8_t lineNumber) const;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

private:
    std::array<uint8_t, 0x1800> m_memory;

}; // class VRAMTileData

} // namespace gbtest

#endif //GBTEST_VRAMTILEDATA_H
