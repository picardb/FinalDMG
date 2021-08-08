#include "Cpu.h"

namespace FinalDMG
{
    void Cpu::instrAddHlReg16(Reg16 reg) {
        m_remainingCycles = 8;

        if (((m_regs16[REG16_HL] & 0x0FFF) + (m_regs16[reg] & 0x0FFF)) > 0x0FFF) {
            setFlag(FLAG_H);
        } else {
            resetFlag(FLAG_H);
        }
        if ((uint32_t(m_regs16[REG16_HL]) + uint32_t(m_regs16[reg])) > 0xFFFF) {
            setFlag(FLAG_C);
        } else {
            resetFlag(FLAG_C);
        }

        m_regs16[REG16_HL] += m_regs16[reg];

        resetFlag(FLAG_N);
    }

    void Cpu::instrAddSpImm(void) {
        fetchParams(1);
        m_remainingCycles = 16;

        m_regs16[REG16_SP] += int8_t(m_params[0]);
        
        resetFlag(FLAG_Z);
        resetFlag(FLAG_N);
        // FLAGS TODO
    }

    void Cpu::instrIncReg16(Reg16 reg) {
        m_remainingCycles = 8;

        m_regs16[reg]++;
    }

    void Cpu::instrDecReg16(Reg16 reg) {
        m_remainingCycles = 8;

        m_regs16[reg]--;
    }
}
