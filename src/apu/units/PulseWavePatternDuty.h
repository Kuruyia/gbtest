#ifndef GBTEST_PULSEWAVEPATTERNDUTY_H
#define GBTEST_PULSEWAVEPATTERNDUTY_H

namespace gbtest {

enum class PulseWavePatternDuty {
    Duty_125 = 1,   // 12.5% Duty cycle
    Duty_25 = 2,   //   25% Duty cycle
    Duty_50 = 4,   //   50% Duty cycle
    Duty_75 = 6,   //   75% Duty cycle
}; // enum class PulseWavePatternDuty

} // namespace gbtest

#endif //GBTEST_PULSEWAVEPATTERNDUTY_H
