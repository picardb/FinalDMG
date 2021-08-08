#include "Cpu.h"
#include "bus/Bus.h"

namespace FinalDMG
{
    void Cpu::instrJp(void) {
        fetchParams(2);
        m_remainingCycles = 12;

        m_regs16[REG16_PC].lo = m_params[0];
        m_regs16[REG16_PC].hi = m_params[1];
    }

    void Cpu::instrJpCond(Condition condition) {
        fetchParams(2);
        bool doTheJump = false;
        switch (condition) {
        case CONDITION_NZ: doTheJump = !getFlag(FLAG_Z); break;
        case CONDITION_Z: doTheJump = getFlag(FLAG_Z); break;
        case CONDITION_NC: doTheJump = !getFlag(FLAG_C); break;
        case CONDITION_C: doTheJump = getFlag(FLAG_C); break;
        default: break;
        }
        if (doTheJump) {
            m_remainingCycles = 16;
            m_regs16[REG16_PC].lo = m_params[0];
            m_regs16[REG16_PC].hi = m_params[1];
        }
        else {
            m_remainingCycles = 12;
        }
    }

    void Cpu::instrJpHl(void) {
        m_remainingCycles = 4;

        m_regs16[REG16_PC].lo = m_regs8[REG8_L];
        m_regs16[REG16_PC].hi = m_regs8[REG8_H];
    }

    void Cpu::instrJr(void) {
        fetchParams(1);
        m_remainingCycles = 8;

        m_regs16[REG16_PC] += int8_t(m_params[0]);
    }

    void Cpu::instrJrCond(Condition condition) {
        fetchParams(1);
        bool doTheJump = false;
        switch (condition) {
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

    void Cpu::instrCall(void) {
        fetchParams(2);
        m_remainingCycles = 24;

        m_bus->write(m_regs16[REG16_SP], m_regs16[REG16_PC].hi);
        m_regs16[REG16_SP]--;
        m_bus->write(m_regs16[REG16_SP], m_regs16[REG16_PC].lo);
        m_regs16[REG16_SP]--;
        m_regs16[REG16_PC].lo = m_params[0];
        m_regs16[REG16_PC].hi = m_params[1];        
    }

    void Cpu::instrCallCond(Condition condition) {
        fetchParams(2);
        bool doTheJump = false;
        switch (condition) {
        case CONDITION_NZ: doTheJump = !getFlag(FLAG_Z); break;
        case CONDITION_Z: doTheJump = getFlag(FLAG_Z); break;
        case CONDITION_NC: doTheJump = !getFlag(FLAG_C); break;
        case CONDITION_C: doTheJump = getFlag(FLAG_C); break;
        default: break;
        }

        if (doTheJump) {
            m_remainingCycles = 24;
            m_bus->write(m_regs16[REG16_SP], m_regs16[REG16_PC].hi);
            m_regs16[REG16_SP]--;
            m_bus->write(m_regs16[REG16_SP], m_regs16[REG16_PC].lo);
            m_regs16[REG16_SP]--;
            m_regs16[REG16_PC].lo = m_params[0];
            m_regs16[REG16_PC].hi = m_params[1];
        } else {
            m_remainingCycles = 12;
        }
    }
}