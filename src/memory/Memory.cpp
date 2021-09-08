#include "Memory.h"

gbtest::Memory::Memory(uint16_t baseAddr, uint32_t size)
        : m_baseAddress(baseAddr)
        , m_memorySize(size)
        , m_memory(new uint8_t[size]())
{

}

gbtest::Memory::~Memory()
{
    delete[] m_memory;
}

bool gbtest::Memory::read(uint16_t addr, uint8_t& val) const
{
    const uint16_t offset = addr - m_baseAddress;

    // Check that the address is in bounds
    if (offset >= m_memorySize) {
        return false;
    }

    // Read from the memory
    val = m_memory[offset];

    return true;
}

bool gbtest::Memory::write(uint16_t addr, uint8_t val)
{
    const uint16_t offset = addr - m_baseAddress;

    // Check that the address is in bounds
    if (offset >= m_memorySize) {
        return false;
    }

    // Write to the memory
    m_memory[offset] = val;

    return true;
}

bool gbtest::Memory::doesAuthorizeAccess(uint16_t addr)
{
    // We have no reason to lock the bus
    return true;
}