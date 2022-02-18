#ifndef GBTEST_APUREGISTERS_H
#define GBTEST_APUREGISTERS_H

#include <cstdint>

namespace gbtest {

// [NR10] Channel 1 Sweep register
union SweepReg {
    struct {
        uint8_t nbSweepShift: 3;    // Number of sweep shift
        uint8_t sweepDirection: 1;  // Sweep direction (0: Decrease; 1: Increase)
        uint8_t sweepTime: 3;       // Sweep time
        uint8_t unused: 1;
    };
    uint8_t raw;
}; // union SweepReg

static_assert(sizeof(SweepReg) == 1, "Sweep register structure size is incorrect");

// [NR11/NR21] Channel 1/2 Sound Length/Wave Pattern Duty register
union SoundLengthWavePatternDutyReg {
    struct {
        uint8_t soundLengthData: 6; // Length of the sound
        uint8_t wavePatternDuty: 2; // Wave duty cycle
    };
    uint8_t raw;
}; // union SoundLengthWavePatternDutyReg

static_assert(sizeof(SoundLengthWavePatternDutyReg) == 1, "Sound Length/Wave Pattern Duty register structure size is incorrect");

// [NR12/22/42] Channel 1/2/4 Volume Envelope
union VolumeEnvelopeReg {
    struct {
        uint8_t nbEnvelopeSweep: 3;         // Number of envelope sweep (0: Stop operation)
        uint8_t envelopeDirection: 1;       // Envelope direction (0: Decrease; 1: Increase)
        uint8_t envelopeInitialVolume: 4;   // Initial volume of envelope (0: No sound)
    };
    uint8_t raw;
}; // union VolumeEnvelopeReg

static_assert(sizeof(VolumeEnvelopeReg) == 1, "Volume Envelope register structure size is incorrect");

// [NR13/23/33] Channel 1/2/3 Frequency Low
union FrequencyLowReg {
    uint8_t raw; // Lower 8 bits of the frequency
}; // union FrequencyLowReg

static_assert(sizeof(FrequencyLowReg) == 1, "Frequency Low register structure size is incorrect");

// [NR14/24/34] Channel 1/2/3 Frequency High
union FrequencyHighReg {
    struct {
        uint8_t frequencyHigh: 3;               // Higher 3 bits of the frequency
        uint8_t unused: 3;
        uint8_t counterConsecutiveSelection: 1; // 1: Stop output when length in NR11/NR21 expires
        uint8_t trigger: 1;                     // 1: Restart sound
    };
    uint8_t raw;
}; // union FrequencyHighReg

static_assert(sizeof(FrequencyHighReg) == 1, "Frequency High register structure size is incorrect");

// [NR30] Channel 3 Sound on/off
union WaveSoundOnOffReg {
    struct {
        uint8_t unused: 7;
        uint8_t soundOff: 1; // 0: Stop; 1: Playback
    };
    uint8_t raw;
}; // union WaveSoundOnOffReg

static_assert(sizeof(WaveSoundOnOffReg) == 1, "Sound on/off register structure size is incorrect");

// [NR31] Channel 3 Sound Length
union WaveSoundLengthReg {
    struct {
        uint8_t soundLengthData: 8; // Length of the sound
    };
    uint8_t raw;
}; // union WaveSoundLengthReg

static_assert(sizeof(WaveSoundLengthReg) == 1, "Wave sound length register structure size is incorrect");

// [NR32] Channel 3 Select output level
union SelectOutputLevelReg {
    struct {
        uint8_t unused1: 5;
        uint8_t selectOutputLevel: 2; // Volume of the sound (00b: Mute; 01b: 100%; 10b: 50%; 11b: 25%)
        uint8_t unused2: 1;
    };
    uint8_t raw;
}; // union SelectOutputLevelReg

static_assert(sizeof(SelectOutputLevelReg) == 1, "Select output level register structure size is incorrect");

// [NR41] Channel 4 Sound Length
union NoiseSoundLengthReg {
    struct {
        uint8_t soundLengthData: 6; // Length of the sound
        uint8_t unused: 2;
    };
    uint8_t raw;
}; // union NoiseSoundLengthReg

static_assert(sizeof(NoiseSoundLengthReg) == 1, "Noise sound length register structure size is incorrect");

// [NR43] Channel 4 Polynomial Counter
union PolynomialCounterReg {
    struct {
        uint8_t dividingRatio: 3;       // Divide ratio of the timer
        uint8_t counterWidth: 1;        // Width of the shift register (0: 15 bits; 1: 7 bits)
        uint8_t shiftClockFrequency: 4; // Frequency of the shift clock
    };
    uint8_t raw;
}; // union PolynomialCounterReg

static_assert(sizeof(PolynomialCounterReg) == 1, "Polynomial counter register structure size is incorrect");

// [NR44] Channel 4 Counter/consecutive; Initial
union CounterConsecutiveAndInitialReg {
    struct {
        uint8_t unused: 6;
        uint8_t counterConsecutiveSelection: 1; // 1: Stop output when length in NR11/NR21 expires
        uint8_t trigger: 1;                     // 1: Restart sound
    };
    uint8_t raw;
}; // union CounterConsecutiveAndInitialReg

static_assert(sizeof(CounterConsecutiveAndInitialReg) == 1,
        "Counter/consecutive and initial register structure size is incorrect");

// [NR50] Channel control / ON-OFF / Volume
union ChannelControlReg {
    struct {
        uint8_t so1OutputVolume: 3; // Output volume of the right channel
        uint8_t so1OutputVin: 1;    // Output Vin to the right channel (0: Disabled; 1: Enabled)
        uint8_t so2OutputVolume: 3; // Output volume of the left channel
        uint8_t so2OutputVin: 1;    // Output Vin to the left channel (0: Disabled; 1: Enabled)
    };
    uint8_t raw;
}; // union ChannelControlReg

static_assert(sizeof(ChannelControlReg) == 1, "Channel Control register structure size is incorrect");

// [NR51] Selection of Sound output terminal
union SoundOutputTerminalSelectionReg {
    struct {
        uint8_t channel1So1Output: 1;   // Output channel 1 to the right channel
        uint8_t channel2So1Output: 1;   // Output channel 2 to the right channel
        uint8_t channel3So1Output: 1;   // Output channel 3 to the right channel
        uint8_t channel4So1Output: 1;   // Output channel 4 to the right channel
        uint8_t channel1So2Output: 1;   // Output channel 1 to the left channel
        uint8_t channel2So2Output: 1;   // Output channel 2 to the left channel
        uint8_t channel3So2Output: 1;   // Output channel 3 to the left channel
        uint8_t channel4So2Output: 1;   // Output channel 4 to the left channel
    };
    uint8_t raw;
}; // union SoundOutputTerminalSelectionReg

static_assert(sizeof(SoundOutputTerminalSelectionReg) == 1, "Sound Output Terminal Selection register structure size is incorrect");

// [NR52] Sound on/off
union SoundOnOffReg {
    struct {
        uint8_t channel1On: 1;  // Output Channel 1
        uint8_t channel2On: 1;  // Output Channel 2
        uint8_t channel3On: 1;  // Output Channel 3
        uint8_t channel4On: 1;  // Output Channel 4
        uint8_t unused: 3;
        uint8_t globalOn: 1;    // Output sound
    };
    uint8_t raw;
}; // union SoundOnOffReg

static_assert(sizeof(SoundOnOffReg) == 1, "Sound On/Off register structure size is incorrect");

// Sound Control registers
struct SoundControlRegisters {
    ChannelControlReg channelControl;
    SoundOutputTerminalSelectionReg soundOutputTerminalSelection;
    SoundOnOffReg soundOnOff;
}; // struct SoundControlRegisters

// Channel registers
struct Channel1Registers {
    SweepReg sweep;
    SoundLengthWavePatternDutyReg soundLengthWavePatternDuty;
    VolumeEnvelopeReg volumeEnvelope;
    FrequencyLowReg frequencyLow;
    FrequencyHighReg frequencyHigh;
}; // struct Channel1Registers

struct Channel2Registers {
    SoundLengthWavePatternDutyReg soundLengthWavePatternDuty;
    VolumeEnvelopeReg volumeEnvelope;
    FrequencyLowReg frequencyLow;
    FrequencyHighReg frequencyHigh;
}; // struct Channel2Registers

struct Channel3Registers {
    WaveSoundOnOffReg soundOnOff;
    WaveSoundLengthReg soundLength;
    SelectOutputLevelReg selectOutputLevel;
    FrequencyLowReg frequencyLow;
    FrequencyHighReg frequencyHigh;
}; // struct Channel3Registers

struct Channel4Registers {
    NoiseSoundLengthReg soundLength;
    VolumeEnvelopeReg volumeEnvelope;
    PolynomialCounterReg polynomialCounter;
    CounterConsecutiveAndInitialReg counterConsecutiveAndInitial;
}; // struct Channel4Registers

} // namespace gbtest

#endif //GBTEST_APUREGISTERS_H
