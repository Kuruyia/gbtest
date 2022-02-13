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
};

static_assert(sizeof(SweepReg) == 1, "Sweep register structure size is incorrect");

// [NR11/NR21] Channel 1/2 Sound Length/Wave Pattern Duty register
union SoundLengthWavePatternDuty {
    struct {
        uint8_t soundLengthData: 6; // Length of the sound
        uint8_t wavePatternDuty: 2; // Wave duty cycle
    };
    uint8_t raw;
}; // union SoundLengthWavePatternDuty

static_assert(sizeof(SoundLengthWavePatternDuty) == 1, "Sound Length/Wave Pattern Duty structure size is incorrect");

// [NR12/NR22/42] Channel 1/2/4 Volume Envelope
union VolumeEnvelopeReg {
    struct {
        uint8_t nbEnvelopeSweep: 3;         // Number of envelope sweep (0: Stop operation)
        uint8_t envelopeDirection: 1;       // Envelope direction (0: Decrease; 1: Increase)
        uint8_t envelopeInitialVolume: 4;   // Initial volume of envelope (0: No sound)
    };
    uint8_t raw;
}; // union VolumeEnvelopeReg

static_assert(sizeof(VolumeEnvelopeReg) == 1, "Volume Envelope register structure size is incorrect");

// [NR13/23] Channel 1/2 Frequency Low
union FrequencyLow {
    uint8_t raw; // Lower 8 bits of the frequency
}; // union FrequencyLow

static_assert(sizeof(FrequencyLow) == 1, "Frequency Low structure size is incorrect");

// [NR14/24] Channel 1/2 Frequency High
union FrequencyHigh {
    struct {
        uint8_t frequencyHigh: 3;               // Higher 3 bits of the frequency
        uint8_t unused: 3;
        uint8_t counterConsecutiveSelection: 1; // 1: Stop output when length in NR11/NR21 expires
        uint8_t trigger: 1;                     // 1: Restart sound
    };
    uint8_t raw;
}; // union FrequencyHigh

static_assert(sizeof(FrequencyHigh) == 1, "Frequency High structure size is incorrect");

// [NR41] Channel 4 Sound Length
union SoundLengthReg {
    struct {
        uint8_t soundLengthData: 6; // Length of the sound
        uint8_t unused: 2;
    };
    uint8_t raw;
}; // union SoundLengthReg

static_assert(sizeof(SoundLengthReg) == 1, "Sound length register structure size is incorrect");

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
union ChannelControl {
    struct {
        uint8_t so1OutputVolume: 3; // Output volume of the right channel
        uint8_t so1OutputVin: 1;    // Output Vin to the right channel (0: Disabled; 1: Enabled)
        uint8_t so2OutputVolume: 3; // Output volume of the left channel
        uint8_t so2OutputVin: 1;    // Output Vin to the left channel (0: Disabled; 1: Enabled)
    };
    uint8_t raw;
}; // union ChannelControl

static_assert(sizeof(ChannelControl) == 1, "Channel Control structure size is incorrect");

// [NR51] Selection of Sound output terminal
union SoundOutputTerminalSelection {
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
}; // union SoundOutputTerminalSelection

static_assert(sizeof(SoundOutputTerminalSelection) == 1, "Sound Output Terminal Selection structure size is incorrect");

// [NR52] Sound on/off
union SoundOnOff {
    struct {
        uint8_t channel1On: 1;  // Output Channel 1
        uint8_t channel2On: 1;  // Output Channel 2
        uint8_t channel3On: 1;  // Output Channel 3
        uint8_t channel4On: 1;  // Output Channel 4
        uint8_t unused: 3;
        uint8_t globalOn: 1;    // Output sound
    };
    uint8_t raw;
}; // union SoundOnOff

static_assert(sizeof(SoundOnOff) == 1, "Sound On/Off structure size is incorrect");

// Sound Control registers
struct SoundControlRegisters {
    ChannelControl channelControl;
    SoundOutputTerminalSelection soundOutputTerminalSelection;
    SoundOnOff soundOnOff;
}; // struct SoundControlRegisters

// Channel registers
struct Channel1Registers {
    SweepReg sweep;
    SoundLengthWavePatternDuty soundLengthWavePatternDuty;
    VolumeEnvelopeReg volumeEnvelope;
    FrequencyLow frequencyLow;
    FrequencyHigh frequencyHigh;
}; // struct Channel1Registers

struct Channel2Registers {
    SoundLengthWavePatternDuty soundLengthWavePatternDuty;
    VolumeEnvelopeReg volumeEnvelope;
    FrequencyLow frequencyLow;
    FrequencyHigh frequencyHigh;
}; // struct Channel2Registers

struct Channel4Registers {
    SoundLengthReg soundLength;
    VolumeEnvelopeReg volumeEnvelope;
    PolynomialCounterReg polynomialCounter;
    CounterConsecutiveAndInitialReg counterConsecutiveAndInitial;
}; // struct Channel4Registers

} // namespace gbtest

#endif //GBTEST_APUREGISTERS_H
