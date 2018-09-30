/*
 * Nathan Bleuzen, 2018
 */

#ifndef CLOCK_HPP
#define CLOCK_HPP

#include "SevenSeg.hpp"

extern Adafruit_NeoPixel strip;

class Clock
{
public:
    Clock(uint8_t nbDigit, uint8_t pixelPerSeg);
    ~Clock();
    void begin(void);
    void display(uint8_t hours, uint8_t minutes);

private:
    const uint8_t m_nbDigit;
    SevenSeg * m_digits[4];
};

#endif // CLOCK_HPP
