#ifndef FINAL_DMG_CPU_
#define FINAL_DMG_CPU_

#include "bus/BusDevice.h"
#include "interrupt_controller/InterruptController.h"

#include <memory>
#include <array>
#include <functional>
#include <cstdint>

#include "Bitwise8.h"
#include "Bitwise16.h"

namespace FinalDMG {
    class Cpu : public BusDevice
    {
    public:
        enum Reg8 { REG8_A = 7, REG8_F = 6, REG8_B = 0, REG8_C = 1, REG8_D = 2, REG8_E = 3, REG8_H = 4, REG8_L = 5};
        enum Reg16 { REG16_AF, REG16_BC, REG16_DE, REG16_HL, REG16_PC, REG16_SP };
        enum Flag { FLAG_Z = 7, FLAG_N = 6, FLAG_H = 5, FLAG_C = 4 };

        Cpu() :
            m_regs8{ 0, 0, 0, 0, 0, 0, 0, 0 },
            m_regPcHi(0), m_regPcLo(0),
            m_regSpHi(0), m_regSpLo(0),
            m_regs16{ Reg16_t(m_regs8[REG8_A], m_regs8[REG8_F]),
                       Reg16_t(m_regs8[REG8_B], m_regs8[REG8_C]),
                       Reg16_t(m_regs8[REG8_D], m_regs8[REG8_E]),
                       Reg16_t(m_regs8[REG8_H], m_regs8[REG8_L]),
                       Reg16_t(m_regPcHi, m_regPcLo),
                       Reg16_t(m_regSpHi, m_regSpLo) },
            m_opcode(0),
            m_params{ 0, 0 },
            m_remainingCycles(0),
            m_irq()
        { }

        void step(void);

        //CpuState getState(void) const;
        //void setState(const CpuState& state);

        void setReg8(Reg8 reg, uint8_t val) { m_regs8[reg] = val; }
        void setFlag(Flag flag) { HelperLib::Bitwise8::setBit(m_regs8[REG8_F], flag); }
        void resetFlag(Flag flag) { HelperLib::Bitwise8::resetBit(m_regs8[REG8_F], flag); }
        void raiseInterrupt(InterruptController::Irq irq) { m_irq.raiseInterrupt(irq); }
        void clearInterrupt(InterruptController::Irq irq) { m_irq.clearInterrupt(irq); }
        void enableInterrupt(InterruptController::Irq irq) { m_irq.enableInterrupt(irq); }
        void disableInterrupt(InterruptController::Irq irq) { m_irq.disableInterrupt(irq); }

        uint8_t getReg8(Reg8 reg) const { return m_regs8[reg]; }
        uint16_t getReg16(Reg16 reg) const { return uint16_t(m_regs16[reg]); }
        bool getFlag(Flag flag) { return HelperLib::Bitwise8::getBit(m_regs8[REG8_F], flag); }
        uint8_t getOpcode(void) const { return m_opcode; }
        int getRemainingCycles(void) const { return m_remainingCycles; }

    private:
        struct Reg16_t {
            uint8_t& hi;
            uint8_t& lo;

            Reg16_t(uint8_t& _hi, uint8_t& _lo) :
                hi(_hi), lo(_lo)
            { }

            Reg16_t& operator=(const Reg16_t reg) { hi = reg.hi; lo = reg.lo; return *this; }
            Reg16_t& operator=(const uint16_t value) { HelperLib::Bitwise16::split(value, hi, lo); return *this; }
            Reg16_t& operator++() { *this = uint16_t(*this) + 1; return *this; }
            Reg16_t operator++(int) { Reg16_t temp = *this; ++*this; return temp; }
            Reg16_t& operator--() { *this = uint16_t(*this) - 1; return *this; }
            Reg16_t operator--(int) { Reg16_t temp = *this; --*this; return temp; }
            Reg16_t& operator+=(const uint16_t value) { *this = uint16_t(*this) + value; return *this; }
            operator uint16_t(void) const { return HelperLib::Bitwise16::concatenate(hi, lo); }
        };

        enum Condition { CONDITION_NZ, CONDITION_Z, CONDITION_NC, CONDITION_C };

        std::array<uint8_t, 8>   m_regs8;
        uint8_t                  m_regSpHi, m_regSpLo;
        uint8_t                  m_regPcHi, m_regPcLo;
        std::array<Reg16_t, 6>   m_regs16;
        uint8_t                  m_opcode;
        std::array<uint8_t, 2>   m_params;
        int                      m_remainingCycles; // Remaining cycles until next instrution
        InterruptController      m_irq;

        void fetchNextInstruction();
        void executeInstruction();
        void fetchParams(int count);
        void processInterrupts(void);

