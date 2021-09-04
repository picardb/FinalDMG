#ifndef FINAL_DMG_BUS_
#define FINAL_DMG_BUS_

#include "cpu/Cpu.h"
#include "memory/BootstrapRom.h"

#include <memory>
#include <cstdint>

namespace FinalDMG {

    class Bus {
    public:
        Bus() :
            m_cpu(nullptr),
            m_bootstrapRom(nullptr)
        { }

        uint8_t read(uint16_t address) const;
        void write(uint16_t address, uint8_t value);

        void connectCpu(Cpu *cpu) { m_cpu = cpu; }
        void connectBootstrapRom(BootstrapRom *bootstrapRom) { m_bootstrapRom = bootstrapRom; }

    private:
        Cpu *m_cpu;
        BootstrapRom *m_bootstrapRom;

        static const uint16_t ADDR_BOOTSTRAP_END = 255;
    };

}


#endif /* FINAL_DMG_BUS_ */
