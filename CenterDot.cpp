/*
 * Nathan Bleuzen, 2018
 */

#include "CenterDot.hpp"

#include "config.h"

CenterDot::CenterDot(uint8_t stripOffset):
        DisplayElement(stripOffset)
{
    logger.log(LOG_DEBUG, "CenterDot stripOffset %2d", m_stripOffset);
}

void CenterDot::set_color(RgbColor color)
{
    m_color = color;
}

void CenterDot::set_color(uint8_t red, uint8_t green, uint8_t blue)
{
    set_color(RgbColor(red, green, blue));
}

void CenterDot::display(uint8_t segChar)
{
    RgbColor dotState = segChar ? m_color : offColor; // Dot is on or off
    for (uint8_t iterPixel = m_stripOffset; iterPixel < m_stripOffset + nbPixelPerDot; ++iterPixel)
        strip.SetPixelColor(iterPixel, dotState);
}
