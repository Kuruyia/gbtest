#ifndef GBTEST_APU_H
#define GBTEST_APU_H

#include <array>
#include <cstddef>

#include "channels/APUChannel2.h"

#include "../platform/bus/BusProvider.h"
#include "../platform/GameBoyFrequencies.h"
#include "../utils/Tickable.h"

namespace gbtest {

class APU
        : public BusProvider, public Tickable {

public:
    static constexpr unsigned SAMPLE_RATE = 44100;
    static constexpr unsigned CHANNELS = 2;
    static constexpr unsigned MAX_FRAME_COUNT = 1024 * CHANNELS;
    static constexpr unsigned SAMPLE_EVERY_X_TICK = GAMEBOY_FREQUENCY / SAMPLE_RATE;

    using AudioFramebuffer = std::array<float, MAX_FRAME_COUNT>;

    APU();
    ~APU() override = default;

    void sample(float& sampleLeft, float& sampleRight) const;

    [[nodiscard]] const AudioFramebuffer& getFramebuffer() const;
    [[nodiscard]] bool isFramebufferFull() const;
    [[nodiscard]] size_t getFrameCount() const;
    void consumeFrames(size_t frameCount);

    [[nodiscard]] SoundControlRegisters& getSoundControlRegisters();
    [[nodiscard]] const SoundControlRegisters& getSoundControlRegisters() const;

    [[nodiscard]] APUChannel2& getChannel2();
    [[nodiscard]] const APUChannel2& getChannel2() const;

    void tick() override;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

private:
    float m_tickProgress;

    SoundControlRegisters m_soundControlRegisters;

    APUChannel2 m_apuChannel2;

    AudioFramebuffer m_framebuffer;
    size_t m_sampleCount;
    unsigned m_sampleCountdown;

}; // class APU

} // namespace gbtest

#endif //GBTEST_APU_H
