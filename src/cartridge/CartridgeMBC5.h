#ifndef GBTEST_CARTRIDGEMBC5_H
#define GBTEST_CARTRIDGEMBC5_H

#include <array>
#include <cstdint>
#include <memory>

#include "BaseCartridge.h"

namespace gbtest {

class CartridgeMBC5
        : public BaseCartridge {

public:
    explicit CartridgeMBC5(std::unique_ptr<CartridgeDataSource> cartridgeDataSource);
    ~CartridgeMBC5() override = default;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

private:
    std::array<uint8_t, 0x20000> m_ram;

    uint16_t m_currentRomBank;
    uint8_t m_currentRamBank;

    bool m_ramEnable;

}; // class CartridgeMBC5

} // namespace gbtest

#endif //GBTEST_CARTRIDGEMBC5_H
