#ifndef GBTEST_BUSPROVIDER_H
#define GBTEST_BUSPROVIDER_H

#include <cstdint>

#include "BusRequestSource.h"

namespace gbtest {

class BusProvider {

public:
    virtual ~BusProvider() = default;

    virtual bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const = 0;
    virtual bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) = 0;

    virtual bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const = 0;
    virtual bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) = 0;

}; // class BusProvider

} // namespace gbtest

#endif //GBTEST_BUSPROVIDER_H
