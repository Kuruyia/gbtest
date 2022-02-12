#ifndef GBTEST_PULSEWAVEPATTERNDUTY_H
#define GBTEST_PULSEWAVEPATTERNDUTY_H

namespace gbtest {

enum class PulseWavePatternDuty {
    Duty_12_5,  // 12.5% Duty cycle
    Duty_25,    //   25% Duty cycle
    Duty_50,    //   50% Duty cycle
    Duty_75,    //   75% Duty cycle
}; // enum class PulseWavePatternDuty

static constexpr uint8_t PULSE_WAVE_PATTERN_WAVEFORMS[] = {
        0, 0, 0, 0, 0, 0, 0, 1, // 12.5% Duty cycle
        1, 0, 0, 0, 0, 0, 0, 1, //   25% Duty cycle
        1, 0, 0, 0, 0, 1, 1, 1, //   50% Duty cycle
        0, 1, 1, 1, 1, 1, 1, 0, //   75% Duty cycle
}; // static constexpr uint8_t PULSE_WAVE_PATTERN_WAVEFORMS[]

} // namespace gbtest

#endif //GBTEST_PULSEWAVEPATTERNDUTY_H
