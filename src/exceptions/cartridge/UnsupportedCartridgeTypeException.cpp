#include "UnsupportedCartridgeTypeException.h"

gbtest::UnsupportedCartridgeTypeException::UnsupportedCartridgeTypeException(CartridgeHeaderCartridgeType cartridgeType)
        : std::runtime_error("This cartridge type is not supported.")
        , m_cartridgeType(cartridgeType)
{

}

CartridgeHeaderCartridgeType gbtest::UnsupportedCartridgeTypeException::getCartridgeType() const
{
    return m_cartridgeType;
}
