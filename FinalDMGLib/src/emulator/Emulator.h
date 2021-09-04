#ifndef FINAL_DMG_EMULATOR_H_
#define FINAL_DMG_EMULATOR_H_

#include "bus/Bus.h"
#include "cpu/Cpu.h"
#include "memory/BootstrapRom.h"

#include <memory>
#include <cstdint>

namespace FinalDMG
{

    class Emulator
    {
    public:
        Emulator();

        Bus* bus(void) const { return m_bus.get(); }
        Cpu* cpu(void) const { return m_cpu.get(); }

        void runForCycles(int cycles);

    private:
        std::unique_ptr<Bus> m_bus;
        std::unique_ptr<Cpu> m_cpu;
        std::unique_ptr<BootstrapRom> m_bootstrapRom;
    };
}

#endif /* FINAL_DMG_EMULATOR_H_ */
