#include "DrawingPPUMode.h"

inline gbtest::PPUModeType gbtest::DrawingPPUMode::getModeType()
{
    return PPUModeType::Drawing;
}

void gbtest::DrawingPPUMode::tick()
{
    PPUMode::tick();
}
