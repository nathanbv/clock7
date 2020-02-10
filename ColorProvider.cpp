/*
 * Nathan Bleuzen, 2018
 */

#include "ColorProvider.hpp"
#include "config.h"

using namespace std;

const uint8_t ColorProvider::s_updatePeriodInSec = 1; // Update the color every second

#define HSL_COLOR_MAX 1.0f
#define HSL_COLOR_INCREMENT 0.005f

ColorProvider::ColorProvider():
        m_count(0),
        m_prevTime(0)
{ }

RgbColor ColorProvider::getSunriseColor(time_t currentTime)
{
    // Beginning of the sunrise
    if (m_prevTime == 0)
        m_hslColor = HslColor(20 / 360.0f, 0.f, HSL_COLOR_INCREMENT); // Redish-orange hue
    else if (currentTime >= m_prevTime + s_updatePeriodInSec)
        updateSunriseColor();
    m_prevTime = currentTime;

    logger.log(LOG_DEBUG, "Sunrise color: H%3d S%.3f L%.3f", (int)(m_hslColor.H * 360), m_hslColor.S, m_hslColor.L);
    return RgbColor(m_hslColor);
}

void ColorProvider::updateSunriseColor(void)
{
    uint8_t shiftRatio = 1.f + 10.f * (1.f - m_hslColor.S);
    if ((m_hslColor.L < HSL_COLOR_MAX - HSL_COLOR_INCREMENT) &&
        ((shiftRatio * m_hslColor.L <= m_hslColor.S) || (m_hslColor.S == HSL_COLOR_MAX)))
        m_hslColor.L += HSL_COLOR_INCREMENT;
    else if (m_hslColor.S < HSL_COLOR_MAX - HSL_COLOR_INCREMENT)
        m_hslColor.S += HSL_COLOR_INCREMENT;
    else
        logger.log(LOG_INFO, "The sun is up ! HSL color is at its max");
}
