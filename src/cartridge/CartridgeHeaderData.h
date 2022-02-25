#ifndef GBTEST_CARTRIDGEHEADERDATA_H
#define GBTEST_CARTRIDGEHEADERDATA_H

#include <cstdint>

// MBC types
enum class CartridgeMBCType {
    Unknown,
    ROMOnly,
    MBC1,
    MBC2,
    MBC3,
    MBC5,
    MBC6,
    MBC7,
    MMM01,
    BandaiTAMA5,
    HuC1,
    HuC3,
}; // enum class CartridgeMBCType

// Valid CGB flags
enum class CartridgeHeaderCGBFlag {
    CGBAndDMG = 0x80,   // Supports CGB functions with DMG backwards-compatibility
    CGBOnly = 0xC0,     // Only works on CGB
}; // enum class CartridgeHeaderCGBFlag

// Valid SGB flags
enum class CartridgeHeaderSGBFlag {
    NoSGB = 0x00,       // No SGB functions
    SGBSupport = 0x03,  // SGB functions supported
}; // enum class CartridgeHeaderSGBFlag

// Valid cartridge types
enum class CartridgeHeaderCartridgeType {
    ROMOnly = 0x00,                                 // ROM ONLY
    MBC1 = 0x01,                                    // MBC1
    MBC1AndRAM = 0x02,                              // MBC1 + RAM
    MBC1AndRAMAndBattery = 0x03,                    // MBC1 + RAM + BATTERY
    MBC2 = 0x05,                                    // MBC2
    MBC2AndBattery = 0x06,                          // MBC2 + BATTERY
    ROMAndRAM = 0x08,                               // ROM + RAM
    ROMAndRAMAndBattery = 0x09,                     // ROM + RAM + BATTERY
    MMM01 = 0x0B,                                   // MMM01
    MMM01AndRAM = 0x0C,                             // MMM01 + RAM
    MMM01AndRAMAndBattery = 0x0D,                   // MMM01 + RAM + BATTERY
    MBC3AndTimerAndBattery = 0x0F,                  // MBC3 + TIMER + BATTERY
    MBC3AndTimerAndRAMAndBattery = 0x10,            // MBC3 + TIMER + RAM + BATTERY
    MBC3 = 0x11,                                    // MBC3
    MBC3AndRAM = 0x12,                              // MBC3 + RAM
    MBC3AndRAMAndBattery = 0x13,                    // MBC3 + RAM + BATTERY
    MBC5 = 0x19,                                    // MBC5
    MBC5AndRAM = 0x1A,                              // MBC5 + RAM
    MBC5AndRAMAndBattery = 0x1B,                    // MBC5 + RAM + BATTERY
    MBC5AndRumble = 0x1C,                           // MBC5 + RUMBLE
    MBC5AndRumbleAndRAM = 0x1D,                     // MBC5 + RUMBLE + RAM
    MBC5AndRumbleAndRAMAndBattery = 0x1E,           // MBC5 + RUMBLE + RAM + BATTERY
    MBC6 = 0x20,                                    // MBC6
    MBC7AndSensorAndRumbleAndRAMAndBattery = 0x22,  // MBC7 + SENSOR + RUMBLE + RAM + BATTERY
    PocketCamera = 0xFC,                            // POCKET CAMERA
    BandaiTAMA5 = 0xFD,                             // BANDAI TAMA5
    HuC3 = 0xFE,                                    // HuC3
    HuC1AndRAMAndBattery = 0xFF,                    // HuC1 + RAM + BATTERY
}; // enum class CartridgeHeaderCartridgeType

// Valid ROM sizes
enum class CartridgeHeaderROMSize {
    ROM32K = 0x00,  //  32 KByte /   2 banks (No ROM banking)
    ROM64K = 0x01,  //  64 KByte /   4 banks
    ROM128K = 0x02, // 128 KByte /   8 banks
    ROM256K = 0x03, // 256 KByte /  16 banks
    ROM512K = 0x04, // 512 KByte /  32 banks
    ROM1M = 0x05,   //   1 MByte /  64 banks
    ROM2M = 0x06,   //   2 MByte / 128 banks
    ROM4M = 0x07,   //   4 MByte / 256 banks
    ROM8M = 0x08,   //   8 MByte / 512 banks
    ROM1_1M = 0x52, // 1.1 MByte /  72 banks
    ROM1_2M = 0x53, // 1.2 MByte /  80 banks
    ROM1_5M = 0x54, // 1.5 MByte /  96 banks
}; // enum class CartridgeHeaderROMSize

// Valid RAM sizes
enum class CartridgeHeaderRAMSize {
    NoRAM = 0x00,
    RAM8K = 0x02,   //   8 KByte /  1 bank
    RAM32K = 0x03,  //  32 KByte /  4 banks
    RAM128K = 0x04, // 128 KByte / 16 banks
    RAM64K = 0x05,  //  64 KByte /  8 banks
}; // enum class CartridgeHeaderRAMSize

// Valid destination codes
enum class CartridgeHeaderDestinationCode {
    Japanese = 0x00,
    NonJapanese = 0x01,
}; // enum class CartridgeHeaderDestinationCode

// Data in the cartridge header
struct CartridgeHeaderData {
    uint8_t logo[0x30];                             // [0104h-0133h] Logo
    uint32_t manufacturerCode;                      // [013Fh-0142h] Manufacturer Code
    CartridgeHeaderCGBFlag cgbFlag;                 // [0143h] CGB Flag
    uint16_t newLicenseeCode;                       // [0144h-0145h] New Licensee Code
    CartridgeHeaderSGBFlag sgbFlag;                 // [0146h] SGB Flag
    CartridgeHeaderCartridgeType cartridgeType;     // [0147h] Cartridge Type
    CartridgeHeaderROMSize romSize;                 // [0148h] ROM Size
    CartridgeHeaderRAMSize ramSize;                 // [0149h] RAM Size
    CartridgeHeaderDestinationCode destinationCode; // [014Ah] Destination Code
    uint8_t oldLicenseeCode;                        // [014Bh] Old Licensee Code
    uint8_t versionNumber;                          // [014Ch] Mask ROM Version number
    uint8_t headerChecksum;                         // [014Dh] Header Checksum
    uint16_t globalChecksum;                        // [014E-014F] Global Checksum
}; // struct CartridgeHeaderData

#endif //GBTEST_CARTRIDGEHEADERDATA_H
