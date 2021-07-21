#ifndef FINAL_DMG_MEM_CONTROLLER_H_
#define FINAL_DMG_MEM_CONTROLLER_H_

#include <cstdint>

namespace FinalDMG
{
    class Emulator;

    class MemController {
    public:
        MemController(Emulator* emulator);

    private:
        Emulator* m_emulator;

        uint8_t m_bios[256];
    };
}

#endif /* FINAL_DMG_MEM_CONTROLLER_H_ */