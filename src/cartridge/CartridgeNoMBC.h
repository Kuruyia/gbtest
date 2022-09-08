#ifndef GBTEST_CARTRIDGENOMBC_H
#define GBTEST_CARTRIDGENOMBC_H

#include <memory>

#include "BaseCartridge.h"

namespace gbtest {

class CartridgeNoMBC
        : public BaseCartridge {

public:
    explicit CartridgeNoMBC(std::unique_ptr<CartridgeDataSource> cartridgeDataSource);
    ~CartridgeNoMBC() override = default;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

}; // class CartridgeNoMBC

} // namespace gbtest

#endif //GBTEST_CARTRIDGENOMBC_H
