#ifndef GBTEST_CARTRIDGEMBC3_H
#define GBTEST_CARTRIDGEMBC3_H

#include <array>
#include <cstdint>
#include <memory>

#include "peripherals/CartridgeRTCPeripheral.h"
#include "BaseCartridge.h"

namespace gbtest {

class CartridgeMBC3
        : public BaseCartridge {

public:
    explicit CartridgeMBC3(std::unique_ptr<CartridgeDataSource> cartridgeDataSource);
    ~CartridgeMBC3() override = default;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    void tick(bool isDoubleSpeedTick) override;

private:
    std::array<uint8_t, 0x8000> m_ram;

    uint8_t m_currentRomBank;
    uint8_t m_currentRamBankAndRTCRegister;

    bool m_ramAndRTCEnable;

    CartridgeRTCPeripheral m_rtcPeripheral;
    bool m_startedLatchSequence;

}; // class CartridgeMBC3

} // namespace gbtest

#endif //GBTEST_CARTRIDGEMBC3_H
