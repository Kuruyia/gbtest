#ifndef GBTEST_BUSNOHANDLEREXCEPTION_H
#define GBTEST_BUSNOHANDLEREXCEPTION_H

#include <stdexcept>

namespace gbtest {

class BusNoHandlerException
        : std::runtime_error {

public:
    BusNoHandlerException(uint16_t addr, bool isWrite);

}; // class BusNoHandlerException

} // namespace gbtest

#endif //GBTEST_BUSNOHANDLEREXCEPTION_H
