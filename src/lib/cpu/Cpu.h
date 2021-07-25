#ifndef FINAL_DMG_CPU_
#define FINAL_DMG_CPU_

#include <memory>

namespace FinalDMG {

    class Emulator;

    class Cpu {
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

        enum Reg16 {
            REG16_AF,
            REG16_BC,
            REG16_DE,
            REG16_HL
        };

        Cpu(Emulator* emulator)
            : m_emulator(emulator)
        { }

        void setReg8(Reg8 reg, uint8_t val) { m_regs8[reg] = val; }
        uint8_t getReg8(Reg8 reg) const { return m_regs8[reg]; }

    private:
        static const int REGS8_NB = 8;
        Emulator *m_emulator;

        uint8_t     m_regs8[REGS8_NB];
        uint16_t    m_regPc;
        uint16_t    m_regSp;
        uint8_t     m_opcode;
        uint8_t     m_params[2];

        void fetchNextInstruction();
        void executeInstruction();
    };

}


#endif /* FINAL_DMG_CPU_ */
