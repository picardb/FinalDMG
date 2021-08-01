#ifndef FINAL_DMG_BUS_
#define FINAL_DMG_BUS_

#include "cpu/Cpu.h"
#include "memory/BootstrapRom.h"

#include <memory>

namespace FinalDMG {

    class Bus {
    public:
        Bus() :
            m_cpu(nullptr),
            m_bootstrapRom(nullptr)
        { }

        uint8_t read(uint16_t address) const;
        void write(uint16_t address, uint8_t value);

        void connectCpu(std::shared_ptr<Cpu> cpu) { m_cpu = cpu; }
        void connectBootstrapRom(std::shared_ptr<BootstrapRom> bootstrapRom) { m_bootstrapRom = bootstrapRom; }

    private:
        std::shared_ptr<Cpu> m_cpu;
        std::shared_ptr<BootstrapRom> m_bootstrapRom;

        static const uint16_t ADDR_BOOTSTRAP_END = 255;
    };

}


#endif /* FINAL_DMG_BUS_ */
