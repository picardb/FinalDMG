#ifndef FINAL_DMG_EMULATOR_H_
#define FINAL_DMG_EMULATOR_H_

#include "bus/Bus.h"
#include "cpu/Cpu.h"
#include "memory/BootstrapRom.h"

#include <memory>

namespace FinalDMG
{

    class Emulator
    {
    public:
        Emulator();

        uint8_t getCpuReg8(Cpu::Reg8 reg) const { return m_cpu->getReg8(reg); }
        uint16_t getCpuRegPc(void) const { return m_cpu->getReg16(Cpu::REG16_PC); }
        uint16_t getCpuRegSp(void) const { return m_cpu->getReg16(Cpu::REG16_SP); }
        uint8_t getCpuOpcode(void) const { return m_cpu->getOpcode(); }
        uint8_t getCpuRemainingCycles(void) const { return m_cpu->getRemainingCycles(); }
        uint8_t busRead(uint16_t address) const { return m_bus->read(address); }
        void busWrite(uint16_t address, uint8_t value) { m_bus->write(address, value); }

        void runForCycles(int cycles);

    private:
        std::unique_ptr<Bus> m_bus;
        std::unique_ptr<Cpu> m_cpu;
        std::unique_ptr<BootstrapRom> m_bootstrapRom;
    };
}

#endif /* FINAL_DMG_EMULATOR_H_ */
