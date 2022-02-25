#include <cstddef>

#include "BaseCartridge.h"

gbtest::BaseCartridge::BaseCartridge(gbtest::CartridgeDataSource& cartridgeDataSource)
        : m_cartridgeDataSource(cartridgeDataSource)
        , m_cartridgeHeaderData()
{
    // Parse the cartridge header
    parseHeader();
}

CartridgeMBCType gbtest::BaseCartridge::getMBCType() const
{
    switch (m_cartridgeHeaderData.cartridgeType) {
    case CartridgeHeaderCartridgeType::ROMOnly:
    case CartridgeHeaderCartridgeType::ROMAndRAM:
    case CartridgeHeaderCartridgeType::ROMAndRAMAndBattery:
        return CartridgeMBCType::ROMOnly;

    case CartridgeHeaderCartridgeType::MBC1:
    case CartridgeHeaderCartridgeType::MBC1AndRAM:
    case CartridgeHeaderCartridgeType::MBC1AndRAMAndBattery:
        return CartridgeMBCType::MBC1;

    case CartridgeHeaderCartridgeType::MBC2:
    case CartridgeHeaderCartridgeType::MBC2AndBattery:
        return CartridgeMBCType::MBC2;

    case CartridgeHeaderCartridgeType::MBC3AndTimerAndBattery:
    case CartridgeHeaderCartridgeType::MBC3AndTimerAndRAMAndBattery:
    case CartridgeHeaderCartridgeType::MBC3:
    case CartridgeHeaderCartridgeType::MBC3AndRAM:
    case CartridgeHeaderCartridgeType::MBC3AndRAMAndBattery:
        return CartridgeMBCType::MBC3;

    case CartridgeHeaderCartridgeType::MBC5:
    case CartridgeHeaderCartridgeType::MBC5AndRAM:
    case CartridgeHeaderCartridgeType::MBC5AndRAMAndBattery:
    case CartridgeHeaderCartridgeType::MBC5AndRumble:
    case CartridgeHeaderCartridgeType::MBC5AndRumbleAndRAM:
    case CartridgeHeaderCartridgeType::MBC5AndRumbleAndRAMAndBattery:
        return CartridgeMBCType::MBC5;

    case CartridgeHeaderCartridgeType::MBC6:
        return CartridgeMBCType::MBC6;

    case CartridgeHeaderCartridgeType::MBC7AndSensorAndRumbleAndRAMAndBattery:
        return CartridgeMBCType::MBC7;

    case CartridgeHeaderCartridgeType::MMM01:
    case CartridgeHeaderCartridgeType::MMM01AndRAM:
    case CartridgeHeaderCartridgeType::MMM01AndRAMAndBattery:
        return CartridgeMBCType::MMM01;

    case CartridgeHeaderCartridgeType::BandaiTAMA5:
        return CartridgeMBCType::BandaiTAMA5;

    case CartridgeHeaderCartridgeType::HuC1AndRAMAndBattery:
        return CartridgeMBCType::HuC1;

    case CartridgeHeaderCartridgeType::HuC3:
        return CartridgeMBCType::HuC3;

    default:
        return CartridgeMBCType::Unknown;
    }
}

inline bool gbtest::BaseCartridge::hasRAM(CartridgeHeaderCartridgeType cartridgeType)
{
    // Return true for all the MBCs that contains RAM
    switch (cartridgeType) {
    case CartridgeHeaderCartridgeType::MBC1AndRAM:
    case CartridgeHeaderCartridgeType::MBC1AndRAMAndBattery:
    case CartridgeHeaderCartridgeType::ROMAndRAM:
    case CartridgeHeaderCartridgeType::ROMAndRAMAndBattery:
    case CartridgeHeaderCartridgeType::MMM01AndRAM:
    case CartridgeHeaderCartridgeType::MMM01AndRAMAndBattery:
    case CartridgeHeaderCartridgeType::MBC3AndTimerAndRAMAndBattery:
    case CartridgeHeaderCartridgeType::MBC3AndRAM:
    case CartridgeHeaderCartridgeType::MBC3AndRAMAndBattery:
    case CartridgeHeaderCartridgeType::MBC5AndRAM:
    case CartridgeHeaderCartridgeType::MBC5AndRAMAndBattery:
    case CartridgeHeaderCartridgeType::MBC5AndRumbleAndRAM:
    case CartridgeHeaderCartridgeType::MBC5AndRumbleAndRAMAndBattery:
    case CartridgeHeaderCartridgeType::MBC7AndSensorAndRumbleAndRAMAndBattery:
    case CartridgeHeaderCartridgeType::HuC1AndRAMAndBattery:
        return true;

    default:
        return false;
    }
}

bool gbtest::BaseCartridge::hasRAM() const
{
    return hasRAM(m_cartridgeHeaderData.cartridgeType);
}

inline bool gbtest::BaseCartridge::hasBattery(CartridgeHeaderCartridgeType cartridgeType)
{
    switch (cartridgeType) {
    case CartridgeHeaderCartridgeType::MBC1AndRAMAndBattery:
    case CartridgeHeaderCartridgeType::MBC2AndBattery:
    case CartridgeHeaderCartridgeType::ROMAndRAMAndBattery:
    case CartridgeHeaderCartridgeType::MMM01AndRAMAndBattery:
    case CartridgeHeaderCartridgeType::MBC3AndTimerAndBattery:
    case CartridgeHeaderCartridgeType::MBC3AndTimerAndRAMAndBattery:
    case CartridgeHeaderCartridgeType::MBC3AndRAMAndBattery:
    case CartridgeHeaderCartridgeType::MBC5AndRAMAndBattery:
    case CartridgeHeaderCartridgeType::MBC5AndRumbleAndRAMAndBattery:
    case CartridgeHeaderCartridgeType::MBC7AndSensorAndRumbleAndRAMAndBattery:
    case CartridgeHeaderCartridgeType::HuC1AndRAMAndBattery:
        return true;

    default:
        return false;
    }
}

