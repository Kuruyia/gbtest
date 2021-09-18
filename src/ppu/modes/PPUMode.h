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

    virtual void restart();
    [[nodiscard]] bool isFinished() const;

    virtual void executeMode() = 0;

    void tick() override;

protected:
    bool m_finished;
    unsigned m_cyclesToWait;

}; // class PPUMode

} // namespace gbtest

#endif //GBTEST_PPUMODE_H
