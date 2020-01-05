/*
 * Nathan Bleuzen, 2018
 */

#include "SevenSeg.hpp"
#include "config.h"

SevenSeg::SevenSeg(uint8_t stripOffset):
        m_stripOffset(stripOffset)
{
    logger.log(LOG_DEBUG, "SevenSeg stripOffset %d", m_stripOffset);
}

void SevenSeg::set_color(RgbColor color)
{
    m_color = color;
}

void SevenSeg::display(uint8_t segChar)
{
    for (int8_t iterSeg = 6; iterSeg >= 0; --iterSeg)
    {
        uint8_t offset = m_stripOffset + iterSeg * nbPixelPerSeg;
        RgbColor segState = (segChar & 0x01) ? m_color : offColor; // Segment is on or off
        for (uint8_t iterPixel = offset; iterPixel < (offset + nbPixelPerSeg); ++iterPixel)
            strip.SetPixelColor(iterPixel, segState);
        segChar = segChar >> 1; // Move to the next segment
    }
}
