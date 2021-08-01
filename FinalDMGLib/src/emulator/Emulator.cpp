#include "Emulator.h"

using namespace std;

namespace FinalDMG {
    Emulator::Emulator() :
        m_bus(make_shared<Bus>()),
        m_cpu(make_shared<Cpu>()),
        m_bootstrapRom(make_shared<BootstrapRom>())
    {
        m_bus->connectCpu(m_cpu);
        m_cpu->connectBus(m_bus);
        m_bus->connectBootstrapRom(m_bootstrapRom);
        m_bootstrapRom->loadFomFile("bootstrap.bin");
    }

    void Emulator::runForCycles(int cycles)
    {
        for (int i = 0; i < cycles; i++) {
            m_cpu->step();
        }
    }
}