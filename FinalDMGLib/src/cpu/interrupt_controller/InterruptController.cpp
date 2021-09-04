#include "InterruptController.h"

#include "Bitwise8.h"

namespace FinalDMG
{
    using namespace HelperLib;

    void InterruptController::raiseInterrupt(Irq irq) {
        if (irq != IRQ_NONE) {
            Bitwise8::setBit(m_regIF, irq);
        }        
    }

    void InterruptController::clearInterrupt(Irq irq) {
        if (irq != IRQ_NONE) {
            Bitwise8::resetBit(m_regIF, irq);
        }        
    }

    void InterruptController::enableInterrupt(Irq irq) {
        if (irq != IRQ_NONE) {
            Bitwise8::setBit(m_regIE, irq);
        }
    }

    void InterruptController::disableInterrupt(Irq irq) {
        if (irq != IRQ_NONE) {
            Bitwise8::resetBit(m_regIE, irq);
        }
    }

    InterruptController::Irq InterruptController::getNextPendingInterrupt(void) const {
        if (!m_masterEnable) {
            return IRQ_NONE;
        }

        uint8_t irqPending = m_regIE & m_regIF;
        if (irqPending == 0) {
            return IRQ_NONE;
        }

        if (Bitwise8::getBit(irqPending, IRQ_VBLANK) == 1) {
            return IRQ_VBLANK;
        } else if (Bitwise8::getBit(irqPending, IRQ_LCDC) == 1) {
            return IRQ_LCDC;
        } else if (Bitwise8::getBit(irqPending, IRQ_TIMER) == 1) {
            return IRQ_TIMER;
        } else if (Bitwise8::getBit(irqPending, IRQ_SERIAL) == 1) {
            return IRQ_TIMER;
        } else if (Bitwise8::getBit(irqPending, IRQ_PAD) == 1) {
            return IRQ_PAD;
        } else {
            return IRQ_NONE;
        }
    }
}