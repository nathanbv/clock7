/*
 * Nathan Bleuzen, 2018
 */

#include <Adafruit_NeoPixel.h>
#include "SevenSeg.hpp"

class Clock
{
public:
    Clock(int dataPin, int pixelPerSeg);
    ~Clock();
    void display(uint8_t hours, uint8_t minutes);

private:
    const int m_dataPin;
    const int m_pixelPerSeg;
    Adafruit_NeoPixel m_strip;
    SevenSeg * m_digits[4];

    static const int s_nbDigit;
};