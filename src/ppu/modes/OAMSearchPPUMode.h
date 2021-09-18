#ifndef GBTEST_OAMSEARCHPPUMODE_H
#define GBTEST_OAMSEARCHPPUMODE_H

#include <array>

#include "PPUMode.h"
#include "PPUModeType.h"

#include "../oam/OAM.h"
#include "../PPURegisters.h"

namespace gbtest {

class OAMSearchPPUMode
        : public PPUMode {

public:
    OAMSearchPPUMode(PPURegisters& ppuRegisters, OAM& oam);
    ~OAMSearchPPUMode() override = default;

    [[nodiscard]] static PPUModeType getModeType();

    [[nodiscard]] const std::array<uint8_t, 10>& getSpriteBuffer() const;
    [[nodiscard]] size_t getSpriteBufferSize() const;

    void restart() override;

    void executeMode() override;

private:
    std::array<uint8_t, 10> m_spriteBuffer;
    size_t m_spriteBufferSize;
    unsigned m_oamIdx;

    PPURegisters& m_ppuRegisters;
    OAM& m_oam;

    void checkCurrentSprite();

}; // class OAMSearchPPUMode

} // namespace gbtest

#endif //GBTEST_OAMSEARCHPPUMODE_H
