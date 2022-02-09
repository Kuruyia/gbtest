#ifndef GBTEST_SPRITEBUFFER_H
#define GBTEST_SPRITEBUFFER_H

#include <array>
#include <cstddef>

#include "OAMEntry.h"

namespace gbtest {

class SpriteBuffer {

public:
    using RawSpriteBuffer = std::array<OAMEntry, 10>;

    SpriteBuffer();

    void push(const OAMEntry& oamEntry);
    [[nodiscard]] const OAMEntry& at(size_t idx) const;
    [[nodiscard]] OAMEntry& at(size_t idx);

    [[nodiscard]] const RawSpriteBuffer& getRawBuffer() const;
    [[nodiscard]] RawSpriteBuffer& getRawBuffer();

    [[nodiscard]] size_t getSize() const;
    void clear();

private:
    RawSpriteBuffer m_buffer;
    size_t m_size;

}; // class SpriteBuffer

} // namespace gbtest

#endif //GBTEST_SPRITEBUFFER_H
