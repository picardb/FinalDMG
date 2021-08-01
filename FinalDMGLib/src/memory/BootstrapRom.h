#ifndef FINAL_DMG_BOOTSTRAP_ROM_
#define FINAL_DMG_BOOTSTRAP_ROM_

#include "bus/BusDevice.h"
#include "helpers/FileHelper.h"

#include <memory>
#include <array>
#include <string>

namespace FinalDMG {

    class BootstrapRom : public BusDevice
    {
    public:
        BootstrapRom() :
            m_rom()
        { }

        uint8_t busRead(uint16_t address) { return m_rom[address]; }
        void busWrite(uint16_t address, uint8_t value) { /* TODO */ }
        void loadFomFile(const std::string& fileName);

    private:
        std::array<uint8_t, 256> m_rom;
    };

}

#endif /* FINAL_DMG_BOOTSTRAP_ROM_ */
