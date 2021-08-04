#ifndef HELPER_LIB_BITWISE8_H_
#define HELPER_LIB_BITWISE8_H_

namespace HelperLib
{
    namespace Bitwise8
    {
        inline void setBit(uint8_t& value, int index) { value |= (1 << index); }
        inline void resetBit(uint8_t& value, int index) { value &= ~(1 << index); }
        inline int getBit(const uint8_t value, int index) { return (value >> index) & 0x01; }
        inline uint8_t extractSubVal(const uint8_t value, int offset, int size) {
            uint8_t mask = 1;
            for (int i = 0; i < size; i++) { mask *= 2; }
            mask--;
            return (value >> offset) & mask;
        }
    }
}

#endif /* HELPER_LIB_BITWISE8_H_ */