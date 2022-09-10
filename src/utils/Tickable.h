#ifndef GBTEST_TICKABLE_H
#define GBTEST_TICKABLE_H

namespace gbtest {

class Tickable {

public:
    virtual ~Tickable() = default;

    virtual void tick(bool isDoubleSpeedTick) = 0;

}; // class Tickable

} // namespace gbtest

#endif //GBTEST_TICKABLE_H
