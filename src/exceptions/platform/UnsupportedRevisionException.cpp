#include "UnsupportedRevisionException.h"

gbtest::UnsupportedRevisionException::UnsupportedRevisionException(gbtest::GameBoyRevisionType revisionType)
        : std::runtime_error("This console revision is not supported.")
        , m_revisionType(revisionType)
{

}

gbtest::GameBoyRevisionType gbtest::UnsupportedRevisionException::getRevisionType() const
{
    return m_revisionType;
}
