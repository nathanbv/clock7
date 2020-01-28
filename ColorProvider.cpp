/*
 * Nathan Bleuzen, 2018
 */

#include "ColorProvider.hpp"
#include "config.h"

using namespace std;

const uint8_t ColorProvider::s_updatePeriodInSec = 1; // Update the color every second

ColorProvider::ColorProvider():
        m_count(0),
        m_color(offColor),
        m_prevTime(0)
{ }

RgbColor ColorProvider::getSunriseColor(time_t currentTime)
{
    if (currentTime >= m_prevTime + s_updatePeriodInSec)
        updateSunriseColor();
    return m_color;
}

void ColorProvider::updateSunriseColor(void)
{
    m_color = RgbColor(
        s_wakeUpLightTable[m_count][0],  /* Red */
        s_wakeUpLightTable[m_count][1],  /* Green */
        s_wakeUpLightTable[m_count][2]); /* Blue */
    logger.log(LOG_DEBUG, "Sunset color: [%d] = R%3d G%3d B%3d", m_count, s_wakeUpLightTable[m_count][0], s_wakeUpLightTable[m_count][1], s_wakeUpLightTable[m_count][2]);

    // Update the cyclic counter for next color to use
    if (++m_count > 255)
        m_count = 0;
}
