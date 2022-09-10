#ifndef GBTEST_VOLUMEENVELOPE_H
#define GBTEST_VOLUMEENVELOPE_H

#include <cstdint>

#include "../../utils/Tickable.h"

namespace gbtest {

class VolumeEnvelope
        : public Tickable {

public:
    VolumeEnvelope();
    ~VolumeEnvelope() override = default;

    void setVolume(uint8_t volume);
    [[nodiscard]] uint8_t getVolume() const;

    void setIncreasing(bool increasing);
    [[nodiscard]] bool isIncreasing() const;

    void setPeriod(uint8_t period);
    [[nodiscard]] uint8_t getPeriod() const;

    [[nodiscard]] uint8_t getCurrentVolume() const;

    void doTrigger();

    void tick(bool isDoubleSpeedTick) override;

private:
    uint8_t m_volume;
    bool m_increasing;
    uint8_t m_period;

    uint8_t m_currentVolume;
    uint8_t m_countdown;

}; // class VolumeEnvelope

} // namespace gbtest

#endif //GBTEST_VOLUMEENVELOPE_H
