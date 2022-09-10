#include "StopInstrGlitchException.h"

gbtest::StopInstrGlitchException::StopInstrGlitchException()
        : std::runtime_error("The CPU glitched because of a STOP instruction.")
{

}
