#include "UnknownPPUModeException.h"

gbtest::UnknownPPUModeException::UnknownPPUModeException()
    : std::runtime_error("The PPU is in an unknown mode.")
{

}
