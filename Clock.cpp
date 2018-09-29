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

    for (uint8_t it = 0; it < s_nbDigit - 1; ++it)
    {
        m_digits[it] = new SevenSeg(it * m_pixelPerSeg * 7, m_pixelPerSeg, m_strip);
        m_digits[it]->set_color(50, 25, 25);
    }
}

Clock::~Clock()
{
    for (uint8_t it = 0; it < s_nbDigit - 1; ++it)
        delete m_digits[it];
}

void Clock::display(uint8_t hours, uint8_t minutes)
{
    uint16_t num = hours * 100 + minutes;
    for (uint8_t i = s_nbDigit - 1; i >= 0; --i)
    {
        m_digits[i]->display(num % 10);
        num /= 10;
    }
    m_strip.show();
}
