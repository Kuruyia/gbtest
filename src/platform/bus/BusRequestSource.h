#ifndef GBTEST_BUSREQUESTSOURCE_H
#define GBTEST_BUSREQUESTSOURCE_H

namespace gbtest {

enum class BusRequestSource {
    Unknown,        // We don't know the source from this request
    Privileged,     // Privileged request (e.g. from the debugger)

    CPU,            // Request from the CPU
    CPUSpeedSwitch, // Request from the CPU for a speed switch (CGB mode)
    OAMDMA,         // Request from the OAM DMA engine
    APUChannel,     // Request from an APU channel
}; // enum class BusRequestSource

} // namespace gbtest

#endif //GBTEST_BUSREQUESTSOURCE_H
