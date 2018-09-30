/*
 * Nathan Bleuzen, 2018
 */

#include "SevenSeg.hpp"

SevenSeg::SevenSeg(uint8_t stripOffset, uint8_t pixelPerSeg, Adafruit_NeoPixel & strip):
        m_stripOffset(stripOffset),
        m_pixelPerSeg(pixelPerSeg),
        m_strip(strip)
{ }

SevenSeg::~SevenSeg()
{ }

void SevenSeg::set_color(uint8_t red, uint8_t green, uint8_t blue)
{
    m_color = m_strip.Color(red, green, blue);
}

void SevenSeg::display(uint8_t segChar)
{
    for (int iterSeg = 6; iterSeg >= 0; --iterSeg)
    {
        int offset = m_stripOffset + iterSeg * m_pixelPerSeg;
        uint32_t segState = (segChar & 0x1) ? m_color : 0; // Segment is on or off
        for (int iterPixel = offset; iterPixel < offset + m_pixelPerSeg; ++iterPixel)
        {
            m_strip.setPixelColor(iterPixel, segState);
        }
        segChar = segChar >> 1; // Move to the next segment
    }
}