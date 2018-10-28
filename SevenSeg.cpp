/*
 * Nathan Bleuzen, 2018
 */

#include "SevenSeg.hpp"

SevenSeg::SevenSeg(uint8_t stripOffset, uint8_t pixelPerSeg):
        m_stripOffset(stripOffset),
        m_pixelPerSeg(pixelPerSeg)
{
    Serial.print(m_stripOffset);
}

SevenSeg::~SevenSeg()
{ }

void SevenSeg::set_color(uint8_t red, uint8_t green, uint8_t blue)
{
    Serial.print(m_stripOffset);
    m_color = RgbColor(red, green, blue);
}

void SevenSeg::display(uint8_t segChar)
{
    for (int8_t iterSeg = 6; iterSeg >= 0; --iterSeg)
    {
        uint8_t offset = m_stripOffset + iterSeg * m_pixelPerSeg;
        RgbColor segState = (segChar & 0x01) ? m_color : RgbColor(0); // Segment is on or off
        for (uint8_t iterPixel = offset; iterPixel < offset + m_pixelPerSeg; ++iterPixel)
        {
            strip.SetPixelColor(iterPixel, segState);
        }
        segChar = segChar >> 1; // Move to the next segment
    }
}