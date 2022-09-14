#ifndef GBTEST_APU_H
#define GBTEST_APU_H

#include <array>
#include <cstddef>

#include "channels/APUChannel1.h"
#include "channels/APUChannel2.h"
#include "channels/APUChannel3.h"
#include "channels/APUChannel4.h"

#include "units/FrameSequencer.h"

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
    static constexpr unsigned SAMPLE_EVERY_X_TICK = GAMEBOY_FREQUENCY / (SAMPLE_RATE * 2);

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

    [[nodiscard]] APUChannel1& getChannel1();
    [[nodiscard]] const APUChannel1& getChannel1() const;

    [[nodiscard]] APUChannel2& getChannel2();
    [[nodiscard]] const APUChannel2& getChannel2() const;

    [[nodiscard]] APUChannel3& getChannel3();
    [[nodiscard]] const APUChannel3& getChannel3() const;

    [[nodiscard]] APUChannel4& getChannel4();
    [[nodiscard]] const APUChannel4& getChannel4() const;

    void tick(bool isDoubleSpeedTick) override;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

private:
    SoundControlRegisters m_soundControlRegisters;

    FrameSequencer m_frameSequencer;
    APUChannel1 m_apuChannel1;
    APUChannel2 m_apuChannel2;
    APUChannel3 m_apuChannel3;
    APUChannel4 m_apuChannel4;

    AudioFramebuffer m_framebuffer;
    size_t m_sampleCount;
    unsigned m_sampleCountdown;

    bool m_tickDivider;

    void tickEnabled();
    void tickDisabled();

}; // class APU

} // namespace gbtest

#endif //GBTEST_APU_H
