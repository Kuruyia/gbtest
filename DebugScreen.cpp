#include <iomanip>
#include <sstream>

#include "DebugScreen.h"

gbtest::DebugScreen::DebugScreen(gbtest::GameBoy &gb)
: m_gb(gb)
{
    m_font.loadFromFile("UbuntuMono-Regular.ttf");

    m_registerText.setFont(m_font);
    m_registerText.setCharacterSize(16);
    m_registerText.setPosition({0, 0});

    m_stateText.setFont(m_font);
    m_stateText.setCharacterSize(16);
    m_stateText.setPosition({125, 0});

    m_memText.setFont(m_font);
    m_memText.setCharacterSize(16);
    m_memText.setPosition({0, 150});
}

void gbtest::DebugScreen::render(sf::RenderTarget &renderTarget)
{
    printRegisters(renderTarget);
    printMemory(renderTarget, 0x9800, 0xF);
    printCpuState(renderTarget);
}

void gbtest::DebugScreen::printRegisters(sf::RenderTarget &renderTarget)
{
    std::stringstream sstr;
    sstr << std::uppercase << std::hex
         << "AF: " << std::setw(2) << std::setfill('0') << m_gb.getCpu().getRegisters().af << std::endl
         << "BC: " << std::setw(4) << std::setfill('0') << m_gb.getCpu().getRegisters().bc << std::endl
         << "DE: " << std::setw(4) << std::setfill('0') << m_gb.getCpu().getRegisters().de << std::endl
         << "HL: " << std::setw(4) << std::setfill('0') << m_gb.getCpu().getRegisters().hl << std::endl
         << "SP: " << std::setw(4) << std::setfill('0') << m_gb.getCpu().getRegisters().sp << std::endl
         << "PC: " << std::setw(4) << std::setfill('0') << m_gb.getCpu().getRegisters().pc << std::endl
         << "F:  " << (m_gb.getCpu().getRegisters().f.z ? 'Z' : '-') << ' ' << (m_gb.getCpu().getRegisters().f.n ? 'N' : '-') << ' '
         << (m_gb.getCpu().getRegisters().f.h ? 'H' : '-') << ' ' << (m_gb.getCpu().getRegisters().f.c ? 'C' : '-') << ' ';

    m_registerText.setString(sstr.str());
    renderTarget.draw(m_registerText);
}

void gbtest::DebugScreen::printMemory(sf::RenderTarget &renderTarget, const uint16_t &startAddr, const uint16_t &nbLines)
{
    std::stringstream sstr;

    // Print the table header
    sstr << std::hex << "Addr " << std::uppercase;
    for (unsigned i = 0; i <= 0xF; ++i)
        sstr << std::setw(2) << i << ' ';

    sstr << std::endl;

    // Print the table content
    for (unsigned i = 0; i <= nbLines; ++i)
    {
        // Get the current base address
        const uint16_t currBaseAddr = startAddr + (i * 0x10);
        sstr << std::setfill('0') << std::setw(4) << currBaseAddr << ' ';

        // Print memory values as hex from currBaseAddr + 0x0 to currBaseAddr + 0xF
        for (unsigned j = 0; j <= 0xF; ++j)
            sstr << std::setw(2) << (int)m_gb.getBus().read(currBaseAddr + j) << ' ';

        // Print memory values as ascii from from currBaseAddr + 0x0 to currBaseAddr + 0xF
        sstr << ' ';
        for (unsigned j = 0; j <= 0xF; ++j)
            sstr << m_gb.getBus().read(currBaseAddr + j);

        sstr << std::endl;
    }

    m_memText.setString(sstr.str());
    renderTarget.draw(m_memText);
}

void gbtest::DebugScreen::printCpuState(sf::RenderTarget &renderTarget)
{
    std::stringstream sstr;
    sstr << std::boolalpha
         << "Cycles:  " << (int)m_gb.getCpu().getCyclesToWaste() << std::endl
         << "TickCnt: " << m_gb.getCpu().getTickCounter() << std::endl
         << "IME:     " << m_gb.getCpu().isInterruptMasterEnabled() << std::endl
         << "Halted:  " << m_gb.getCpu().isHalted() << std::endl
         << "Stopped: " << m_gb.getCpu().isStopped() << std::endl;

    m_stateText.setString(sstr.str());
    renderTarget.draw(m_stateText);
}