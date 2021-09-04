#ifndef FINAL_DMG_INTERRUPT_CONTROLLER_
#define FINAL_DMG_INTERRUPT_CONTROLLER_

#include <cstdint>

namespace FinalDMG {
    class InterruptController
    {
    public:
        enum Irq {
            IRQ_VBLANK = 0,
            IRQ_LCDC = 1,
            IRQ_TIMER = 2,
            IRQ_SERIAL = 3,
            IRQ_PAD = 4,
            IRQ_NONE = 8
        };

        InterruptController() :
            m_masterEnable(false),
            m_regIF(0),
            m_regIE(0)
        {}

        void enableMasterInterrupts(void) { m_masterEnable = true; }
        void disableMasterInterrupt(void) { m_masterEnable = false; }
        void raiseInterrupt(Irq irq);
        void clearInterrupt(Irq irq);
        void enableInterrupt(Irq irq);
        void disableInterrupt(Irq irq);

        void setRegIF(uint8_t value) { m_regIF = value; }
        void setRegIE(uint8_t value) {m_regIE = value; }
        uint8_t getRegIF(void) const { return m_regIF; }
        uint8_t getRegIE(void) const { return m_regIE; }

        Irq getNextPendingInterrupt(void) const;

    private:
        bool m_masterEnable;
        uint8_t m_regIF;
        uint8_t m_regIE;
    };

    struct InterruptControllerState
    {
        bool m_masterEnable = false;
        uint8_t m_regIF = 0;
        uint8_t m_regIE = 0;
    };
}

#endif /* FINAL_DMG_INTERRUPT_CONTROLLER_ */