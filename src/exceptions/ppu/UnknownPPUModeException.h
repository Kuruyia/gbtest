#ifndef GBTEST_UNKNOWNPPUMODEEXCEPTION_H
#define GBTEST_UNKNOWNPPUMODEEXCEPTION_H

#include <stdexcept>

namespace gbtest {

class UnknownPPUModeException:
        public std::runtime_error {

public:
    UnknownPPUModeException();

}; // class UnknownPPUModeException

} // namespace gbtest

#endif //GBTEST_UNKNOWNPPUMODEEXCEPTION_H
