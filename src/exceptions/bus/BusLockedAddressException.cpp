#include <string>

#include "BusLockedAddressException.h"

gbtest::BusLockedAddressException::BusLockedAddressException(uint16_t addr, bool isWrite)
        : std::runtime_error(
        "A memory " + std::string(isWrite ? "write" : "read") + " occurred at " + std::to_string(addr)
                + ", but the address is locked")
{

}
