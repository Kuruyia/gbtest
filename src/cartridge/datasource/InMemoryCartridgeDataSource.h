#ifndef GBTEST_INMEMORYCARTRIDGEDATASOURCE_H
#define GBTEST_INMEMORYCARTRIDGEDATASOURCE_H

#include <cstddef>
#include <vector>

#include "CartridgeDataSource.h"

namespace gbtest {

class InMemoryCartridgeDataSource
        : public CartridgeDataSource {

public:
    using InMemoryCartridgeStorage_t = std::vector<uint8_t>;

    InMemoryCartridgeDataSource() = default;
    ~InMemoryCartridgeDataSource() override = default;

    InMemoryCartridgeStorage_t& getStorage();
    const InMemoryCartridgeStorage_t& getStorage() const;

    bool read(uint32_t addr, uint8_t& val) override;

private:
    InMemoryCartridgeStorage_t m_rom;

}; // class InMemoryCartridgeDataSource

} // namespace gbtest

#endif //GBTEST_INMEMORYCARTRIDGEDATASOURCE_H