        // Misc
        void instrNop(void);

        // 8-bit loads
        void instrLdReg8Imm(Reg8 reg);
        void instrLdReg8Reg8(Reg8 dest, Reg8 src);
        void instrLdReg8MemInd(Reg8 dest, Reg16 regAddr);
        void instrLddReg8MemInd(Reg8 dest, Reg16 regAddr);
        void instrLdiReg8MemInd(Reg8 dest, Reg16 regAddr);
        void instrLdReg8MemDir(Reg8 reg);
        void instrLdReg8PeriphInd(Reg8 regVal, Reg8 regOffset);
        void instrLdReg8PeriphImm(Reg8 dest);
        void instrLdMemReg8Ind(Reg16 regAddr, Reg8 regVal);
        void instrLddMemReg8Ind(Reg16 regAddr, Reg8 regVal);
        void instrLdiMemReg8Ind(Reg16 regAddr, Reg8 regVal);
        void instrLdMemImmInd(Reg16 regAddr);
        void instrLdMemReg8Dir(Reg8 reg);
        void instrLdPeriphReg8Ind(Reg8 regOffset, Reg8 regVal);
        void instrLdPeriphReg8Imm(Reg8 src);

        // 16-bit loads
        void instrLdReg16Imm(Reg16 reg);
        void instrLdReg16Reg16(Reg16 dest, Reg16 src);
        void instrLdReg16Reg16Offset(Reg16 dest, Reg16 src);
        void instrLdMemReg16Dir(Reg16 src);
        void instrPush(Reg16 reg);
        void instrPop(Reg16 reg);

        // 8-bit ALU
        void instrAdd8Reg8(Reg8 reg, bool withCarry = false);
        void instrAdd8Imm(bool withCarry = false);
        void instrAdd8MemInd(Reg16 regAddr, bool withCarry = false);
        void instrSub8Reg8(Reg8 reg, bool withCarry = false);
        void instrSub8Imm(bool withCarry = false);
        void instrSub8MemInd(Reg16 regAddr, bool withCarry = false);
        void instrAnd8Reg8(Reg8 reg);
        void instrAnd8Imm(void);
        void instrAnd8MemInd(Reg16 regAddr);
        void instrOr8Reg8(Reg8 reg);
        void instrOr8Imm(void);
        void instrOr8MemInd(Reg16 regAddr);
        void instrXor8Reg8(Reg8 reg);
        void instrXor8Imm(void);
        void instrXor8MemInd(Reg16 regAddr);
        void instrCp8Reg8(Reg8 reg);
        void instrCp8Imm(void);
        void instrCp8MemInd(Reg16 regAddr);
        void instrInc8Reg8(Reg8 reg);
        void instrInc8MemInd(Reg16 regAddr);
        void instrDec8Reg8(Reg8 reg);
        void instrDec8MemInd(Reg16 regAddr);

        // 16-bit ALU
        void instrAddHlReg16(Reg16 reg);
        void instrAddSpImm(void);
        void instrIncReg16(Reg16 reg);
        void instrDecReg16(Reg16 reg);

        // Jumps
        void instrJp(void);
        void instrJpCond(Condition condition);
        void instrJpHl(void);
        void instrJr(void);
        void instrJrCond(Condition condition);
        void instrCall(void);
        void instrCallCond(Condition condition);

        // Extended instruction
        void instrExtended(void);
        void instrRlc(int dest);
        void instrRrc(int dest);
        void instrRl(int dest);
        void instrRr(int dest);
        void instrSla(int dest);
        void instrSra(int dest);
        void instrSwap(int dest);
        void instrSrl(int dest);
        void instrBit(int dest, int index);
        void instrSet(int dest, int index);
        void instrRes(int dest, int index);

        // Carries utility
        bool setCarryOnAdd8(uint8_t left, uint8_t right, bool inCarry);
        bool setHalfCarryOnAdd8(uint8_t left, uint8_t right, bool inCarry);
        bool setCarryOnSub8(uint8_t left, uint8_t right, bool inCarry);
        bool setHalfCarryOnSub8(uint8_t left, uint8_t right, bool inCarry);
    };

    struct CpuState
    {
        uint8_t m_regA = 0;
        uint8_t m_regF = 0;
        uint8_t m_regB = 0;
        uint8_t m_regC = 0;
        uint8_t m_regD = 0;
        uint8_t m_regE = 0;
        uint8_t m_regH = 0;
        uint8_t m_regL = 0;
        uint16_t m_regPc = 0;
        uint16_t m_regSp = 0;
        InterruptControllerState m_irqState;
    };

}

#endif /* FINAL_DMG_CPU_ */
