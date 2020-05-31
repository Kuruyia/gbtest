#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "DebugScreen.h"
#include "GameBoy.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "gbtest");
    sf::Clock fpsClock;

    gbtest::GameBoy gameboy;
    gbtest::DebugScreen debugScreen(gameboy);
    bool tickEnabled = true;

    FILE *gbRom;
    if (fopen_s(&gbRom, "boot.bin", "rb") == 0)
    {
        uint8_t currByte;
        unsigned offset = 0;
        while (fread(&currByte, sizeof(currByte), 0x1, gbRom) > 0)
            gameboy.getBus().write(offset++, currByte);

        fclose(gbRom);
    } else
    {
        gameboy.getBus().write(0x100, 0x06); // LD B, 0x69
        gameboy.getBus().write(0x101, 0x69);
        gameboy.getBus().write(0x102, 0x2E); // LD L, 0xF
        gameboy.getBus().write(0x103, 0xF);
        gameboy.getBus().write(0x104, 0x70); // LD (HL), B

        gameboy.getBus().write(0x106, 0x31); // LD SP, 0x0040
        gameboy.getBus().write(0x107, 0x40);
        gameboy.getBus().write(0x108, 0x00);

        gameboy.getBus().write(0x110, 0x08); // LD 0x20, SP
        gameboy.getBus().write(0x111, 0x20);
        gameboy.getBus().write(0x112, 0x00);

        gameboy.getBus().write(0x114, 0x0E); // LD C, 0x42
        gameboy.getBus().write(0x115, 0x42);
        gameboy.getBus().write(0x116, 0xC5); // PUSH BC
        gameboy.getBus().write(0x117, 0xD1); // POP DE

        gameboy.getBus().write(0x119, 0xF8); // LD HL, SP + (-1)
        gameboy.getBus().write(0x11A, -1);
    }

    sf::Clock busTick;

    while (window.isOpen())
    {
        if (tickEnabled)
            gameboy.update(busTick.getElapsedTime().asMicroseconds());

        busTick.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Key::Space)
                {
                    gameboy.tick();
                } else if (event.key.code == sf::Keyboard::P)
                {
                    tickEnabled = !tickEnabled;
                }
            }
        }

        window.clear();

        debugScreen.render(window);

        window.display();

        window.setTitle("gbtest - " + std::to_string(1.f / fpsClock.getElapsedTime().asSeconds()) + " FPS");
        fpsClock.restart();
    }

    return 0;
}
