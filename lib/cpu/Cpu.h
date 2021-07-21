#ifndef FINAL_DMG_CPU_
#define FINAL_DMG_CPU_

#include <memory>

#include "CpuRegs.h"

namespace FinalDMG {

    class Emulator;

    class Cpu {
    public:
        Cpu(Emulator* emulator)
            : m_emulator(emulator)
        { }

    private:
        Emulator *m_emulator;

        CpuRegs m_cpuRegs;
        uint8_t m_opcode;
        uint8_t m_params[2];

        void fetchNextInstruction();
        void executeInstruction();
    };

}


#endif /* FINAL_DMG_CPU_ */
