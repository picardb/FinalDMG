#ifndef FINAL_DMG_BUS_DEVICE_
#define FINAL_DMG_BUS_DEVICE_

#include <memory>
#include <cstdint>

namespace FinalDMG
{
    class Bus;

    class BusDevice
    {
    public:
        BusDevice() :
            m_bus(nullptr)
        { }

        void connectBus(Bus *bus) { m_bus = bus; }

        virtual uint8_t busRead(uint16_t address) { return 0; }
        virtual void busWrite(uint16_t address, uint8_t value) { /* Do nothing */ }

    protected:
        Bus *m_bus;
    };
}

#endif /* FINAL_DMG_BUS_DEVICE_ */