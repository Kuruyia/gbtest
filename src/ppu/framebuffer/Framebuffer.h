#ifndef GBTEST_FRAMEBUFFER_H
#define GBTEST_FRAMEBUFFER_H

#include <array>
#include <cstdint>
#include <functional>

namespace gbtest {

class Framebuffer {

public:
    using FramebufferContainer = std::array<uint32_t, 160 * 144>;
    using FramebufferReadyCallback = std::function<void(const FramebufferContainer& framebuffer)>;

    Framebuffer();

    void setPixel(unsigned x, unsigned y, uint32_t pixel);
    [[nodiscard]] uint32_t getPixel(unsigned x, unsigned y) const;

    [[nodiscard]] const FramebufferContainer& getRawBuffer() const;
    [[nodiscard]] FramebufferContainer& getRawBuffer();

    void setFramebufferReadyCallback(FramebufferReadyCallback&& framebufferReadyCallback);
    void notifyReady();

private:
    FramebufferContainer m_framebuffer;
    FramebufferReadyCallback m_framebufferReadyCallback;

}; // class Framebuffer

} // namespace gbtest

#endif //GBTEST_FRAMEBUFFER_H
