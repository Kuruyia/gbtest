#ifndef GBTEST_HBLANKPPUMODE_H
#define GBTEST_HBLANKPPUMODE_H

#include "PPUMode.h"
#include "PPUModeType.h"

namespace gbtest {

class HBlankPPUMode
        : public PPUMode {

public:
    HBlankPPUMode();
    ~HBlankPPUMode() override = default;

    void setBlankingCycleCount(unsigned blankingCycleCount);
    [[nodiscard]] unsigned getBlankingCycleCount() const;

    [[nodiscard]] static PPUModeType getModeType();

    void restart() override;

    void executeMode() override;

private:
    bool m_blanking;
    unsigned m_blankingCycleCount;

}; // class HBlankPPUMode

} // namespace gbtest

#endif //GBTEST_HBLANKPPUMODE_H
