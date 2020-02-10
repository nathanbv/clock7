/*
 * Nathan Bleuzen, 2018
 */

#ifndef COLORPROVIDER_HPP
#define COLORPROVIDER_HPP

#include <NeoPixelBus.h>

class ColorProvider
{
public:
    ColorProvider();
    ~ColorProvider() { }
    void resetSunriseColor(void);
    RgbColor getSunriseColor(time_t currentTime);

private:
    void updateSunriseColor(void);

    uint16_t m_count;
    time_t m_prevTime; // Last timestamp at which the color was updated
    HslColor m_hslColor;

    static const uint8_t s_updatePeriodInSec; // Time in second between 2 updates of the color
};

#endif // COLORPROVIDER_HPP
