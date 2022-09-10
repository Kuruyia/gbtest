#ifndef GBTEST_BASECARTRIDGE_H
#define GBTEST_BASECARTRIDGE_H

#include <memory>

#include "datasource/CartridgeDataSource.h"
#include "CartridgeHeaderData.h"

#include "../platform/bus/BusProvider.h"
#include "../utils/Tickable.h"

namespace gbtest {

class BaseCartridge
        : public BusProvider, public Tickable {

public:
    explicit BaseCartridge(std::unique_ptr<CartridgeDataSource> cartridgeDataSource);
    ~BaseCartridge() override = default;

    void tick(bool isDoubleSpeedTick) override;

    [[nodiscard]] const CartridgeHeaderData& getHeaderData() const;

    [[nodiscard]] CartridgeMBCType getMBCType() const;

    static bool hasRAM(CartridgeHeaderCartridgeType cartridgeType);
    [[nodiscard]] bool hasRAM() const;

    static bool hasBattery(CartridgeHeaderCartridgeType cartridgeType);
    [[nodiscard]] bool hasBattery() const;

    static bool hasTimer(CartridgeHeaderCartridgeType cartridgeType);
    [[nodiscard]] bool hasTimer() const;

    static bool hasRumble(CartridgeHeaderCartridgeType cartridgeType);
    [[nodiscard]] bool hasRumble() const;

    static bool hasSensor(CartridgeHeaderCartridgeType cartridgeType);
    [[nodiscard]] bool hasSensor() const;

protected:
    std::unique_ptr<CartridgeDataSource> m_cartridgeDataSource;
    CartridgeHeaderData m_cartridgeHeaderData;

    void parseHeader();

}; // class BaseCartridge

} // namespace gbtest

#endif //GBTEST_BASECARTRIDGE_H
