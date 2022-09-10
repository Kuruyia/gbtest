#ifndef GBTEST_CARTRIDGERTCPERIPHERAL_H
#define GBTEST_CARTRIDGERTCPERIPHERAL_H

#include <cstdint>

#include "CartridgeRTCPeripheralRegisters.h"
#include "../../utils/Tickable.h"

namespace gbtest {

class CartridgeRTCPeripheral
        : public Tickable {

public:
    CartridgeRTCPeripheral();
    ~CartridgeRTCPeripheral() override = default;

    void tick(bool isDoubleSpeedTick) override;

    void latch();

    [[nodiscard]] const CartridgeRTCPeripheralRegisters& getRegisters() const;
    CartridgeRTCPeripheralRegisters& getRegisters();

    [[nodiscard]] const CartridgeRTCPeripheralRegisters& getLatchedRegisters() const;
    CartridgeRTCPeripheralRegisters& getLatchedRegisters();

private:
    CartridgeRTCPeripheralRegisters m_registers;
    CartridgeRTCPeripheralRegisters m_latchedRegisters;

    uint32_t m_tickCounter;

}; // class CartridgeRTCPeripheral

} // namespace gbtest

#endif //GBTEST_CARTRIDGERTCPERIPHERAL_H
