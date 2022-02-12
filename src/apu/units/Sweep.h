#ifndef GBTEST_SWEEP_H
#define GBTEST_SWEEP_H

#include <cstdint>

#include "AudioPulseWave.h"
#include "../../utils/Tickable.h"

namespace gbtest {

class Sweep
        : public Tickable {

public:
    explicit Sweep(AudioPulseWave& audioPulseWave);
    ~Sweep() override = default;

    [[nodiscard]] unsigned getShadowFrequency() const;

    [[nodiscard]] bool isChannelDisabled() const;

    void setPeriod(uint8_t period);
    [[nodiscard]] uint8_t getPeriod() const;

    void setIncreasing(bool increasing);
    [[nodiscard]] bool isIncreasing() const;

    void setSweepShift(uint8_t sweepShift);
    [[nodiscard]] uint8_t getSweepShift() const;

    void doTrigger(uint8_t period);

    void tick() override;

private:
    AudioPulseWave& m_audioPulseWave;

    unsigned m_shadowFrequency;
    bool m_channelDisabled;

    uint8_t m_period;
    bool m_increasing;
    uint8_t m_sweepShift;

}; // class Sweep

} // namespace gbtest

#endif //GBTEST_SWEEP_H
