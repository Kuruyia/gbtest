#ifndef GBTEST_AUDIONOISE_H
#define GBTEST_AUDIONOISE_H

#include <cstdint>

#include "../../utils/Tickable.h"

namespace gbtest {

class AudioNoise
        : public Tickable {

public:
    static constexpr unsigned TIMER_CLOCK_FREQUENCY = 1048576;

    AudioNoise();
    ~AudioNoise() override = default;

    void setDivideRatio(uint8_t divideRatio);
    [[nodiscard]] uint8_t getDivideRatio() const;

    void setHalfWidth(bool halfWidth);
    [[nodiscard]] bool isHalfWidth() const;

    void setShiftClockFrequency(uint8_t shiftClockFrequency);
    [[nodiscard]] uint8_t getShiftClockFrequency() const;

    [[nodiscard]] float getSample() const;

    void doTrigger();

    void tick() override;

private:
    uint8_t m_divideRatio;
    bool m_halfWidth;
    uint8_t m_shiftClockFrequency;

    uint16_t m_lfsr;

    unsigned m_tickCountdown;

    [[nodiscard]] uint8_t getDivisor() const;
    void updateSample();

}; // class AudioNoise

} // namespace gbtest

#endif //GBTEST_AUDIONOISE_H
