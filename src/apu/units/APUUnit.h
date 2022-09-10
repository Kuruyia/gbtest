#ifndef GBTEST_APUUNIT_H
#define GBTEST_APUUNIT_H

namespace gbtest {

enum class APUUnit {
    LengthCounter = 1 << 0,     // Length counter: Disables a channel after a certain amount of time
    VolumeEnvelope = 1 << 1,    // Volume envelope: Gradually increases/decreases the output volume of a channel
    Sweep = 1 << 2,             // Sweep: Gradually increases/decreases the frequency of a pulse wave channel
    PulseWave = 1 << 3,         // Pulse wave: Generates a square wave signal
    Waveform = 1 << 4,          // Waveform: Generates sound from an arbitrary waveform
    Noise = 1 << 5,             // Noise: Generates noise-like sound
    None = 1 << 7               // No unit
}; // enum class APUUnit

} // namespace gbtest

#endif //GBTEST_APUUNIT_H
