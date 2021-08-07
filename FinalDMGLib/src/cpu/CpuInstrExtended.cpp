#include "Cpu.h"

#include "Bitwise8.h"

using namespace HelperLib;

namespace FinalDMG
{

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