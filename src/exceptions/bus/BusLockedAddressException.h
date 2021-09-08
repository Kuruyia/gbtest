#ifndef GBTEST_BUSLOCKEDADDRESSEXCEPTION_H
#define GBTEST_BUSLOCKEDADDRESSEXCEPTION_H

#include <stdexcept>

class BusLockedAddressException
        : public std::runtime_error {

public:
    explicit BusLockedAddressException(uint16_t addr);

}; // class BusLockedAddressException

#endif //GBTEST_BUSLOCKEDADDRESSEXCEPTION_H
