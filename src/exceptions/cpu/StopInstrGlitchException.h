#ifndef GBTEST_STOPINSTRGLITCHEXCEPTION_H
#define GBTEST_STOPINSTRGLITCHEXCEPTION_H

#include <stdexcept>

namespace gbtest {

class StopInstrGlitchException
        : std::runtime_error {

public:
    StopInstrGlitchException();

}; // class StopInstrGlitchException

} // namespace gbtest

#endif //GBTEST_STOPINSTRGLITCHEXCEPTION_H
