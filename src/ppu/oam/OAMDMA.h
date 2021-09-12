#ifndef GBTEST_OAMDMA_H
#define GBTEST_OAMDMA_H

#include "../../platform/bus/Bus.h"
#include "../../platform/bus/BusProvider.h"
#include "../../utils/Tickable.h"

namespace gbtest {

class OAMDMA
        : public BusProvider, public Tickable {

public:
    OAMDMA(Bus& bus);
    ~OAMDMA() override = default;

    void startTransfer(uint8_t sourceAddressHigh);
    [[nodiscard]] bool isTransferring() const;

    void tick() override;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

private:
    bool m_transferring;
    uint8_t m_currentAddressLow;
    uint8_t m_sourceAddressHigh;

    Bus& m_bus;

}; // class OAMDMA

} // namespace gbtest

#endif //GBTEST_OAMDMA_H
