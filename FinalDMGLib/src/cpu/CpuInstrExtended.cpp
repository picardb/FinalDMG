#include "Cpu.h"
#include "bus/Bus.h"

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
        case 0:
            switch (middle) {
            case 0: instrRlc(low); break;
            case 1: instrRrc(low); break;
            case 2: instrRl(low); break;
            case 3: instrRr(low); break;
            case 4: instrSla(low); break;
            case 5: instrSra(low); break;
            case 6: instrSwap(low); break;
            case 7: instrSrl(low); break;
            default: break;
            }
            break;
        case 1: instrBit(low, middle); break;
        case 2: instrRes(low, middle); break;
        case 3: instrSet(low, middle); break;
        default: break;
        }
    }

    void Cpu::instrRlc(int dest) {
        uint8_t value;
        if (dest == 6) {
            value = m_bus->read(m_regs16[REG16_HL]);
        } else {
            value = m_regs8[dest];
        }
        int bit7 = Bitwise8::getBit(value, 7);

        value <<= 1;
        value += bit7;

        if (dest == 6) {
            m_bus->write(m_regs16[REG16_HL], value);
        } else {
            m_regs8[dest] = value;
        }

        if (value == 0) {
            setFlag(FLAG_Z);
        } else {
            resetFlag(FLAG_Z);
        }
        resetFlag(FLAG_N);
        resetFlag(FLAG_H);
        if (bit7 == 1) {
            setFlag(FLAG_C);
        } else {
            resetFlag(FLAG_C);
        }
    }

    void Cpu::instrRrc(int dest) {
        uint8_t value;
        if (dest == 6) {
            value = m_bus->read(m_regs16[REG16_HL]);
        }
        else {
            value = m_regs8[dest];
        }
        int bit0 = Bitwise8::getBit(value, 0);

        value >>= 1;
        value += (bit0 << 7);

        if (dest == 6) {
            m_bus->write(m_regs16[REG16_HL], value);
        }
        else {
            m_regs8[dest] = value;
        }

        if (value == 0) {
            setFlag(FLAG_Z);
        }
        else {
            resetFlag(FLAG_Z);
        }
        resetFlag(FLAG_N);
        resetFlag(FLAG_H);
        if (bit0 == 1) {
            setFlag(FLAG_C);
        }
        else {
            resetFlag(FLAG_C);
        }
    }

    void Cpu::instrRl(int dest) {
        uint8_t value;
        if (dest == 6) {
            value = m_bus->read(m_regs16[REG16_HL]);
        }
        else {
            value = m_regs8[dest];
        }
        int bit7 = Bitwise8::getBit(value, 7);

        value <<= 1;
        if (getFlag(FLAG_C)) { value++; }

        if (dest == 6) {
            m_bus->write(m_regs16[REG16_HL], value);
        }
        else {
            m_regs8[dest] = value;
        }

        if (value == 0) {
            setFlag(FLAG_Z);
        }
        else {
            resetFlag(FLAG_Z);
        }
        resetFlag(FLAG_N);
        resetFlag(FLAG_H);
        if (bit7 == 1) {
            setFlag(FLAG_C);
        }
        else {
            resetFlag(FLAG_C);
        }
    }

    void Cpu::instrRr(int dest) {
        uint8_t value;
        if (dest == 6) {
            value = m_bus->read(m_regs16[REG16_HL]);
        }
        else {
            value = m_regs8[dest];
        }
        int bit0 = Bitwise8::getBit(value, 0);

        value >>= 1;
        if (getFlag(FLAG_C)) { value += 0x80; }

        if (dest == 6) {
            m_bus->write(m_regs16[REG16_HL], value);
        }
        else {
            m_regs8[dest] = value;
        }

        if (value == 0) {
            setFlag(FLAG_Z);
        } else {
            resetFlag(FLAG_Z);
        }
        resetFlag(FLAG_N);
        resetFlag(FLAG_H);
        if (bit0 == 1) {
            setFlag(FLAG_C);
        } else {
            resetFlag(FLAG_C);
        }
    }

    void Cpu::instrSla(int dest) {
        uint8_t value;
        if (dest == 6) {
            value = m_bus->read(m_regs16[REG16_HL]);
        } else {
            value = m_regs8[dest];
        }
        int bit7 = Bitwise8::getBit(value, 7);

        value <<= 1;

        if (dest == 6) {
            m_bus->write(m_regs16[REG16_HL], value);
        } else {
            m_regs8[dest] = value;
        }

        if (value == 0) {
            setFlag(FLAG_Z);
        } else {
            resetFlag(FLAG_Z);
        }
        resetFlag(FLAG_N);
        resetFlag(FLAG_H);
        if (bit7 == 1) {
            setFlag(FLAG_C);
        } else {
            resetFlag(FLAG_C);
        }
    }

    void Cpu::instrSra(int dest) {
        uint8_t value;
        if (dest == 6) {
            value = m_bus->read(m_regs16[REG16_HL]);
        } else {
            value = m_regs8[dest];
        }
        int bit0 = Bitwise8::getBit(value, 0);
        int bit7 = Bitwise8::getBit(value, 7);

        value >>= 1;
        if (bit7 == 1) { Bitwise8::setBit(value, 7); }

        if (dest == 6) {
            m_bus->write(m_regs16[REG16_HL], value);
        } else {
            m_regs8[dest] = value;
        }

        if (value == 0) {
            setFlag(FLAG_Z);
        } else {
            resetFlag(FLAG_Z);
        }
        resetFlag(FLAG_N);
        resetFlag(FLAG_H);
        if (bit0 == 1) {
            setFlag(FLAG_C);
        } else {
            resetFlag(FLAG_C);
        }
    }

    void Cpu::instrSwap(int dest) {
        uint8_t value;
        if (dest == 6) {
            value = m_bus->read(m_regs16[REG16_HL]);
        } else {
            value = m_regs8[dest];
        }

        uint8_t low = Bitwise8::extractSubVal(value, 0, 4);
        uint8_t high = Bitwise8::extractSubVal(value, 4, 4);
        value = (low << 4) + high;

        if (dest == 6) {
            m_bus->write(m_regs16[REG16_HL], value);
        } else {
            m_regs8[dest] = value;
        }

        if (value == 0) {
            setFlag(FLAG_Z);
        } else {
            resetFlag(FLAG_Z);
        }
        resetFlag(FLAG_N);
        resetFlag(FLAG_H);
        resetFlag(FLAG_C);
    }

    void Cpu::instrSrl(int dest) {
        uint8_t value;
        if (dest == 6) {
            value = m_bus->read(m_regs16[REG16_HL]);
        } else {
            value = m_regs8[dest];
        }
        int bit0 = Bitwise8::getBit(value, 0);

        value >>= 1;

        if (dest == 6) {
            m_bus->write(m_regs16[REG16_HL], value);
        } else {
            m_regs8[dest] = value;
        }

        if (value == 0) {
            setFlag(FLAG_Z);
        } else {
            resetFlag(FLAG_Z);
        }
        resetFlag(FLAG_N);
        resetFlag(FLAG_H);
        if (bit0 == 1) {
            setFlag(FLAG_C);
        } else {
            resetFlag(FLAG_C);
        }
    }

    void Cpu::instrBit(int dest, int index) {
        int bit;
        if (dest == 6) {
            bit = Bitwise8::getBit(m_bus->read(m_regs16[REG16_HL]), index);
        } else {
            bit = Bitwise8::getBit(m_regs8[dest], index);
        }

        if (bit == 0) {
            setFlag(FLAG_Z);
        } else {
            resetFlag(FLAG_Z);
        }
        resetFlag(FLAG_N);
        setFlag(FLAG_H);
    }

    void Cpu::instrSet(int dest, int index) {
        if (dest == 6) {
            uint8_t memVal = m_bus->read(m_regs16[REG16_HL]);
            Bitwise8::setBit(memVal, index);
            m_bus->write(m_regs16[REG16_HL], memVal);
        }
        else {
            Bitwise8::setBit(m_regs8[dest], index);
        }
    }

    void Cpu::instrRes(int dest, int index) {
        if (dest == 6) {
            uint8_t memVal = m_bus->read(m_regs16[REG16_HL]);
            Bitwise8::resetBit(memVal, index);
            m_bus->write(m_regs16[REG16_HL], memVal);
        }
        else {
            Bitwise8::resetBit(m_regs8[dest], index);
        }
    }
}