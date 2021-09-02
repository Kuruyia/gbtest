#include <iostream>

#include <raylib.h>

#include "GameBoy.h"

int main()
{
    InitWindow(600, 700, "gbtest");
    SetTargetFPS(60);

    gbtest::GameBoy gameboy;
    bool tickEnabled = true;

    // Try to open a ROM file
    if (FILE* gbRom = fopen("boot.bin", "rb"); gbRom!=nullptr) {
        uint8_t currByte;
        unsigned offset = 0;
        while (fread(&currByte, sizeof(currByte), 0x1, gbRom)>0) {
            gameboy.getBus().write(offset++, currByte);
        }

        fclose(gbRom);
    }
    else {
        gameboy.getBus().write(0x100, 0x3E); // LD A, 0xFF
        gameboy.getBus().write(0x101, 0xFF);

        gameboy.getBus().write(0x102, 0xC6); // ADD A, 0x01
        gameboy.getBus().write(0x103, 0x01);

        gameboy.getBus().write(0x110, 0x18); // JR -2
        gameboy.getBus().write(0x111, -2);
    }

    while (!WindowShouldClose()) {
        // Tick the CPU (if enabled)
        if (tickEnabled) {
            // TODO: De-hardcode that
            gameboy.update(1000);
        }

        // Check if keys were pressed
        int keyPressed = 0;
        while ((keyPressed = GetKeyPressed())!=0) {
            switch (keyPressed) {
            case KEY_SPACE:gameboy.tick();
                break;

            case KEY_P:tickEnabled = !tickEnabled;
                break;

            default: break;
            }
        }

        // Draw the window
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
