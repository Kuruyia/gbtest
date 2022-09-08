#ifndef GBTEST_UNSUPPORTEDCARTRIDGETYPEEXCEPTION_H
#define GBTEST_UNSUPPORTEDCARTRIDGETYPEEXCEPTION_H

#include <stdexcept>

#include "../../cartridge/CartridgeHeaderData.h"

namespace gbtest {

class UnsupportedCartridgeTypeException
        :
                public std::runtime_error {

public:
    explicit UnsupportedCartridgeTypeException(CartridgeHeaderCartridgeType cartridgeType);

    [[nodiscard]] CartridgeHeaderCartridgeType getCartridgeType() const;

private:
    CartridgeHeaderCartridgeType m_cartridgeType;

}; // class UnsupportedCartridgeTypeException

} // namespace gbtest

#endif //GBTEST_UNSUPPORTEDCARTRIDGETYPEEXCEPTION_H
