#include "Cpu.h"
#include "bus/Bus.h"

namespace FinalDMG
{

    void Cpu::step(void) {
        if (m_remainingCycles == 0) {
            fetchNextInstruction();
            executeInstruction();
        }
        m_remainingCycles--;
    }

    void Cpu::fetchNextInstruction() {
        m_opcode = m_bus->read(m_regs16[REG16_PC]);
        m_regs16[REG16_PC]++;
    }

    void Cpu::executeInstruction() {
        switch (m_opcode) {
        case 0x01: instrLdReg16Imm(REG16_BC); break;
        case 0x02: instrLdMemReg8Ind(REG16_BC, REG8_A); break;
        case 0x06: instrLdReg8Imm(REG8_B); break;
        case 0x08: instrLdMemReg16Dir(REG16_SP); break;
        case 0x0A: instrLdReg8MemInd(REG8_A, REG16_BC); break;
        case 0x0E: instrLdReg8Imm(REG8_C); break;
        case 0x11: instrLdReg16Imm(REG16_DE); break;
        case 0x12: instrLdMemReg8Ind(REG16_DE, REG8_A); break;
        case 0x16: instrLdReg8Imm(REG8_D); break;
        case 0x1A: instrLdReg8MemInd(REG8_A, REG16_DE); break;
        case 0x1E: instrLdReg8Imm(REG8_E); break;
        case 0x20: instrJrCond(CONDITION_NZ); break;
        case 0x21: instrLdReg16Imm(REG16_HL); break;
        case 0x22: instrLdiMemReg8Ind(REG16_HL, REG8_A); break;
        case 0x26: instrLdReg8Imm(REG8_H); break;
        case 0x28: instrJrCond(CONDITION_Z); break;
        case 0x2A: instrLdiReg8MemInd(REG8_A, REG16_HL); break;
        case 0x2E: instrLdReg8Imm(REG8_L); break;
        case 0x30: instrJrCond(CONDITION_NC); break;
        case 0x31: instrLdReg16Imm(REG16_SP); break;
        case 0x32: instrLddMemReg8Ind(REG16_HL, REG8_A); break;
        case 0x36: instrLdMemImmInd(REG16_HL); break;
        case 0x38: instrJrCond(CONDITION_C); break;
        case 0x3A: instrLddReg8MemInd(REG8_A, REG16_HL); break;
        case 0x3E: instrLdReg8Imm(REG8_A); break;
        case 0x40: instrLdReg8Reg8(REG8_B, REG8_B); break;
        case 0x41: instrLdReg8Reg8(REG8_B, REG8_C); break;
        case 0x42: instrLdReg8Reg8(REG8_B, REG8_D); break;
        case 0x43: instrLdReg8Reg8(REG8_B, REG8_E); break;
        case 0x44: instrLdReg8Reg8(REG8_B, REG8_H); break;
        case 0x45: instrLdReg8Reg8(REG8_B, REG8_L); break;
        case 0x46: instrLdReg8MemInd(REG8_B, REG16_HL); break;
        case 0x47: instrLdReg8Reg8(REG8_B, REG8_A); break;
        case 0x48: instrLdReg8Reg8(REG8_C, REG8_B); break;
        case 0x49: instrLdReg8Reg8(REG8_C, REG8_C); break;
        case 0x4A: instrLdReg8Reg8(REG8_C, REG8_D); break;
        case 0x4B: instrLdReg8Reg8(REG8_C, REG8_E); break;
        case 0x4C: instrLdReg8Reg8(REG8_C, REG8_H); break;
        case 0x4D: instrLdReg8Reg8(REG8_C, REG8_L); break;
        case 0x4E: instrLdReg8MemInd(REG8_C, REG16_HL); break;
        case 0x4F: instrLdReg8Reg8(REG8_C, REG8_A); break;
        case 0x50: instrLdReg8Reg8(REG8_D, REG8_B); break;
        case 0x51: instrLdReg8Reg8(REG8_D, REG8_C); break;
        case 0x52: instrLdReg8Reg8(REG8_D, REG8_D); break;
        case 0x53: instrLdReg8Reg8(REG8_D, REG8_E); break;
        case 0x54: instrLdReg8Reg8(REG8_D, REG8_H); break;
        case 0x55: instrLdReg8Reg8(REG8_D, REG8_L); break;
        case 0x56: instrLdReg8MemInd(REG8_D, REG16_HL); break;
        case 0x57: instrLdReg8Reg8(REG8_D, REG8_A); break;
        case 0x58: instrLdReg8Reg8(REG8_E, REG8_B); break;
        case 0x59: instrLdReg8Reg8(REG8_E, REG8_C); break;
        case 0x5A: instrLdReg8Reg8(REG8_E, REG8_D); break;
        case 0x5B: instrLdReg8Reg8(REG8_E, REG8_E); break;
        case 0x5C: instrLdReg8Reg8(REG8_E, REG8_H); break;
        case 0x5D: instrLdReg8Reg8(REG8_E, REG8_L); break;
        case 0x5E: instrLdReg8MemInd(REG8_E, REG16_HL); break;
        case 0x5F: instrLdReg8Reg8(REG8_E, REG8_A); break;
        case 0x60: instrLdReg8Reg8(REG8_H, REG8_B); break;
        case 0x61: instrLdReg8Reg8(REG8_H, REG8_C); break;
        case 0x62: instrLdReg8Reg8(REG8_H, REG8_D); break;
        case 0x63: instrLdReg8Reg8(REG8_H, REG8_E); break;
        case 0x64: instrLdReg8Reg8(REG8_H, REG8_H); break;
        case 0x65: instrLdReg8Reg8(REG8_H, REG8_L); break;
        case 0x66: instrLdReg8MemInd(REG8_H, REG16_HL); break;
        case 0x67: instrLdReg8Reg8(REG8_H, REG8_A); break;
        case 0x68: instrLdReg8Reg8(REG8_L, REG8_B); break;
        case 0x69: instrLdReg8Reg8(REG8_L, REG8_C); break;
        case 0x6A: instrLdReg8Reg8(REG8_L, REG8_D); break;
        case 0x6B: instrLdReg8Reg8(REG8_L, REG8_E); break;
        case 0x6C: instrLdReg8Reg8(REG8_L, REG8_H); break;
        case 0x6D: instrLdReg8Reg8(REG8_L, REG8_L); break;
        case 0x6E: instrLdReg8MemInd(REG8_L, REG16_HL); break;
        case 0x6F: instrLdReg8Reg8(REG8_L, REG8_A); break;
        case 0x70: instrLdMemReg8Ind(REG16_HL, REG8_B); break;
        case 0x71: instrLdMemReg8Ind(REG16_HL, REG8_C); break;
        case 0x72: instrLdMemReg8Ind(REG16_HL, REG8_D); break;
        case 0x73: instrLdMemReg8Ind(REG16_HL, REG8_E); break;
        case 0x74: instrLdMemReg8Ind(REG16_HL, REG8_H); break;
        case 0x75: instrLdMemReg8Ind(REG16_HL, REG8_L); break;
        case 0x77: instrLdMemReg8Ind(REG16_HL, REG8_A); break;
        case 0x78: instrLdReg8Reg8(REG8_A, REG8_B); break;
        case 0x79: instrLdReg8Reg8(REG8_A, REG8_C); break;
        case 0x7A: instrLdReg8Reg8(REG8_A, REG8_D); break;
        case 0x7B: instrLdReg8Reg8(REG8_A, REG8_E); break;
        case 0x7C: instrLdReg8Reg8(REG8_A, REG8_H); break;
        case 0x7D: instrLdReg8Reg8(REG8_A, REG8_L); break;
        case 0x7E: instrLdReg8MemInd(REG8_A, REG16_HL); break;
        case 0x7F: instrLdReg8Reg8(REG8_A, REG8_A); break;
        case 0xA8: instrXor8(REG8_B); break;
        case 0xA9: instrXor8(REG8_C); break;
        case 0xAA: instrXor8(REG8_D); break;
        case 0xAB: instrXor8(REG8_E); break;
        case 0xAC: instrXor8(REG8_H); break;
        case 0xAD: instrXor8(REG8_L); break;
        case 0xAF: instrXor8(REG8_A); break;
        case 0xC1: instrPop(REG16_BC); break;
        case 0xC5: instrPush(REG16_BC); break;
        case 0xCB: instrExtended(); break;
        case 0xD1: instrPop(REG16_DE); break;
        case 0xD5: instrPush(REG16_DE); break;
        case 0xE0: instrLdPeriphReg8Imm(REG8_A); break;
        case 0xE1: instrPop(REG16_HL); break;
        case 0xE2: instrLdPeriphReg8Ind(REG8_C, REG8_A); break;
        case 0xE5: instrPush(REG16_HL); break;
        case 0xEA: instrLdMemReg8Dir(REG8_A); break;
        case 0xF0: instrLdReg8PeriphImm(REG8_A); break;
        case 0xF1: instrPop(REG16_AF); break;
        case 0xF2: instrLdReg8PeriphInd(REG8_A, REG8_C);
        case 0xF5: instrPush(REG16_AF); break;
        case 0xF8: instrLdReg16Reg16Offset(REG16_HL, REG16_SP); break;
        case 0xF9: instrLdReg16Reg16(REG16_SP, REG16_HL); break;
        case 0xFA: instrLdReg8MemDir(REG8_A); break;

        default:
            instrNop();
        }
    }

    void Cpu::fetchParams(int count) {
        for (int i = 0; i < count; i++) {
            m_params[i] = m_bus->read(m_regs16[REG16_PC]);
            m_regs16[REG16_PC]++;
        }
    }

}