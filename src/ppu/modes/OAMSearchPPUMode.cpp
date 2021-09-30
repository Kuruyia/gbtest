#include <algorithm>
#include <iterator>

#include "OAMSearchPPUMode.h"

gbtest::OAMSearchPPUMode::OAMSearchPPUMode(const PPURegisters& ppuRegisters, const OAM& oam)
        : m_spriteBuffer()
        , m_oamIdx(0)
        , m_ppuRegisters(ppuRegisters)
        , m_oam(oam)
{

}

inline gbtest::PPUModeType gbtest::OAMSearchPPUMode::getModeType()
{
    return PPUModeType::OAM_Search;
}

const gbtest::SpriteBuffer& gbtest::OAMSearchPPUMode::getSpriteBuffer() const
{
    return m_spriteBuffer;
}

void gbtest::OAMSearchPPUMode::restart()
{
    PPUMode::restart();

    m_spriteBuffer.clear();
    m_oamIdx = 0;
}

void gbtest::OAMSearchPPUMode::executeMode()
{
    // Check the current sprite if we still have room
    if (m_spriteBuffer.getSize() < 10) {
        checkCurrentSprite();
    }

    ++m_oamIdx;

    // Each OAM check takes 2 cycles
    m_cyclesToWait = 2;

    if (m_oamIdx == 40) {
        // There are no more sprites to check
        m_finished = true;

        // Sort the sprite buffer by the sprite's X coordinate
        auto iterEnd = m_spriteBuffer.getRawBuffer().begin();
        std::advance(iterEnd, m_spriteBuffer.getSize());

        std::sort(m_spriteBuffer.getRawBuffer().begin(), iterEnd, [](const OAMEntry& a, const OAMEntry& b) {
            return a.xPosition < b.xPosition;
        });
    }
}

void gbtest::OAMSearchPPUMode::checkCurrentSprite()
{
    // Fetch the sprite to check
    const OAMEntry& oamEntry = m_oam.getOamEntry(m_oamIdx);

    // Check if the sprite is on this line
    const unsigned spriteHeight = (m_ppuRegisters.lcdControl.objSize == 0 ? 8 : 16);
    const uint8_t correctedYLcdCoordinate = m_ppuRegisters.lcdPositionAndScrolling.yLcdCoordinate + 16;

    if (oamEntry.xPosition > 0
            && correctedYLcdCoordinate >= oamEntry.yPosition
            && correctedYLcdCoordinate < (oamEntry.yPosition + spriteHeight)) {
        // This sprite will be shown on this line, store it
        m_spriteBuffer.push(oamEntry);
    }
}
