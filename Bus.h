#ifndef GBTEST_BUS_H
#define GBTEST_BUS_H

#include <array>
#include <cinttypes>

namespace gbtest
{

class Bus
{

public:
    const uint8_t &read(const uint16_t &addr) const;
    void write(const uint16_t &addr, const uint8_t &data);

private:
    std::array<uint8_t, 0x10000> m_memory;

}; // class Bus

} // namespace gbtest

#endif //GBTEST_BUS_H
