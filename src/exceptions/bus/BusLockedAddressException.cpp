#include <string>

#include "BusLockedAddressException.h"

BusLockedAddressException::BusLockedAddressException(uint16_t addr)
        : std::runtime_error("A memory access occurred at " + std::to_string(addr) + ", but the address is locked")
{

}
