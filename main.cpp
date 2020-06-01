#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "DebugScreen.h"
#include "GameBoy.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 700), "gbtest");
    window.setVerticalSyncEnabled(true);

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
        gameboy.getBus().write(0x100, 0x3E); // LD A, 0xFF
        gameboy.getBus().write(0x101, 0xFF);

        gameboy.getBus().write(0x102, 0xC6); // ADD A, 0x01
        gameboy.getBus().write(0x103, 0x01);

        gameboy.getBus().write(0x110, 0x18); // JR -2
        gameboy.getBus().write(0x111, -2);
    }

//    gameboy.getBus().write(0xFF44, 144);

    sf::Clock busTick;

    while (window.isOpen())
    {
        const int64_t delta = busTick.getElapsedTime().asMicroseconds();
        busTick.restart();
        if (tickEnabled)
            gameboy.update(delta);


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
