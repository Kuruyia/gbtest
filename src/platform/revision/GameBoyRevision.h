#ifndef GBTEST_GAMEBOYREVISION_H
#define GBTEST_GAMEBOYREVISION_H

#include "GameBoyRevisionType.h"

namespace gbtest {

class GameBoyRevision {

public:
    explicit GameBoyRevision(GameBoyRevisionType revisionType);

    [[nodiscard]] GameBoyRevisionType getRevisionType() const;

    static bool isDMG(GameBoyRevisionType revisionType);
    [[nodiscard]] bool isDMG() const;

    static bool isCGB(GameBoyRevisionType revisionType);
    [[nodiscard]] bool isCGB() const;

private:
    GameBoyRevisionType m_revisionType;

    bool m_isDMG;
    bool m_isCGB;

}; // class GameBoyRevision

} // namespace gbtest

#endif //GBTEST_GAMEBOYREVISION_H
