#ifndef GBTEST_APU_H
#define GBTEST_APU_H

#include <array>

#include "channels/APUChannel2.h"

#include "../platform/bus/BusProvider.h"
#include "../platform/GameBoyFrequencies.h"
#include "../utils/Tickable.h"

namespace gbtest {

class APU
        : public BusProvider, public Tickable {

public:
    static constexpr unsigned MAX_SAMPLE_COUNT = 1024;
    static constexpr unsigned SAMPLE_RATE = 44100;
    static constexpr unsigned SAMPLE_EVERY_X_TICK = GAMEBOY_FREQUENCY / SAMPLE_RATE;

    using SampleBuffer = std::array<float, MAX_SAMPLE_COUNT>;

    APU();
    ~APU() override = default;

    [[nodiscard]] float sample() const;

    [[nodiscard]] const SampleBuffer& getSampleBuffer() const;
    [[nodiscard]] bool isSampleBufferFull() const;
    void resetSampling();

    void tick() override;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

private:
    SoundControlRegisters m_soundControlRegisters;

    APUChannel2 m_apuChannel2;

    SampleBuffer m_samples;
    size_t m_sampleCount;
    unsigned m_sampleCountdown;

}; // class APU

} // namespace gbtest

#endif //GBTEST_APU_H
