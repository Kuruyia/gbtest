#ifndef GBTEST_CARTRIDGEMBC1_H
#define GBTEST_CARTRIDGEMBC1_H

#include <array>
#include <cstdint>
#include <memory>

#include "BaseCartridge.h"

namespace gbtest {

class CartridgeMBC1
        : public BaseCartridge {

public:
    explicit CartridgeMBC1(std::unique_ptr<CartridgeDataSource> cartridgeDataSource);
    ~CartridgeMBC1() override = default;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

private:
    std::array<uint8_t, 0x8000> m_ram;

    uint8_t m_currentRomBank;
    uint8_t m_currentRamAndUpperRomBank;

    bool m_advancedBankingMode;
    bool m_ramEnable;

}; // class CartridgeMBC1

} // namespace gbtest

#endif //GBTEST_CARTRIDGEMBC1_H
