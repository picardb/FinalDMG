#include "Emulator.h"

using namespace std;

namespace FinalDMG {
    Emulator::Emulator() :
        m_bus(make_unique<Bus>()),
        m_cpu(make_unique<Cpu>()),
        m_bootstrapRom(make_unique<BootstrapRom>())
    {
        m_bus->connectCpu(m_cpu.get());
        m_cpu->connectBus(m_bus.get());
        m_bus->connectBootstrapRom(m_bootstrapRom.get());
        m_bootstrapRom->loadFomFile("bootstrap.bin");
    }

    void Emulator::runForCycles(int cycles)
    {
        for (int i = 0; i < cycles; i++) {
            m_cpu->step();
        }
    }
}