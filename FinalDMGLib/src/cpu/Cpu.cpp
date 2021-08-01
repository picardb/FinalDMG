#include "Cpu.h"
#include "emulator/Emulator.h"

#include <cstring>

using namespace std;

namespace FinalDMG
{

    void Cpu::step(void)
    {
        if (m_remainingCycles == 0) {
            fetchNextInstruction();
            executeInstruction();
        }
        else {
            m_remainingCycles--;
        }
    }

    void Cpu::fetchNextInstruction()
    {
        m_opcode = m_bus->read(m_regPc);
    }

    void Cpu::executeInstruction()
    {
        // TODO
        m_remainingCycles = 4;
    }

}