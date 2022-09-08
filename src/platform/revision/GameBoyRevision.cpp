#include "GameBoyRevision.h"

gbtest::GameBoyRevision::GameBoyRevision(gbtest::GameBoyRevisionType revisionType)
        : m_revisionType(revisionType)
        , m_isDMG(isDMG(revisionType))
        , m_isCGB(isCGB(revisionType))
{

}

gbtest::GameBoyRevisionType gbtest::GameBoyRevision::getRevisionType() const
{
    return m_revisionType;
}

bool gbtest::GameBoyRevision::isDMG(gbtest::GameBoyRevisionType revisionType)
{
    return (revisionType == GameBoyRevisionType::DMG);
}

bool gbtest::GameBoyRevision::isDMG() const
{
    return m_isDMG;
}

bool gbtest::GameBoyRevision::isCGB(gbtest::GameBoyRevisionType revisionType)
{
    return (revisionType == GameBoyRevisionType::CGB);
}

bool gbtest::GameBoyRevision::isCGB() const
{
    return m_isCGB;
}
