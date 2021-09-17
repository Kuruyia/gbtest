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

    void tick() override;

private:
    bool m_finished;

}; // class PPUMode

} // namespace gbtest

#endif //GBTEST_PPUMODE_H
