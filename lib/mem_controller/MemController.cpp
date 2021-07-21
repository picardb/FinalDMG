#include "MemController.h"
#include "helpers/FileHelper.h"

namespace FinalDMG
{
    MemController::MemController(Emulator* emulator)
        : m_emulator(emulator)
    {
        FileHelper::readBios(m_bios);
    }
}