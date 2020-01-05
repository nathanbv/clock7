/*
 * Nathan Bleuzen, 2018
 */

#include "CenterDot.hpp"
#include "config.h"

CenterDot::CenterDot(uint8_t stripOffset):
        m_stripOffset(stripOffset)
{
    logger.log(LOG_DEBUG, "CenterDot stripOffset %d", m_stripOffset);
}

void CenterDot::set_color(RgbColor color)
{
    m_color = color;
}

void CenterDot::display(bool state)
{
    RgbColor dotState = state ? m_color : offColor; // Dot is on or off
    for (uint8_t iterPixel = m_stripOffset; iterPixel < m_stripOffset + nbPixelPerDot; ++iterPixel)
        strip.SetPixelColor(iterPixel, dotState);
}
