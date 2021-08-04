#include "Cpu.h"
#include "bus/Bus.h"

#include "Bitwise8.h"

using namespace HelperLib;

namespace FinalDMG {

    void Cpu::instrNop(void) {
        m_remainingCycles = 4;
    }

    void Cpu::instrLdReg8Imm(Reg8 reg) {
        fetchParams(1);
        m_remainingCycles = 8;

        m_regs8[reg] = m_params[0];
    }

    void Cpu::instrLdReg8Reg8(Reg8 dest, Reg8 src) {
        m_remainingCycles = 4;

        m_regs8[dest] = m_regs8[src];
    }

    void Cpu::instrLdReg8MemInd(Reg8 dest, Reg16 regAddr) {
        m_remainingCycles = 8;

        m_regs8[dest] = m_bus->read(regAddr);
    }

    void Cpu::instrLdMemReg8Ind(Reg16 regAddr, Reg8 regVal) {
        m_remainingCycles = 8;

        m_bus->write(m_regs16[regAddr], m_regs8[regVal]);
    }

    void Cpu::instrLddMemReg8Ind(Reg16 regAddr, Reg8 regVal) {
        instrLdMemReg8Ind(regAddr, regVal);
        m_regs16[regAddr]--;
    }

    void Cpu::instrLdiMemReg8Ind(Reg16 regAddr, Reg8 regVal) {
        instrLdMemReg8Ind(regAddr, regVal);
        m_regs16[regAddr]++;
    }

    void Cpu::instrLdMemImmInd(Reg16 regAddr) {
        fetchParams(1);
        m_remainingCycles = 12;

        m_bus->write(m_regs16[regAddr], m_params[0]);
    }

    void Cpu::instrLdReg16Imm(Reg16 reg) {
        m_remainingCycles = 12;
        fetchParams(2);

        m_regs16[reg].lo = m_params[0];
        m_regs16[reg].hi = m_params[1];
    }

    void Cpu::instrXor8(Reg8 reg) {
        m_remainingCycles = 4;
        m_regs8[REG8_A] = m_regs8[REG8_A] ^ m_regs8[reg];
        if (m_regs8[REG8_A] == 0) { setFlag(FLAG_Z); }
        resetFlag(FLAG_N);
        resetFlag(FLAG_H);
        resetFlag(FLAG_C);
    }

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

    void Cpu::instrExtended(void) {
        fetchParams(1);

        uint8_t low = Bitwise8::extractSubVal(m_params[0], 0, 3);
        uint8_t middle = Bitwise8::extractSubVal(m_params[0], 3, 3);
        uint8_t high = Bitwise8::extractSubVal(m_params[0], 6, 2);

        if (low == 6) { m_remainingCycles = 16; }
        else { m_remainingCycles = 8; }

        switch (high) {
        case 1: instrBit(low, middle); break;
        default: break;
        }
    }

    void Cpu::instrBit(int dest, int index) {
        if (dest == 6) { /* TODO */ }
        else {
            int bit = Bitwise8::getBit(m_regs8[dest], index);
            if (bit == 0) {
                setFlag(FLAG_Z);
            }
            else {
                resetFlag(FLAG_Z);
            }
            resetFlag(FLAG_N);
            setFlag(FLAG_H);
        }
    }

}