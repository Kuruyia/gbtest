#include <array>
#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>
#include <sys/stat.h>

#include "miniaudio.h"
#include <raylib.h>

#include "cartridge/datasource/InMemoryCartridgeDataSource.h"
#include "platform/revision/GameBoyRevisionType.h"
#include "platform/GameBoy.h"

#define SYNC_ON_AUDIO

static constexpr unsigned TARGET_FPS = 60;
static constexpr float FRAME_TIME = 1.f / TARGET_FPS;
static constexpr size_t AUDIO_FRAMES_REQUIRED = 1024;

ma_lpf g_lpf;
std::mutex g_audioMutex;

void maDataCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    // Lock the audio mutex
    const std::lock_guard<std::mutex> lock(g_audioMutex);

    // Grab the emulator core from user data
    auto* ctx = static_cast<gbtest::GameBoy*>(pDevice->pUserData);

    // If the emulator is paused, output silence
    if (!ctx->isRunning()) {
        return;
    }

    // Consume the samples if there are enough available
    if (ctx->getApu().getFrameCount() >= frameCount) {
        ma_copy_pcm_frames(pOutput, ctx->getApu().getFramebuffer().data(), frameCount, ma_format_f32,
                gbtest::APU::CHANNELS);
        ma_lpf_process_pcm_frames(&g_lpf, pOutput, pOutput, frameCount);

        ctx->getApu().consumeFrames(frameCount);
    }

#ifdef SYNC_ON_AUDIO
    // Sync on audio
    while (ctx->getApu().getFrameCount() < AUDIO_FRAMES_REQUIRED) {
        ctx->tick();
    }
#endif
}

void loadROM(std::string_view filename, gbtest::InMemoryCartridgeDataSource& cartridgeDataSource)
{
    if (FILE* gbRom = fopen(filename.data(), "rb"); gbRom != nullptr) {
        struct stat fileStats{};
        fstat(fileno(gbRom), &fileStats);
        cartridgeDataSource.getStorage().reserve(fileStats.st_size);

        uint8_t currByte;
        unsigned offset = 0;

        while (fread(&currByte, sizeof(currByte), 0x1, gbRom) > 0) {
            cartridgeDataSource.getStorage().push_back(currByte);
            ++offset;
        }

        fclose(gbRom);
    }
    else {
        std::cerr << "File " << filename << " not found!" << std::endl;
    }
}

void updateWindowTitle(gbtest::GameBoy* gb)
{
    // Build the title string
    std::stringstream titleStream;

    if (gb->getCartridge()) {
        // Check if the emulator is paused
        if (!gb->isRunning()) {
            titleStream << "[PAUSED] ";
        }

        // Add the name of the game
        titleStream << gb->getCartridge()->getHeaderData().title << " - ";
    }

    // Add the emulator name
    titleStream << "gbtest";

    // Set the window title
    SetWindowTitle(titleStream.str().c_str());
}

int main()
{
    // Init the core emulator
    std::unique_ptr<gbtest::GameBoy> gameboy = std::make_unique<gbtest::GameBoy>(gbtest::GameBoyRevisionType::DMG);
    gameboy->init();

    // Load a ROM file
    auto cartridgeDataSource = std::make_unique<gbtest::InMemoryCartridgeDataSource>();
    loadROM("dmgsnd_individual/02.bin", *(cartridgeDataSource.get()));
    gameboy->loadCartridgeFromDataSource(std::move(cartridgeDataSource));

    std::cout << "Loaded cartridge type: " << (unsigned) gameboy->getCartridge()->getMBCType() << std::endl;

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
                UpdateTexture(lcdTex, framebuffer.data());
#else
                // Mark the framebuffer ready
                framebufferReady = true;
#endif
            });

    // Init miniaudio
    ma_lpf_config lpfConfig = ma_lpf_config_init(ma_format_f32, gbtest::APU::CHANNELS, gbtest::APU::SAMPLE_RATE,
            (float) gbtest::APU::SAMPLE_RATE / 2, 3);
    ma_result result = ma_lpf_init(&lpfConfig, nullptr, &g_lpf);
    if (result != MA_SUCCESS) {
        return -1;
    }

    ma_device_config config = ma_device_config_init(ma_device_type_playback);
    config.playback.format = ma_format_f32;
    config.playback.channels = gbtest::APU::CHANNELS;
    config.sampleRate = gbtest::APU::SAMPLE_RATE;
    config.dataCallback = maDataCallback;
    config.pUserData = gameboy.get();
    config.noClip = true;

    ma_device device;
    if (ma_device_init(nullptr, &config, &device) != MA_SUCCESS) {
        return -1;
    }

    // Start the emulator
    gameboy->start();
    ma_device_start(&device);

    updateWindowTitle(gameboy.get());

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

        // Handle the start/stop key
        if (IsKeyPressed(KEY_P)) {
            // Lock the audio mutex
            const std::lock_guard<std::mutex> lock(g_audioMutex);

            if (gameboy->isRunning()) {
                gameboy->stop();

                updateWindowTitle(gameboy.get());
                std::cout << "Emulator stopped" << std::endl;
            }
            else {
                gameboy->start();

                updateWindowTitle(gameboy.get());
                std::cout << "Emulator started" << std::endl;
            }
        }

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
