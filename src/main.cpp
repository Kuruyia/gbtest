#include <array>
#include <chrono>
#include <iostream>
#include <memory>

#include <raylib.h>

#include "platform/GameBoy.h"

static constexpr unsigned TARGET_FPS = 60;
static constexpr float FRAME_TIME = 1.f / TARGET_FPS;

int main()
{
    // Init the core emulator
    std::unique_ptr<gbtest::GameBoy> gameboy = std::make_unique<gbtest::GameBoy>();
    gameboy->init();

    // Init the window
    InitWindow(680, 616, "gbtest");
    SetTargetFPS(TARGET_FPS);

    Image lcdImage = {
            &(gameboy->getPpu().getFramebuffer().getRawBuffer().front()),
            160,
            144,
            1,
            PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };
    Texture2D lcdTex = LoadTextureFromImage(lcdImage);

    gameboy->getPpu().getFramebuffer().setFramebufferReadyCallback(
            [&](const gbtest::Framebuffer::FramebufferContainer& framebuffer) -> void {
                // Copy the framebuffer for rendering
                UpdateTexture(lcdTex, &(framebuffer.front()));
            });

    // Try to open a ROM file
    if (FILE* gbRom = fopen("tetris.bin", "rb"); gbRom != nullptr) {
        uint8_t currByte;
        unsigned offset = 0;
        while (fread(&currByte, sizeof(currByte), 0x1, gbRom) > 0) {
            gameboy->getBus().write(offset++, currByte, gbtest::BusRequestSource::Privileged);
        }

        fclose(gbRom);
    }
    else {
        gameboy->getBus().write(0x100, 0x3E, gbtest::BusRequestSource::Privileged); // LD A, 0xFF
        gameboy->getBus().write(0x101, 0xFF, gbtest::BusRequestSource::Privileged);

        gameboy->getBus().write(0x102, 0xC6, gbtest::BusRequestSource::Privileged); // ADD A, 0x01
        gameboy->getBus().write(0x103, 0x01, gbtest::BusRequestSource::Privileged);

        gameboy->getBus().write(0x110, 0x18, gbtest::BusRequestSource::Privileged); // JR -2
        gameboy->getBus().write(0x111, -2, gbtest::BusRequestSource::Privileged);
    }

    while (!WindowShouldClose()) {
        // Tick the gameboy
        gameboy->update(FRAME_TIME);

        // Update the joypad
        gameboy->getJoypad().updateJoypadState(
                IsKeyDown(KEY_RIGHT),
                IsKeyDown(KEY_LEFT),
                IsKeyDown(KEY_UP),
                IsKeyDown(KEY_DOWN),
                IsKeyDown(KEY_A),
                IsKeyDown(KEY_S),
                IsKeyDown(KEY_LEFT_SHIFT),
                IsKeyDown(KEY_ENTER)
        );

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
