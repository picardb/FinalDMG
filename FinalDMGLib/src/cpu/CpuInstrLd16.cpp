#include "Cpu.h"
#include "bus/Bus.h"

#include "Bitwise8.h"

using namespace HelperLib;

namespace FinalDMG 
{
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
        }
        else {
            resetFlag(FLAG_H);
        }
        if (m_regs16[dest] < m_regs16[src]) {
            setFlag(FLAG_C);
        }
        else {
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
}