bool gbtest::BaseCartridge::hasBattery() const
{
    return hasBattery(m_cartridgeHeaderData.cartridgeType);
}

inline bool gbtest::BaseCartridge::hasTimer(CartridgeHeaderCartridgeType cartridgeType)
{
    switch (cartridgeType) {
    case CartridgeHeaderCartridgeType::MBC3AndTimerAndBattery:
    case CartridgeHeaderCartridgeType::MBC3AndTimerAndRAMAndBattery:
        return true;

    default:
        return false;
    }
}

bool gbtest::BaseCartridge::hasTimer() const
{
    return hasTimer(m_cartridgeHeaderData.cartridgeType);
}

inline bool gbtest::BaseCartridge::hasRumble(CartridgeHeaderCartridgeType cartridgeType)
{
    switch (cartridgeType) {
    case CartridgeHeaderCartridgeType::MBC5AndRumble:
    case CartridgeHeaderCartridgeType::MBC5AndRumbleAndRAM:
    case CartridgeHeaderCartridgeType::MBC5AndRumbleAndRAMAndBattery:
    case CartridgeHeaderCartridgeType::MBC7AndSensorAndRumbleAndRAMAndBattery:
        return true;

    default:
        return false;
    }
}

bool gbtest::BaseCartridge::hasRumble() const
{
    return hasRumble(m_cartridgeHeaderData.cartridgeType);
}

inline bool gbtest::BaseCartridge::hasSensor(CartridgeHeaderCartridgeType cartridgeType)
{
    return (cartridgeType == CartridgeHeaderCartridgeType::MBC7AndSensorAndRumbleAndRAMAndBattery);
}

bool gbtest::BaseCartridge::hasSensor() const
{
    return hasSensor(m_cartridgeHeaderData.cartridgeType);
}

void gbtest::BaseCartridge::parseHeader()
{
    // Variable declaration
    uint8_t buff;

    // Extract the logo
    for (size_t i = 0; i < 48; ++i) {
        m_cartridgeDataSource.read(0x0104 + i, m_cartridgeHeaderData.logo[i]);
    }

    // Extract the manufacturer code
    m_cartridgeDataSource.read(0x013F, buff);
    m_cartridgeHeaderData.manufacturerCode = buff;

    m_cartridgeDataSource.read(0x0140, buff);
    m_cartridgeHeaderData.manufacturerCode <<= 8;
    m_cartridgeHeaderData.manufacturerCode |= buff;

    m_cartridgeDataSource.read(0x0141, buff);
    m_cartridgeHeaderData.manufacturerCode <<= 8;
    m_cartridgeHeaderData.manufacturerCode |= buff;

    m_cartridgeDataSource.read(0x0142, buff);
    m_cartridgeHeaderData.manufacturerCode <<= 8;
    m_cartridgeHeaderData.manufacturerCode |= buff;

    // Extract the CGB flag
    m_cartridgeDataSource.read(0x0143, buff);
    m_cartridgeHeaderData.cgbFlag = CartridgeHeaderCGBFlag(buff);

    // Extract the new licensee code
    m_cartridgeDataSource.read(0x0144, buff);
    m_cartridgeHeaderData.newLicenseeCode = buff;

    m_cartridgeDataSource.read(0x0145, buff);
    m_cartridgeHeaderData.newLicenseeCode <<= 8;
    m_cartridgeHeaderData.newLicenseeCode |= buff;

    // Extract the SGB flag
    m_cartridgeDataSource.read(0x0146, buff);
    m_cartridgeHeaderData.sgbFlag = CartridgeHeaderSGBFlag(buff);

    // Extract the cartridge type
    m_cartridgeDataSource.read(0x0147, buff);
    m_cartridgeHeaderData.cartridgeType = CartridgeHeaderCartridgeType(buff);

    // Extract the ROM size
    m_cartridgeDataSource.read(0x0148, buff);
    m_cartridgeHeaderData.romSize = CartridgeHeaderROMSize(buff);

    // Extract the RAM size
    m_cartridgeDataSource.read(0x0149, buff);
    m_cartridgeHeaderData.ramSize = CartridgeHeaderRAMSize(buff);

    // Extract the destination code
    m_cartridgeDataSource.read(0x014A, buff);
    m_cartridgeHeaderData.destinationCode = CartridgeHeaderDestinationCode(buff);

    // Extract the old licensee code
    m_cartridgeDataSource.read(0x014B, m_cartridgeHeaderData.oldLicenseeCode);

    // Extract the version number
    m_cartridgeDataSource.read(0x014C, m_cartridgeHeaderData.versionNumber);

    // Extract the checksums
    m_cartridgeDataSource.read(0x014D, m_cartridgeHeaderData.headerChecksum);

    m_cartridgeDataSource.read(0x014E, buff);
    m_cartridgeHeaderData.globalChecksum = buff;

    m_cartridgeDataSource.read(0x014F, buff);
    m_cartridgeHeaderData.globalChecksum <<= 8;
    m_cartridgeHeaderData.globalChecksum |= buff;
}
