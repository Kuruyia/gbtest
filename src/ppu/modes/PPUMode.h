#ifndef GBTEST_PPUMODE_H
#define GBTEST_PPUMODE_H

#include "PPUModeType.h"
#include "../../utils/Tickable.h"

namespace gbtest {

class PPUMode
        : public Tickable {

public:
    PPUMode();
    ~PPUMode() override = default;

    virtual void setCGBMode(bool cgbMode);
    [[nodiscard]] bool isCGBMode() const;

    virtual void restart();
    [[nodiscard]] bool isFinished() const;
    [[nodiscard]] bool isFullyFinished() const;

    virtual void executeMode() = 0;

    void tick() override;

protected:
    bool m_cgbMode;
    bool m_finished;
    unsigned m_cyclesToWait;

}; // class PPUMode

} // namespace gbtest

#endif //GBTEST_PPUMODE_H
