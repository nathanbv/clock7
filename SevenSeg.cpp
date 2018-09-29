#include "SevenSeg.hpp"

const uint8_t SevenSeg::m_segChar[SevenSeg::m_segCharSize] = {
    0b1111110, // 0
    0b0011000, // 1
    0b0110111, // 2
    0b0111101, // 3
    0b1011001, // 4
    0b1101101, // 5
    0b1101111, // 6
    0b0111000, // 7
    0b1111111, // 8
    0b1111001, // 9
    0b1111011, // A
    0b1111111, // B, same as 8
    0b1100110, // C
    0b1100111, // E
    0b1100011, // F
    0b1000110, // L
};

SevenSeg::SevenSeg(uint8_t stripOffset, uint8_t pixelPerSeg, Adafruit_NeoPixel & strip):
        m_stripOffset(stripOffset),
        m_pixelPerSeg(pixelPerSeg),
        m_strip(strip)
{ }

void SevenSeg::set_color(uint8_t red, uint8_t green, uint8_t blue)
{
    m_color = m_strip.Color(red, green, blue);
}

void SevenSeg::display(uint8_t value)
{
    if (value >= m_segCharSize)
        return;

    uint8_t seg = m_segChar[value];
    for (int seg_it = 6; seg_it >= 0; --seg_it)
    {
        int offset = m_stripOffset + seg_it * m_pixelPerSeg;
        uint32_t seg_state = (seg & 0x1) ? m_color : 0;
        for (int pixel_it = offset; pixel_it < offset + m_pixelPerSeg; ++pixel_it)
        {
            m_strip.setPixelColor(pixel_it, seg_state);
        }
        seg = seg >> 1;
    }
}