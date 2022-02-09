#ifndef GBTEST_OAM_H
#define GBTEST_OAM_H

#include <array>
#include <cstddef>

#include "OAMEntry.h"
#include "../../platform/bus/BusProvider.h"

namespace gbtest {

class OAM
        : public BusProvider {

public:
    OAM();
    ~OAM() override = default;

    void writeRawValue(size_t offset, uint8_t val);
    void readRawValue(size_t offset, uint8_t& val) const;

    void setOamEntry(const OAMEntry& entry, size_t idx);
    [[nodiscard]] const OAMEntry& getOamEntry(size_t idx) const;
    [[nodiscard]] OAMEntry& getOamEntry(size_t idx);

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

private:
    std::array<OAMEntry, 40> m_oamEntries;

}; // class OAM

} // namespace gbtest

#endif //GBTEST_OAM_H
