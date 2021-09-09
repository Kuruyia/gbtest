#ifndef GBTEST_OAMDMA_H
#define GBTEST_OAMDMA_H

#include "../../platform/bus/BusProvider.h"
#include "../../utils/Tickable.h"

namespace gbtest {

class OAMDMA
        : public BusProvider, public Tickable {

public:
    ~OAMDMA() override = default;

    void tick() override;

    bool read(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool write(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool readOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool writeOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

}; // class OAMDMA

} // namespace gbtest

#endif //GBTEST_OAMDMA_H
