#ifndef GBTEST_APU_H
#define GBTEST_APU_H

#include "channels/APUChannel2.h"

#include "../platform/bus/BusProvider.h"
#include "../utils/Tickable.h"

namespace gbtest {

class APU
        : public BusProvider, public Tickable {

public:
    APU();
    ~APU() override = default;

    [[nodiscard]] float sample() const;

    void tick() override;

    bool busRead(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWrite(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

    bool busReadOverride(uint16_t addr, uint8_t& val, BusRequestSource requestSource) const override;
    bool busWriteOverride(uint16_t addr, uint8_t val, BusRequestSource requestSource) override;

private:
    SoundControlRegisters m_soundControlRegisters;

    APUChannel2 m_apuChannel2;

}; // class APU

} // namespace gbtest

#endif //GBTEST_APU_H
