#ifndef GBTEST_BUSLOCKEDADDRESSEXCEPTION_H
#define GBTEST_BUSLOCKEDADDRESSEXCEPTION_H

#include <stdexcept>

namespace gbtest {

class BusLockedAddressException
        : public std::runtime_error {

public:
    BusLockedAddressException(uint16_t addr, bool isWrite);

}; // class BusLockedAddressException

} // namespace gbtest

#endif //GBTEST_BUSLOCKEDADDRESSEXCEPTION_H
