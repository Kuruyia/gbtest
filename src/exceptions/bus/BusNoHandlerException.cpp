#include <string>

#include "BusNoHandlerException.h"

gbtest::BusNoHandlerException::BusNoHandlerException(uint16_t addr, bool isWrite)
        : std::runtime_error(
        "No bus provider was registered for handling " + std::string(isWrite ? "write" : "read") + " access at "
                + std::to_string(addr))
{

}
