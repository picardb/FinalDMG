#ifndef FINAL_DMG_EMULATOR_H_
#define FINAL_DMG_EMULATOR_H_

#include "cpu/Cpu.h"
#include "mem_controller/MemController.h"

namespace FinalDMG
{

    class Emulator
    {
    public:
        Emulator();

        uint8_t readMemByte(uint16_t address) const { return m_memController->readByte(address); }
        void writeMemByte(uint16_t address, uint8_t value) { m_memController->writeByte(address, value); }
        void readMemBlock(uint16_t address, int length, uint8_t* pDest) const { return m_memController->readBlock(address, length, pDest); }

    private:
        Cpu* m_cpu;
        MemController* m_memController;
    };
}

#endif /* FINAL_DMG_EMULATOR_H_ */
