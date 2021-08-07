#include "Cpu.h"
#include "bus/Bus.h"

namespace FinalDMG 
{
    void Cpu::instrAdd8Reg8(Reg8 reg, bool withCarry) {
        m_remainingCycles = 4;

        if (setHalfCarryOnAdd8(m_regs8[REG8_A], m_regs8[reg], withCarry & getFlag(FLAG_C))) { setFlag(FLAG_H); }
        else { resetFlag(FLAG_H); }
        if (setCarryOnAdd8(m_regs8[REG8_A], m_regs8[reg], withCarry & getFlag(FLAG_C))) { setFlag(FLAG_C); }
        else { resetFlag(FLAG_C); }

        m_regs8[REG8_A] += m_regs8[reg];

        if (m_regs8[REG8_A] == 0) { setFlag(FLAG_Z); }
        else { resetFlag(FLAG_Z); }
        resetFlag(FLAG_N);
    }

    void Cpu::instrAdd8Imm(bool withCarry) {
        fetchParams(1);
        m_remainingCycles = 8;

        if (setHalfCarryOnAdd8(m_regs8[REG8_A], m_params[0], withCarry & getFlag(FLAG_C))) { setFlag(FLAG_H); }
        else { resetFlag(FLAG_H); }
        if (setCarryOnAdd8(m_regs8[REG8_A], m_params[0], withCarry & getFlag(FLAG_C))) { setFlag(FLAG_C); }
        else { resetFlag(FLAG_C); }

        m_regs8[REG8_A] += m_params[0];

        if (m_regs8[REG8_A] == 0) {
            setFlag(FLAG_Z);
        }
        else {
            resetFlag(FLAG_Z);
        }
        resetFlag(FLAG_N);
    }

    void Cpu::instrAdd8MemInd(Reg16 regAddr, bool withCarry) {
        m_remainingCycles = 8;

        uint8_t memVal = m_bus->read(m_regs16[regAddr]);
        if (setHalfCarryOnAdd8(m_regs8[REG8_A], memVal, withCarry & getFlag(FLAG_C))) { setFlag(FLAG_H); }
        else { resetFlag(FLAG_H); }
        if (setCarryOnAdd8(m_regs8[REG8_A], memVal, withCarry & getFlag(FLAG_C))) { setFlag(FLAG_C); }
        else { resetFlag(FLAG_C); }

        m_regs8[REG8_A] += memVal;

        if (m_regs8[REG8_A] == 0) { setFlag(FLAG_Z); }
        else { resetFlag(FLAG_Z); }
        resetFlag(FLAG_N);
    }

    void Cpu::instrSub8Reg8(Reg8 reg, bool withCarry) {
        m_remainingCycles = 4;

        if (setHalfCarryOnSub8(m_regs8[REG8_A], m_regs8[reg], withCarry & getFlag(FLAG_C))) { setFlag(FLAG_H); }
        else { resetFlag(FLAG_H); }
        if (setCarryOnSub8(m_regs8[REG8_A], m_regs8[reg], withCarry & getFlag(FLAG_C))) { setFlag(FLAG_C); }
        else { resetFlag(FLAG_C); }

        m_regs8[REG8_A] -= m_regs8[reg];

        if (m_regs8[REG8_A] == 0) { setFlag(FLAG_Z); }
        else { resetFlag(FLAG_Z); }
        setFlag(FLAG_N);
    }

    void Cpu::instrSub8Imm(bool withCarry) {
        fetchParams(1);
        m_remainingCycles = 8;

        if (setHalfCarryOnSub8(m_regs8[REG8_A], m_params[0], withCarry & getFlag(FLAG_C))) { setFlag(FLAG_H); }
        else { resetFlag(FLAG_H); }
        if (setCarryOnSub8(m_regs8[REG8_A], m_params[0], withCarry & getFlag(FLAG_C))) { setFlag(FLAG_C); }
        else { resetFlag(FLAG_C); }

        m_regs8[REG8_A] -= m_params[0];

        if (m_regs8[REG8_A] == 0) { setFlag(FLAG_Z); }
        else { resetFlag(FLAG_Z); }
        setFlag(FLAG_N);
    }
    void Cpu::instrSub8MemInd(Reg16 regAddr, bool withCarry) {
        m_remainingCycles = 8;

        uint8_t memVal = m_bus->read(m_regs16[regAddr]);
        if (setHalfCarryOnSub8(m_regs8[REG8_A], memVal, withCarry & getFlag(FLAG_C))) { setFlag(FLAG_H); }
        else { resetFlag(FLAG_H); }
        if (setCarryOnSub8(m_regs8[REG8_A], memVal, withCarry & getFlag(FLAG_C))) { setFlag(FLAG_C); }
        else { resetFlag(FLAG_C); }

        m_regs8[REG8_A] += memVal;

        if (m_regs8[REG8_A] == 0) { setFlag(FLAG_Z); }
        else { resetFlag(FLAG_Z); }
        setFlag(FLAG_N);
    }

