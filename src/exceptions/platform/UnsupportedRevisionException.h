#ifndef GBTEST_UNSUPPORTEDREVISIONEXCEPTION_H
#define GBTEST_UNSUPPORTEDREVISIONEXCEPTION_H

#include <stdexcept>

#include "../../platform/revision/GameBoyRevisionType.h"

namespace gbtest {

class UnsupportedRevisionException
        : public std::runtime_error {

public:
    explicit UnsupportedRevisionException(GameBoyRevisionType revisionType);

    [[nodiscard]] GameBoyRevisionType getRevisionType() const;

private:
    GameBoyRevisionType m_revisionType;

}; // class UnsupportedRevisionException

} // namespace gbtest

#endif //GBTEST_UNSUPPORTEDREVISIONEXCEPTION_H
