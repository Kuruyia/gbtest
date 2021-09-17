#ifndef GBTEST_OAMSEARCHPPUMODE_H
#define GBTEST_OAMSEARCHPPUMODE_H

#include "PPUMode.h"
#include "PPUModeType.h"

namespace gbtest {

class OAMSearchPPUMode
        : public PPUMode {

public:
    OAMSearchPPUMode() = default;
    ~OAMSearchPPUMode() override = default;

    [[nodiscard]] static PPUModeType getModeType();

    void tick() override;

}; // class OAMSearchPPUMode

} // namespace gbtest

#endif //GBTEST_OAMSEARCHPPUMODE_H
