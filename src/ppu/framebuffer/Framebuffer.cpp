#include "Framebuffer.h"

gbtest::Framebuffer::Framebuffer()
        : m_framebuffer()
{

}

void gbtest::Framebuffer::setPixel(unsigned int x, unsigned int y, uint32_t pixel)
{
    m_framebuffer.at((y * 160) + x) = pixel;
}

uint32_t gbtest::Framebuffer::getPixel(unsigned int x, unsigned int y) const
{
    return m_framebuffer.at((y * 160) + x);
}

const gbtest::Framebuffer::FramebufferContainer& gbtest::Framebuffer::getRawBuffer() const
{
    return m_framebuffer;
}

gbtest::Framebuffer::FramebufferContainer& gbtest::Framebuffer::getRawBuffer()
{
    return m_framebuffer;
}

void gbtest::Framebuffer::setFramebufferReadyCallback(FramebufferReadyCallback&& framebufferReadyCallback)
{
    m_framebufferReadyCallback = framebufferReadyCallback;
}

void gbtest::Framebuffer::notifyReady()
{
    if (m_framebufferReadyCallback) {
        m_framebufferReadyCallback(m_framebuffer);
    }
}
