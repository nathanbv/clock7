/*
 * Nathan Bleuzen, 2018
 */

#include "Clock.hpp"

Clock::Clock(uint8_t nbDigit, uint8_t pixelPerSeg):
        m_nbDigit(nbDigit)
{
    for (uint8_t iter = 0; iter < m_nbDigit; ++iter)
        m_digits[iter] = new SevenSeg(iter * pixelPerSeg * 7, pixelPerSeg);
}

Clock::~Clock()
{
    for (uint8_t iter = 0; iter < m_nbDigit; ++iter)
        delete m_digits[iter];
}

void Clock::begin(void)
{
    for (uint8_t iter = 0; iter < m_nbDigit; ++iter)
        m_digits[iter]->set_color(50, 25, 25);
}

void Clock::display(uint8_t hours, uint8_t minutes)
{
    uint16_t timeDesc = hours * 100 + minutes;
    for (int8_t iter = m_nbDigit - 1; iter >= 0; --iter)
    {
        m_digits[iter]->display(SevenSeg::indexToChar(timeDesc % 10));
        timeDesc /= 10;
    }
    strip.Show();
}
