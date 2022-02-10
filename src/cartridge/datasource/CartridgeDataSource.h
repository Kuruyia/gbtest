#ifndef GBTEST_CARTRIDGEDATASOURCE_H
#define GBTEST_CARTRIDGEDATASOURCE_H

#include <cstdint>

namespace gbtest {

class CartridgeDataSource {

public:
    CartridgeDataSource() = default;
    virtual ~CartridgeDataSource() = default;

    virtual bool read(uint32_t addr, uint8_t& val) = 0;

}; // class CartridgeDataSource

} // namespace gbtest

#endif //GBTEST_CARTRIDGEDATASOURCE_H
