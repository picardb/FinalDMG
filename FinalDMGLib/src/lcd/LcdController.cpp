#include "LcdController.h"

namespace FinalDMG
{
    void LcdController::reset(void) {
        m_sleepCycles = 0;
        m_regLcdc = 0x91;

    }

    void LcdController::step(void)
    {
        // TODO
    }
}