    void Cpu::instrAnd8Reg8(Reg8 reg) {
        m_remainingCycles = 4;

        m_regs8[REG8_A] &= m_regs8[reg];

        if (m_regs8[REG8_A] == 0) { setFlag(FLAG_Z); }
        else { resetFlag(FLAG_Z); }
        resetFlag(FLAG_N);
        setFlag(FLAG_H);
        resetFlag(FLAG_C);
    }
    
    void Cpu::instrAnd8Imm(void) {
        fetchParams(1);
        m_remainingCycles = 8;

        m_regs8[REG8_A] &= m_params[0];

        if (m_regs8[REG8_A] == 0) { setFlag(FLAG_Z); }
        else { resetFlag(FLAG_Z); }
        resetFlag(FLAG_N);
        setFlag(FLAG_H);
        resetFlag(FLAG_C);
    }

    void Cpu::instrAnd8MemInd(Reg16 regAddr) {
        m_remainingCycles = 8;

        uint8_t memVal = m_bus->read(m_regs16[regAddr]);
        m_regs8[REG8_A] &= memVal;

        if (m_regs8[REG8_A] == 0) { setFlag(FLAG_Z); }
        else { resetFlag(FLAG_Z); }
        resetFlag(FLAG_N);
        setFlag(FLAG_H);
        resetFlag(FLAG_C);
    }
    
    void Cpu::instrOr8Reg8(Reg8 reg) {
        m_remainingCycles = 4;

        m_regs8[REG8_A] |= m_regs8[reg];

        if (m_regs8[REG8_A] == 0) { setFlag(FLAG_Z); }
        else { resetFlag(FLAG_Z); }
        resetFlag(FLAG_N);
        resetFlag(FLAG_H);
        resetFlag(FLAG_C);
    }

    void Cpu::instrOr8Imm(void) {
        fetchParams(1);
        m_remainingCycles = 8;

        m_regs8[REG8_A] |= m_params[0];

        if (m_regs8[REG8_A] == 0) { setFlag(FLAG_Z); }
        else { resetFlag(FLAG_Z); }
        resetFlag(FLAG_N);
        resetFlag(FLAG_H);
        resetFlag(FLAG_C);
    }

    void Cpu::instrOr8MemInd(Reg16 regAddr) {
        m_remainingCycles = 8;

        uint8_t memVal = m_bus->read(m_regs16[regAddr]);
        m_regs8[REG8_A] |= memVal;

        if (m_regs8[REG8_A] == 0) { setFlag(FLAG_Z); }
        else { resetFlag(FLAG_Z); }
        resetFlag(FLAG_N);
        resetFlag(FLAG_H);
        resetFlag(FLAG_C);
    }

    void Cpu::instrXor8Reg8(Reg8 reg) {
        m_remainingCycles = 4;

        m_regs8[REG8_A] ^= m_regs8[reg];
        if (m_regs8[REG8_A] == 0) { setFlag(FLAG_Z); }
        else { resetFlag(FLAG_Z); }
        resetFlag(FLAG_N);
        resetFlag(FLAG_H);
        resetFlag(FLAG_C);
    }

    void Cpu::instrXor8Imm(void) {
        fetchParams(1);
        m_remainingCycles = 8;

        m_regs8[REG8_A] ^= m_params[0];

        if (m_regs8[REG8_A] == 0) { setFlag(FLAG_Z); }
        else { resetFlag(FLAG_Z); }
        resetFlag(FLAG_N);
        resetFlag(FLAG_H);
        resetFlag(FLAG_C);
    }

    void Cpu::instrXor8MemInd(Reg16 regAddr) {
        m_remainingCycles = 8;

        uint8_t memVal = m_bus->read(m_regs16[regAddr]);
        m_regs8[REG8_A] ^= memVal;

        if (m_regs8[REG8_A] == 0) { setFlag(FLAG_Z); }
        else { resetFlag(FLAG_Z); }
        resetFlag(FLAG_N);
        resetFlag(FLAG_H);
        resetFlag(FLAG_C);
    }

