#include <iomanip>
#include <iostream>
#include <sstream>

#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "LR35902.h"

void printRegisters(sf::RenderTarget &renderTarget, const gbtest::LR35902 &cpu, const sf::Vector2f &pos)
{
    sf::Font font;
    font.loadFromFile("UbuntuMono-Regular.ttf");

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(16);
    text.setPosition(pos);

    std::stringstream sstr;
    sstr << std::hex
            << "A: " << std::setw(2) << std::setfill('0') << (int)cpu.getRegisters().a << "h" << std::endl
            << "BC: " << std::setw(4) << std::setfill('0') << cpu.getRegisters().bc << "h" << std::endl
            << "DE: " << std::setw(4) << std::setfill('0') << cpu.getRegisters().de << "h" << std::endl
            << "HL: " << std::setw(4) << std::setfill('0') << cpu.getRegisters().hl << "h" << std::endl
            << "SP: " << std::setw(4) << std::setfill('0') << cpu.getRegisters().sp << "h" << std::endl
            << "PC: " << std::setw(4) << std::setfill('0') << cpu.getRegisters().pc << "h" << std::endl;

    text.setString(sstr.str());
    renderTarget.draw(text);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "gbtest");

    gbtest::Bus bus;
    gbtest::LR35902 cpu(bus);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        printRegisters(window, cpu, {0, 0});

        window.display();
    }

    return 0;
}
