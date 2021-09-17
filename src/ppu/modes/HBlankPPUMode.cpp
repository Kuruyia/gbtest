#include "HBlankPPUMode.h"

inline gbtest::PPUModeType gbtest::HBlankPPUMode::getModeType()
{
    return PPUModeType::HBlank;
}

void gbtest::HBlankPPUMode::tick()
{
    PPUMode::tick();
}
