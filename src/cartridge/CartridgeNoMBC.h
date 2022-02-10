#ifndef GBTEST_CARTRIDGENOMBC_H
#define GBTEST_CARTRIDGENOMBC_H

#include "BaseCartridge.h"

namespace gbtest {

class CartridgeNoMBC
        : public BaseCartridge {

public:
    explicit CartridgeNoMBC(CartridgeDataSource& cartridgeDataSource);
    ~CartridgeNoMBC() override = default;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

}; // class CartridgeNoMBC

} // namespace gbtest

#endif //GBTEST_CARTRIDGENOMBC_H
