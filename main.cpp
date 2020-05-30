#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "LR35902.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "gbtest");

    gbtest::LR35902 cpu;
    cpu.m_registers.a = 1;
    cpu.m_registers.f.n = 1;
    std::cout << cpu.m_registers.af << " (size: " << sizeof(cpu.m_registers.af) << ")" << std::endl;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        window.display();
    }

    return 0;
}
