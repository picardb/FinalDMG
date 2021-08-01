#ifndef FINAL_DMG_MEM_CONTROLLER_H_
#define FINAL_DMG_MEM_CONTROLLER_H_

#include <cstdint>

namespace FinalDMG
{
    class Emulator;

    class MemController {
    public:
        MemController(Emulator* emulator);

        uint8_t readByte(uint16_t address) const;
        void writeByte(uint16_t address, uint8_t value);
        void readBlock(uint16_t address, int length, uint8_t *pDest) const;

    private:
        static const uint16_t ADDRESS_CART_START = 256;

        Emulator* m_emulator;

        uint8_t m_bootstrapRom[256];
    };
}

#endif /* FINAL_DMG_MEM_CONTROLLER_H_ */