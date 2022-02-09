#include <array>
#include <chrono>
#include <iostream>
#include <memory>

#include "miniaudio.h"
#include <raylib.h>

#include "platform/GameBoy.h"

#define SYNC_ON_AUDIO

static constexpr unsigned TARGET_FPS = 60;
static constexpr float FRAME_TIME = 1.f / TARGET_FPS;
static constexpr size_t AUDIO_FRAMES_REQUIRED = 512;

void maDataCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    // Grab the emulator core from user data
    auto* ctx = static_cast<gbtest::GameBoy*>(pDevice->pUserData);

    // Consume the samples if there are enough available
    if (ctx->getApu().getFrameCount() >= frameCount) {
        ma_copy_pcm_frames(pOutput, ctx->getApu().getFramebuffer().data(), frameCount, ma_format_f32,
                gbtest::APU::CHANNELS);

        ctx->getApu().consumeFrames(frameCount);
    }

#ifdef SYNC_ON_AUDIO
    // Sync on audio
    while (ctx->getApu().getFrameCount() < AUDIO_FRAMES_REQUIRED) {
        ctx->tick();
    }
#endif
}

int main()
{
    // Init the core emulator
    std::unique_ptr<gbtest::GameBoy> gameboy = std::make_unique<gbtest::GameBoy>();
    gameboy->init();

    // Try to open a ROM file
    if (FILE* gbRom = fopen("individual/05.bin", "rb"); gbRom != nullptr) {
        uint8_t currByte;
        unsigned offset = 0;
        while (fread(&currByte, sizeof(currByte), 0x1, gbRom) > 0) {
            gameboy->getBus().write(offset, currByte, gbtest::BusRequestSource::Privileged);
            ++offset;
        }

        fclose(gbRom);
    }
    else {
        // LD A, 0xFF
        gameboy->getBus().write(0x100, 0x3E, gbtest::BusRequestSource::Privileged);
        gameboy->getBus().write(0x101, 0xFF, gbtest::BusRequestSource::Privileged);

        // ADD A, 0x01
        gameboy->getBus().write(0x102, 0xC6, gbtest::BusRequestSource::Privileged);
        gameboy->getBus().write(0x103, 0x01, gbtest::BusRequestSource::Privileged);

        // JR -1
        gameboy->getBus().write(0x110, 0x18, gbtest::BusRequestSource::Privileged);
        gameboy->getBus().write(0x111, -1, gbtest::BusRequestSource::Privileged);
    }

    // Init the window
    InitWindow(680, 616, "gbtest");
    SetTargetFPS(TARGET_FPS);

    bool framebufferReady = false;
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
#ifndef SYNC_ON_AUDIO
                // Copy the framebuffer for rendering
                UpdateTexture(lcdTex, framebuffer.begin());
#else
                // Mark the framebuffer ready
                framebufferReady = true;
#endif
            });

    // Init miniaudio
    ma_device_config config = ma_device_config_init(ma_device_type_playback);
    config.playback.format = ma_format_f32;
    config.playback.channels = gbtest::APU::CHANNELS;
    config.sampleRate = gbtest::APU::SAMPLE_RATE;
    config.dataCallback = maDataCallback;
    config.pUserData = gameboy.get();

    ma_device device;
    if (ma_device_init(nullptr, &config, &device) != MA_SUCCESS) {
        return -1;
    }

    ma_device_start(&device);

    while (!WindowShouldClose()) {
#ifndef SYNC_ON_AUDIO
        // Tick the gameboy
        gameboy->update(FRAME_TIME);
#endif

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

#ifdef SYNC_ON_AUDIO
        if (framebufferReady) {
            // Framebuffer was updated, copy its texture
            UpdateTexture(lcdTex, gameboy->getPpu().getFramebuffer().getRawBuffer().data());
            framebufferReady = false;
        }
#endif

        // Draw the window
        BeginDrawing();
        ClearBackground({0xE3, 0xFF, 0x8A, 0xFF});

        DrawTexturePro(lcdTex, {0, 0, 160, 144}, {20, 20, 640, 576}, {0, 0}, 0, WHITE);

        DrawFPS(0, 0);
        EndDrawing();
    }

    ma_device_uninit(&device);
    CloseWindow();

    return 0;
}
