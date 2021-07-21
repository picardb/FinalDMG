#ifndef FINAL_DMG_CPU_REGS_
#define FINAL_DMG_CPU_REGS_

#include <cstdint>

namespace FinalDMG {

    class CpuRegs {
    public:
        enum Reg8 {
            REG8_A,
            REG8_F,
            REG8_B,
            REG8_C,
            REG8_D,
            REG8_E,
            REG8_H,
            REG8_L
        };

        CpuRegs();

        void setReg8(Reg8 reg, uint8_t val) { m_regs8[reg] = val; }
        uint8_t reg8(Reg8 reg) const { return m_regs8[reg]; }

    private:
        static const int REGS8_NB = 8;

        uint8_t m_regs8[REGS8_NB];
    };

}

#endif /* FINAL_DMG_CPU_REGS_ */