#ifndef GBTEST_DEBUGSCREEN_H
#define GBTEST_DEBUGSCREEN_H

#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "platform/GameBoy.h"

namespace gbtest {

class DebugScreen {

public:
    DebugScreen(GameBoy& gb);

    void render(sf::RenderTarget& renderTarget);

private:
    void printRegisters(sf::RenderTarget& renderTarget);
    void printMemory(sf::RenderTarget& renderTarget, const uint16_t& startAddr, const uint16_t& nbLines);
    void printCpuState(sf::RenderTarget& renderTarget);

    GameBoy& m_gb;

    sf::Font m_font;
    sf::Text m_registerText;
    sf::Text m_stateText;
    sf::Text m_memText;

}; // class DebugScreen

} // namespace gbtest

#endif //GBTEST_DEBUGSCREEN_H
