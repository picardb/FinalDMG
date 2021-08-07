#include "Cpu.h"

namespace FinalDMG
{
    void Cpu::instrJrCond(Condition cond) {
        fetchParams(1);
        bool doTheJump = false;
        switch (cond) {
        case CONDITION_NZ: doTheJump = !getFlag(FLAG_Z); break;
        case CONDITION_Z: doTheJump = getFlag(FLAG_Z); break;
        case CONDITION_NC: doTheJump = !getFlag(FLAG_C); break;
        case CONDITION_C: doTheJump = getFlag(FLAG_C); break;
        default: break;
        }
        if (doTheJump) {
            m_remainingCycles = 12;
            m_regs16[REG16_PC] += int8_t(m_params[0]);
        }
        else {
            m_remainingCycles = 8;
        }
    }
}