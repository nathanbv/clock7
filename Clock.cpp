/*
 * Nathan Bleuzen, 2018
 */

#include "Clock.hpp"

const int Clock::s_nbDigit = 4;

Clock::Clock(int dataPin, int pixelPerSeg):
        m_dataPin(dataPin),
        m_pixelPerSeg(pixelPerSeg)
{
    m_strip = Adafruit_NeoPixel(
        m_pixelPerSeg * 7 * s_nbDigit,
        m_dataPin,
        NEO_GRB + NEO_KHZ800);
    m_strip.begin();

    for (uint8_t iter = 0; iter < s_nbDigit - 1; ++iter)
    {
        m_digits[iter] = new SevenSeg(iter * m_pixelPerSeg * 7, m_pixelPerSeg, m_strip);
        m_digits[iter]->set_color(50, 25, 25);
    }
}

Clock::~Clock()
{
    for (uint8_t iter = 0; iter < s_nbDigit - 1; ++iter)
        delete m_digits[iter];
}

void Clock::display(uint8_t hours, uint8_t minutes)
{
    uint16_t num = hours * 100 + minutes;
    for (uint8_t iter = s_nbDigit - 1; iter >= 0; --iter)
    {
        m_digits[iter]->display(SevenSeg::indexToChar(num % 10));
        num /= 10;
    }
    m_strip.show();
}
