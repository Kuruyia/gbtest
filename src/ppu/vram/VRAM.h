#ifndef GBTEST_VRAM_H
#define GBTEST_VRAM_H

#include "VRAMMapAttributes.h"
#include "VRAMTileData.h"
#include "VRAMTileMaps.h"

#include "../../platform/bus/BusProvider.h"

namespace gbtest {

class VRAM
        : public BusProvider {

public:
    VRAM();
    ~VRAM() override = default;

    [[nodiscard]] VRAMTileData& getCurrentVramTileData();
    [[nodiscard]] const VRAMTileData& getCurrentVramTileData() const;

    [[nodiscard]] VRAMTileData& getVramTileData0();
    [[nodiscard]] const VRAMTileData& getVramTileData0() const;

    [[nodiscard]] VRAMTileData& getVramTileData1();
    [[nodiscard]] const VRAMTileData& getVramTileData1() const;

    [[nodiscard]] VRAMTileMaps& getVramTileMaps();
    [[nodiscard]] const VRAMTileMaps& getVramTileMaps() const;

    void setReadBlocked(bool readBlocked);
    [[nodiscard]] bool isReadBlocked() const;

    void setCGBMode(bool cgbMode);
    [[nodiscard]] bool isCGBMode() const;

    void setCurrentBank(uint8_t bank);
    [[nodiscard]] uint8_t getCurrentBank() const;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

private:
    VRAMTileData m_vramTileData0;
    VRAMTileData m_vramTileData1;

    VRAMMapAttributes m_vramMapAttributes;
    VRAMTileMaps m_vramTileMaps;

    bool m_readBlocked;
    bool m_cgbMode;
    uint8_t m_currentBank;

}; // class VRAM

} // namespace gbtest

#endif //GBTEST_VRAM_H
