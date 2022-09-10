#ifndef GBTEST_AUDIOWAVE_H
#define GBTEST_AUDIOWAVE_H

#include <array>
#include <cstddef>
#include <cstdint>

#include "../../utils/Tickable.h"

namespace gbtest {

class AudioWave
        : public Tickable {

public:
    using WavePatternSample = uint8_t;
    using WavePatternData = std::array<WavePatternSample, 16>;

    AudioWave();
    ~AudioWave() override = default;

    [[nodiscard]] WavePatternData& getWavePatternData();
    [[nodiscard]] const WavePatternData& getWavePatternData() const;

    void setEnabled(bool enabled);
    [[nodiscard]] bool isEnabled() const;

    void setFrequency(uint16_t frequency);
    [[nodiscard]] uint16_t getFrequency() const;

    void setVolume(uint8_t volume);
    [[nodiscard]] uint8_t getVolume() const;

    void writeWavePatternData(size_t idx, uint8_t val);
    [[nodiscard]] uint8_t readWavePatternData(size_t idx) const;

    [[nodiscard]] float getSample() const;

    void doTrigger();

    void tick(bool isDoubleSpeedTick) override;

private:
    WavePatternData m_wavePatternData;

    uint8_t m_currentSampleIdx;
    float m_currentSample;

    bool m_enabled;
    uint16_t m_frequency;
    uint8_t m_volume;

    unsigned m_tickCountdown;

}; // class AudioWave

} // namespace gbtest

#endif //GBTEST_AUDIOWAVE_H
