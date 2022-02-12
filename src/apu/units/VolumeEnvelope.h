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

    void setIncreasing(bool increasing);
    [[nodiscard]] bool isIncreasing() const;

    void setVolume(uint8_t volume);
    [[nodiscard]] uint8_t getVolume() const;

    void setPeriod(uint8_t period);
    [[nodiscard]] uint8_t getPeriod() const;

    void doTrigger(uint8_t volume, uint8_t period);

    void tick() override;

private:
    bool m_increasing;

    uint8_t m_volume;
    uint8_t m_period;

}; // class VolumeEnvelope

} // namespace gbtest

#endif //GBTEST_VOLUMEENVELOPE_H
