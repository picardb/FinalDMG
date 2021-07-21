#include "CpuRegs.h"

namespace FinalDMG {

    CpuRegs::CpuRegs() {
        for (int i = 0 ; i < REGS8_NB ; i++) {
            m_regs8[i] = 0;
        }
    }

}