#include "Cpu.h"
#include "bus/Bus.h"

namespace FinalDMG 
{
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
}