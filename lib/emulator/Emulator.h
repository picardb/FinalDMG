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

    private:
        Cpu* m_cpu;
        MemController* m_memController;
    };
}

#endif /* FINAL_DMG_EMULATOR_H_ */
