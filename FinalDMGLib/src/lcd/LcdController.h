#ifndef FINAL_DMG_LCD_CONTROLLER_H__
#define FINAL_DMG_LCD_CONTROLLER_H__

#include <cstdint>

#include "bus/BusDevice.h"

namespace FinalDMG
{
    class LcdController : public BusDevice
    {
    public:
        enum Mode { LCD_MODE_0, LCD_MODE_1, LCD_MODE_2, LCD_MODE_3 };

        LcdController() :
            m_sleepCycles(0),
            m_regLcdc(0),
            m_regLy(0),
            m_currentMode(LCD_MODE_0)
        { }

        void reset(void);
        void step(void);

    private:
        int m_sleepCycles;
        uint8_t m_regLcdc;
        uint8_t m_regLy;
        Mode m_currentMode;
    };
}

#endif /* FINAL_DMG_LCD_CONTROLLER_H__ */