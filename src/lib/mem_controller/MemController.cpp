#include "MemController.h"
#include "helpers/FileHelper.h"

#include <cstring>

namespace FinalDMG
{
    MemController::MemController(Emulator* emulator)
        : m_emulator(emulator)
    {
        FileHelper::loadBootstrap(m_bootstrapRom);
    }

    uint8_t MemController::readByte(uint16_t address) const
    {
        if (address < ADDRESS_CART_START) {
            return m_bootstrapRom[address];
        }
    }

    void MemController::writeByte(uint16_t address, uint8_t value)
    {
        if (address < ADDRESS_CART_START) {
            /* Do nothing. TODO: raise error */
        }
    }

    void MemController::readBlock(uint16_t address, int length, uint8_t* pDest) const
    {
        if (address < ADDRESS_CART_START) {
            memcpy(pDest, m_bootstrapRom, length);
        }
    }
}