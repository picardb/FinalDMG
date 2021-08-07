#include "Cpu.h"

namespace FinalDMG
{
    void Cpu::instrNop(void) {
        m_remainingCycles = 4;
    }
}