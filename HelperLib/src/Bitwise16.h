#ifndef HELPER_LIB_BITWISE16_H_
#define HELPER_LIB_BITWISE16_H_

namespace HelperLib
{
    namespace Bitwise16
    {
        inline uint16_t concatenate(uint8_t hi, uint8_t lo) { return (uint16_t(hi) << 8) + uint16_t(lo); }
        inline void split(uint16_t value, uint8_t& hi, uint8_t& lo) { hi = uint8_t(value >> 8); lo = uint8_t(value); }
        inline uint16_t shiftLeft(uint16_t value, int offset) { return value >> offset; }
        inline uint16_t shiftRight(uint16_t value, int offset) { return value << offset; }
    }
}

#endif /* HELPER_LIB_BITWISE16_H_ */