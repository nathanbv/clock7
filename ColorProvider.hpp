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
    RgbColor getSunriseColor(time_t currentTime);

private:
    void updateSunriseColor(void);

    uint16_t m_count;
    RgbColor m_color;
    time_t m_prevTime; // Last timestamp at which the color was updated

    static const uint8_t s_updatePeriodInSec; // Time in second between 2 updates of the color
    static const uint8_t s_sunriseColorTable[256][3]; // Table of ordered {r,g,b} values to use as sunrise colors
};

#endif // COLORPROVIDER_HPP
