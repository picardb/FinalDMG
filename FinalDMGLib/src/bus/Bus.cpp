#include "Bus.h"

using namespace std;

namespace FinalDMG
{
    uint8_t Bus::read(uint16_t address) const
    {
        if (address <= ADDR_BOOTSTRAP_END) {
            return m_bootstrapRom->busRead(address);
        }

        return 0;
    }

    void Bus::write(uint16_t address, uint8_t value)
    {
        if (address <= ADDR_BOOTSTRAP_END) {
            m_bootstrapRom->busWrite(address, value);
        }
    }
}