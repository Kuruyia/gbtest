#ifndef GBTEST_OAMSEARCHPPUMODE_H
#define GBTEST_OAMSEARCHPPUMODE_H

#include <array>

#include "PPUMode.h"
#include "PPUModeType.h"

#include "../oam/OAM.h"
#include "../oam/OAMEntry.h"
#include "../PPURegisters.h"

namespace gbtest {

class OAMSearchPPUMode
        : public PPUMode {

public:
    OAMSearchPPUMode(const PPURegisters& ppuRegisters, const OAM& oam);
    ~OAMSearchPPUMode() override = default;

    [[nodiscard]] static PPUModeType getModeType();

    [[nodiscard]] const SpriteBuffer& getSpriteBuffer() const;
    [[nodiscard]] size_t getSpriteBufferSize() const;

    void restart() override;

    void executeMode() override;

private:
    SpriteBuffer m_spriteBuffer;
    size_t m_spriteBufferSize;
    unsigned m_oamIdx;

    const PPURegisters& m_ppuRegisters;
    const OAM& m_oam;

    void checkCurrentSprite();

}; // class OAMSearchPPUMode

} // namespace gbtest

#endif //GBTEST_OAMSEARCHPPUMODE_H
