#include <array>
#include <chrono>
#include <iostream>

#include <raylib.h>

#include "platform/GameBoy.h"

int main()
{
    InitWindow(680, 616, "gbtest");
    SetTargetFPS(60);

    gbtest::GameBoy gameboy;
    gameboy.init();

    Image lcdImage = {
            &(gameboy.getPpu().getFramebuffer().getRawBuffer().front()),
            160,
            144,
            1,
            PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };
    Texture2D lcdTex = LoadTextureFromImage(lcdImage);

    gameboy.getPpu().getFramebuffer().setFramebufferReadyCallback(
            [&](const gbtest::Framebuffer::FramebufferContainer& framebuffer) -> void {
                // Copy the framebuffer for rendering
                UpdateTexture(lcdTex, &(framebuffer.front()));
            });

    bool tickEnabled = true;

    // Try to open a ROM file
    if (FILE* gbRom = fopen("acid.bin", "rb"); gbRom != nullptr) {
        uint8_t currByte;
        unsigned offset = 0;
        while (fread(&currByte, sizeof(currByte), 0x1, gbRom) > 0) {
            gameboy.getBus().write(offset++, currByte, gbtest::BusRequestSource::Privileged);
        }

        fclose(gbRom);
    }
    else {
        gameboy.getBus().write(0x100, 0x3E, gbtest::BusRequestSource::Privileged); // LD A, 0xFF
        gameboy.getBus().write(0x101, 0xFF, gbtest::BusRequestSource::Privileged);

        gameboy.getBus().write(0x102, 0xC6, gbtest::BusRequestSource::Privileged); // ADD A, 0x01
        gameboy.getBus().write(0x103, 0x01, gbtest::BusRequestSource::Privileged);

        gameboy.getBus().write(0x110, 0x18, gbtest::BusRequestSource::Privileged); // JR -2
        gameboy.getBus().write(0x111, -2, gbtest::BusRequestSource::Privileged);
    }

    while (!WindowShouldClose()) {
        // Tick the CPU (if enabled)
        if (tickEnabled) {
            // TODO: De-hardcode that
            gameboy.update(16667);
        }

        // Check if keys were pressed
        int keyPressed = 0;
        while ((keyPressed = GetKeyPressed()) != 0) {
            switch (keyPressed) {
            case KEY_SPACE:
                gameboy.tick();
                break;

            case KEY_P:
                tickEnabled = !tickEnabled;
                break;

            default:
                break;
            }
        }

        // Draw the window
        BeginDrawing();
        ClearBackground({0xE3, 0xFF, 0x8A, 0xFF});

        DrawTexturePro(lcdTex, {0, 0, 160, 144}, {20, 20, 640, 576}, {0, 0}, 0, WHITE);

        DrawFPS(0, 0);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
