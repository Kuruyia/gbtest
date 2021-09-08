#ifndef GBTEST_BUSPROVIDER_H
#define GBTEST_BUSPROVIDER_H

#include <cstdint>

namespace gbtest {

class BusProvider {

public:
    virtual ~BusProvider() = default;

    virtual bool read(uint16_t addr, uint8_t& val) const = 0;
    virtual bool write(uint16_t addr, uint8_t val) = 0;

    virtual bool doesAuthorizeAccess(uint16_t addr) = 0;

}; // class BusProvider

} // namespace gbtest

#endif //GBTEST_BUSPROVIDER_H
