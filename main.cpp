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
            << "A:  " << std::setw(2) << std::setfill('0') << (int)cpu.getRegisters().a << "h" << std::endl
            << "BC: " << std::setw(4) << std::setfill('0') << cpu.getRegisters().bc << "h" << std::endl
            << "DE: " << std::setw(4) << std::setfill('0') << cpu.getRegisters().de << "h" << std::endl
            << "HL: " << std::setw(4) << std::setfill('0') << cpu.getRegisters().hl << "h" << std::endl
            << "SP: " << std::setw(4) << std::setfill('0') << cpu.getRegisters().sp << "h" << std::endl
            << "PC: " << std::setw(4) << std::setfill('0') << cpu.getRegisters().pc << "h" << std::endl
            << "F:  " << (cpu.getRegisters().f.z ? 'Z' : '-') << ' ' << (cpu.getRegisters().f.n ? 'N' : '-') << ' '
            << (cpu.getRegisters().f.h ? 'H' : '-') << ' ' << (cpu.getRegisters().f.c ? 'C' : '-') << ' ';

    text.setString(sstr.str());
    renderTarget.draw(text);
}

void printMemory(sf::RenderTarget &renderTarget, const gbtest::Bus &bus, const uint16_t &startAddr, const uint16_t &nbLines,
        const sf::Vector2f &pos)
{
    sf::Font font;
    font.loadFromFile("UbuntuMono-Regular.ttf");

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(16);
    text.setPosition(pos);

    std::stringstream sstr;
    sstr << std::hex << "Addr ";
    for (unsigned i = 0; i <= 0xF; ++i)
        sstr << std::setw(2) << i << ' ';

    sstr << std::endl;
    for (unsigned i = 0; i <= nbLines; ++i)
    {
        const uint16_t currBaseAddr = startAddr + (i * 0x10);
        sstr << std::setfill('0') << std::setw(4) << currBaseAddr << ' ';
        for (unsigned j = 0; j <= 0xF; ++j)
            sstr << std::setw(2) << (int)bus.read(currBaseAddr + j) << ' ';

        sstr << std::endl;
    }

    text.setString(sstr.str());
    renderTarget.draw(text);
}

void printCpuState(sf::RenderTarget &renderTarget, const gbtest::LR35902 &cpu, const sf::Vector2f &pos)
{
    sf::Font font;
    font.loadFromFile("UbuntuMono-Regular.ttf");

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(16);
    text.setPosition(pos);

    std::stringstream sstr;
    sstr << std::boolalpha
         << "Cycles:  " << (int)cpu.getCyclesToWaste() << std::endl
         << "TickCnt: " << cpu.getTickCounter() << std::endl
         << "IME:     " << cpu.isInterruptMasterEnabled() << std::endl
         << "Halted:  " << cpu.isHalted() << std::endl
         << "Stopped: " << cpu.isStopped() << std::endl;

    text.setString(sstr.str());
    renderTarget.draw(text);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "gbtest");

    gbtest::Bus bus;
    gbtest::LR35902 cpu(bus);

    FILE *gbRom;
    if (fopen_s(&gbRom, "boot.bin", "rb") == 0)
    {
        uint8_t currByte;
        unsigned offset = 0;
        while (fread(&currByte, sizeof(currByte), 0x1, gbRom) > 0)
            bus.write(0x100 + (offset++), currByte);

        fclose(gbRom);
    } else
    {
        bus.write(0x100, 0x06); // LD B, 0x69
        bus.write(0x101, 0x69);
        bus.write(0x102, 0x2E); // LD L, 0xF
        bus.write(0x103, 0xF);
        bus.write(0x104, 0x70); // LD (HL), B

        bus.write(0x106, 0x31); // LD SP, 0x0040
        bus.write(0x107, 0x40);
        bus.write(0x108, 0x00);

        bus.write(0x110, 0x08); // LD 0x20, SP
        bus.write(0x111, 0x20);
        bus.write(0x112, 0x00);

        bus.write(0x114, 0x0E); // LD C, 0x42
        bus.write(0x115, 0x42);
        bus.write(0x116, 0xC5); // PUSH BC
        bus.write(0x117, 0xD1); // POP DE

        bus.write(0x119, 0xF8); // LD HL, SP + (-1)
        bus.write(0x11A, -1);
    }

    while (window.isOpen())
    {
        cpu.tick();

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
//                    cpu.tick();
                }
            }
        }

        window.clear();

        printRegisters(window, cpu, {0, 0});
        printCpuState(window, cpu, {125, 0});
        printMemory(window, bus, 0x100, 0xF, {0, 150});

        window.display();

        sf::sleep(sf::milliseconds(13));
    }

    return 0;
}
