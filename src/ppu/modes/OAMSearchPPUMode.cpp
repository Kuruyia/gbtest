#include "OAMSearchPPUMode.h"

gbtest::OAMSearchPPUMode::OAMSearchPPUMode(PPURegisters& ppuRegisters, OAM& oam)
        : m_spriteBuffer()
        , m_spriteBufferSize(0)
        , m_oamIdx(0)
        , m_ppuRegisters(ppuRegisters)
        , m_oam(oam)
{

}

inline gbtest::PPUModeType gbtest::OAMSearchPPUMode::getModeType()
{
    return PPUModeType::OAM_Search;
}

const std::array<uint8_t, 10>& gbtest::OAMSearchPPUMode::getSpriteBuffer() const
{
    return m_spriteBuffer;
}

size_t gbtest::OAMSearchPPUMode::getSpriteBufferSize() const
{
    return m_spriteBufferSize;
}

void gbtest::OAMSearchPPUMode::restart()
{
    PPUMode::restart();

    m_spriteBufferSize = 0;
    m_oamIdx = 0;
}

void gbtest::OAMSearchPPUMode::executeMode()
{
    // Check the current sprite if we still have room
    if (m_spriteBufferSize < 10) {
        checkCurrentSprite();
    }

    ++m_oamIdx;

    if (m_oamIdx < 40) {
        // Each OAM check takes 2 cycles
        m_cyclesToWait = 2;
    }
    else {
        // There are no more sprites to check
        m_finished = true;
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
        m_spriteBuffer.at(m_spriteBufferSize) = m_oamIdx;
        ++m_spriteBufferSize;
    }
}
