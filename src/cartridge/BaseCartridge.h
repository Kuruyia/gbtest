#ifndef GBTEST_BASECARTRIDGE_H
#define GBTEST_BASECARTRIDGE_H

#include "datasource/CartridgeDataSource.h"
#include "../platform/bus/BusProvider.h"

namespace gbtest {

class BaseCartridge
        : public BusProvider {

public:
    explicit BaseCartridge(CartridgeDataSource& cartridgeDataSource);
    ~BaseCartridge() override = default;

protected:
    CartridgeDataSource& m_cartridgeDataSource;

}; // class BaseCartridge

} // namespace gbtest

#endif //GBTEST_BASECARTRIDGE_H
