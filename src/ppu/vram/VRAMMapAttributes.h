#ifndef GBTEST_VRAMMAPATTRIBUTES_H
#define GBTEST_VRAMMAPATTRIBUTES_H

#include <array>
#include <cstddef>
#include <cstdint>

#include "../../platform/bus/BusProvider.h"
#include "VRAMMapAttributesData.h"

namespace gbtest {

class VRAMMapAttributes
        : public BusProvider {

public:
    VRAMMapAttributes();
    ~VRAMMapAttributes() override = default;

    [[nodiscard]] const VRAMMapAttributesData& getTileAttributesFromTileMap(size_t offset, uint8_t whichMap) const;

    void clear();

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

private:
    std::array<VRAMMapAttributesData, 0x800> m_memory;

}; // class VRAMMapAttributes

} // namespace gbtest

#endif //GBTEST_VRAMMAPATTRIBUTES_H
