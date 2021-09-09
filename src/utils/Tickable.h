#ifndef GBTEST_TICKABLE_H
#define GBTEST_TICKABLE_H

namespace gbtest {

class Tickable {

public:
    virtual ~Tickable() = default;

    virtual void tick() = 0;

}; // class Tickable

} // namespace gbtest

#endif //GBTEST_TICKABLE_H
