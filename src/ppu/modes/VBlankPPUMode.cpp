#include "VBlankPPUMode.h"

inline gbtest::PPUModeType gbtest::VBlankPPUMode::getModeType()
{
    return PPUModeType::VBlank;
}

void gbtest::VBlankPPUMode::tick()
{
    PPUMode::tick();
}