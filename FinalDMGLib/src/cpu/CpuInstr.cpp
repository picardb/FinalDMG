#include "Cpu.h"
#include "bus/Bus.h"

#include "Bitwise8.h"

using namespace HelperLib;

namespace FinalDMG {

    void Cpu::instrNop(void) {
        m_remainingCycles = 4;
    }

    // 8-bit loads

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
    
    void Cpu::instrLddReg8MemInd(Reg8 dest, Reg16 regAddr) {
        instrLdReg8MemInd(dest, regAddr);
        m_regs16[regAddr]--;
    }
    void Cpu::instrLdiReg8MemInd(Reg8 dest, Reg16 regAddr) {
        instrLdReg8MemInd(dest, regAddr);
        m_regs16[regAddr]++;
    }

    void Cpu::instrLdReg8MemDir(Reg8 reg) {
        fetchParams(2);
        m_remainingCycles = 16;

        m_regs8[reg] = m_bus->read(m_params[0] + (m_params[1] << 8));
    }

    void Cpu::instrLdReg8PeriphInd(Reg8 regVal, Reg8 regOffset) {
        m_remainingCycles = 8;

        m_regs8[regVal] = m_bus->read(0xFF00 + uint16_t(m_regs8[regOffset]));
    }

    void Cpu::instrLdReg8PeriphImm(Reg8 dest) {
        fetchParams(1);
        m_remainingCycles = 12;

        m_regs8[dest] = m_bus->read(0xFF00 + uint16_t(m_params[0]));
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

    void Cpu::instrLdMemReg8Dir(Reg8 reg) {
        fetchParams(2);
        m_remainingCycles = 16;

        m_bus->write(m_params[0] + (m_params[1] << 8), m_regs8[reg]);
    }

    void Cpu::instrLdPeriphReg8Ind(Reg8 regOffset, Reg8 regVal) {
        m_remainingCycles = 8;

        m_bus->write(0xFF00 + uint16_t(m_regs8[regOffset]), m_regs8[regVal]);
    }

    void Cpu::instrLdPeriphReg8Imm(Reg8 src) {
        fetchParams(1);
        m_remainingCycles = 12;

        m_bus->write(0xFF00 + uint16_t(m_params[0]), m_regs8[src]);
    }

    // 16-bit loads

    void Cpu::instrLdReg16Imm(Reg16 reg) {
        m_remainingCycles = 12;
        fetchParams(2);

        m_regs16[reg].lo = m_params[0];
        m_regs16[reg].hi = m_params[1];
    }

    void Cpu::instrLdReg16Reg16(Reg16 dest, Reg16 src) {
        m_remainingCycles = 8;

        m_regs16[dest] = m_regs16[src];
    }

    void Cpu::instrLdReg16Reg16Offset(Reg16 dest, Reg16 src) {
        fetchParams(1);
        m_remainingCycles = 12;
        uint8_t halfSrc = Bitwise8::extractSubVal(m_regs16[src].hi, 0, 4);
        uint8_t halfOffset = Bitwise8::extractSubVal(m_params[0], 0, 4);

        m_regs16[dest] = uint16_t(m_regs16[src]) + uint16_t(m_params[0]);

        resetFlag(FLAG_Z);
        resetFlag(FLAG_N);
        if (Bitwise8::getBit(halfSrc + halfOffset, 5) == 1) {
            setFlag(FLAG_H);
        } else {
            resetFlag(FLAG_H);
        }
        if (m_regs16[dest] < m_regs16[src]) {
            setFlag(FLAG_C);
        } else {
            resetFlag(FLAG_C);
        }
    }

    void Cpu::instrLdMemReg16Dir(Reg16 src) {
        fetchParams(2);
        m_remainingCycles = 20;

        m_bus->write(m_params[0] + (m_params[1] << 8), m_regs16[src].lo);
        m_bus->write(m_params[0] + (m_params[1] << 8) + 1, m_regs16[src].hi);
    }

    void Cpu::instrPush(Reg16 reg) {
        m_remainingCycles = 16;

        m_bus->write(m_regs16[REG16_SP], m_regs16[reg].hi);
        m_regs16[REG16_SP]--;
        m_bus->write(m_regs16[REG16_SP], m_regs16[reg].lo);
        m_regs16[REG16_SP]--;
    }

    void Cpu::instrPop(Reg16 reg) {
        m_remainingCycles = 12;

        m_regs16[reg].lo = m_bus->read(m_regs16[REG16_SP]);
        m_regs16[REG16_SP]++;
        m_regs16[reg].hi = m_bus->read(m_regs16[REG16_SP]);
        m_regs16[REG16_SP]++;
    }

    // 8-bit ALU

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