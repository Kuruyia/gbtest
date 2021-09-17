#include "OAMSearchPPUMode.h"

inline gbtest::PPUModeType gbtest::OAMSearchPPUMode::getModeType()
{
    return PPUModeType::OAM_Search;
}

void gbtest::OAMSearchPPUMode::tick()
{
    PPUMode::tick();
}
