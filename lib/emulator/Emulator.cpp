#include "Emulator.h"

using namespace std;

namespace FinalDMG {
    Emulator::Emulator() :
        m_cpu(new Cpu(this)),
        m_memController(new MemController(this))
    {
    }
}