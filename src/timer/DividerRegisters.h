#ifndef GBTEST_DIVIDERREGISTERS_H
#define GBTEST_DIVIDERREGISTERS_H

#include <cstdint>

namespace gbtest {

// [DIV] Divider Register
struct DividerReg {
    uint8_t value;
};

static_assert(sizeof(DividerReg) == 1, "Divider register structure size is incorrect");

} // namespace gbtest

#endif //GBTEST_DIVIDERREGISTERS_H