    void Cpu::instrCp8Reg8(Reg8 reg) {
        m_remainingCycles = 4;

        if (m_regs8[REG8_A] == m_regs8[reg]) { setFlag(FLAG_Z); }
        else { resetFlag(FLAG_Z); }
        setFlag(FLAG_N);
        if (setHalfCarryOnSub8(m_regs8[REG8_A], m_regs8[reg], false)) { setFlag(FLAG_H); }
        else { resetFlag(FLAG_H); }
        if (setCarryOnSub8(m_regs8[REG8_A], m_regs8[reg], false)) { setFlag(FLAG_C); }
        else { resetFlag(FLAG_C); }
    }

    void Cpu::instrCp8Imm(void) {
        fetchParams(1);
        m_remainingCycles = 8;

        if (m_regs8[REG8_A] == m_params[0]) { setFlag(FLAG_Z); }
        else { resetFlag(FLAG_Z); }
        setFlag(FLAG_N);
        if (setHalfCarryOnSub8(m_regs8[REG8_A], m_params[0], false)) { setFlag(FLAG_H); }
        else { resetFlag(FLAG_H); }
        if (setCarryOnSub8(m_regs8[REG8_A], m_params[0], false)) { setFlag(FLAG_C); }
        else { resetFlag(FLAG_C); }
    }

    void Cpu::instrCp8MemInd(Reg16 regAddr) {
        m_remainingCycles = 8;

        uint8_t memVal = m_bus->read(m_regs16[regAddr]);
        if (m_regs8[REG8_A] == memVal) { setFlag(FLAG_Z); }
        else { resetFlag(FLAG_Z); }
        setFlag(FLAG_N);
        if (setHalfCarryOnSub8(m_regs8[REG8_A], memVal, false)) { setFlag(FLAG_H); }
        else { resetFlag(FLAG_H); }
        if (setCarryOnSub8(m_regs8[REG8_A], memVal, false)) { setFlag(FLAG_C); }
        else { resetFlag(FLAG_C); }
    }
    
    void Cpu::instrInc8Reg8(Reg8 reg) {
        m_remainingCycles = 4;

        if (setHalfCarryOnAdd8(m_regs8[reg], 1, false)) { setFlag(FLAG_H); }
        else { resetFlag(FLAG_H); }

        m_regs8[reg]++;

        if (m_regs8[reg] == 0) { setFlag(FLAG_Z); }
        else { resetFlag(FLAG_Z); }
        resetFlag(FLAG_N);
    }

    void Cpu::instrInc8MemInd(Reg16 regAddr) {
        m_remainingCycles = 12;

        uint8_t memVal = m_bus->read(m_regs16[regAddr]);
        if (setHalfCarryOnAdd8(memVal, 1, false)) { setFlag(FLAG_H); }
        else { resetFlag(FLAG_H); }

        memVal++;
        m_bus->write(m_regs16[regAddr], memVal);

        if (memVal == 0) { setFlag(FLAG_Z); }
        else { resetFlag(FLAG_Z); }
        resetFlag(FLAG_N);
    }

    bool Cpu::setCarryOnAdd8(uint8_t left, uint8_t right, bool inCarry) {
        uint16_t carryVal;
        if (inCarry) { carryVal = 1; }
        else { carryVal = 0; }
        return (uint16_t(left) + uint16_t(right) + carryVal > 0xFF);
    }

    bool Cpu::setHalfCarryOnAdd8(uint8_t left, uint8_t right, bool inCarry) {
        uint8_t carryVal;
        if (inCarry) { carryVal = 1; }
        else { carryVal = 0; }
        return (((left & 0x0F) + (right & 0x0F) + carryVal) > 0x0F);
    }

    bool Cpu::setCarryOnSub8(uint8_t left, uint8_t right, bool inCarry) {
        uint8_t carryVal;
        if (inCarry) { carryVal = 1; }
        else { carryVal = 0; }
        return (uint16_t(left) - uint16_t(right) - carryVal > 0xFF);
    }
    bool Cpu::setHalfCarryOnSub8(uint8_t left, uint8_t right, bool inCarry) {
        uint8_t carryVal;
        if (inCarry) { carryVal = 1; }
        else { carryVal = 0; }
        return (((left & 0x0F) - (right & 0x0F) - carryVal) > 0x0F);
    }
}