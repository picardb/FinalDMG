#ifndef FINAL_DMG_CPU_
#define FINAL_DMG_CPU_

#include <bus/BusDevice.h>

#include <memory>
#include <array>

namespace FinalDMG {
    class Cpu : public BusDevice
    {
    public:
        enum Reg8 { REG8_A, REG8_F, REG8_B, REG8_C, REG8_D, REG8_E, REG8_H, REG8_L };
        enum Reg16 { REG16_AF, REG16_BC, REG16_DE, REG16_HL };

        Cpu() :
            m_regs8 { 0, 0, 0, 0, 0, 0, 0, 0},
            m_regs16 { Reg16_t(m_regs8[REG8_A], m_regs8[REG8_F]),
                       Reg16_t(m_regs8[REG8_B], m_regs8[REG8_C]),
                       Reg16_t(m_regs8[REG8_D], m_regs8[REG8_E]),
                       Reg16_t(m_regs8[REG8_H], m_regs8[REG8_L]) },
            m_regPc(0),
            m_regSp(0),
            m_opcode(0),
            m_params { 0, 0 },
            m_remainingCycles(0)
        { }

        void step(void);

        void setReg8(Reg8 reg, uint8_t val) { m_regs8[reg] = val; }

        uint8_t getReg8(Reg8 reg) const { return m_regs8[reg]; }
        uint16_t getRegPc(void) const { return m_regPc; }
        uint16_t getRegSp(void) const { return m_regSp; }
        uint8_t getOpcode(void) const { return m_opcode; }
        uint8_t getRemainingCycles(void) const { return m_remainingCycles; }

    private:
        struct Reg16_t {
            uint8_t& m_hi;
            uint8_t& m_lo;

            Reg16_t(uint8_t& hi, uint8_t& lo) :
                m_hi(hi), m_lo(lo)
            { }
        };

        std::array<uint8_t, 8>  m_regs8;
        std::array<Reg16_t, 4>  m_regs16;
        uint16_t                m_regPc;
        uint16_t                m_regSp;
        uint8_t                 m_opcode;
        std::array<uint8_t, 2>  m_params;
        uint8_t                 m_remainingCycles; // Remaining cycles until next instrution

        void fetchNextInstruction();
        void executeInstruction();
    };

}

#endif /* FINAL_DMG_CPU_ */
