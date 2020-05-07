#include "Display7.hpp"

#include "config.h"
#include "CenterDot.hpp"
#include "SevenSeg.hpp"

// Unique intstance of Display7
Display7 display7;

Display7::Display7()
{ }

Display7::~Display7()
{
    for (SevenSeg * digit : m_digits)
        delete digit;
    m_dots.clear();
    for (CenterDot * dot : m_dots)
        delete dot;
    m_digits.clear();
}

void Display7::init()
{
    logger.log(LOG_DEBUG, "Display7::%s", __func__);

    // The display of the Clock7 requires 4 SevenSegment digits with 2 CenterDots in the middle
    if ((nbSevenSeg != 4) || (nbCenterDot != 2)) {
        logger.log(LOG_WARN, "Incorrect number of displays ! The full Clock7 requires 4 digits (%d) and 2 dots (%d)", nbSevenSeg, nbCenterDot);
        // Still allow the display to be initiliazed to test only a subset of the display
    }

    // If there is more than 2 SevenSeg digits, we need to account for the CenterDots
    const uint8_t nbSevenSegPerSide = (nbSevenSeg > 2) ? 2 : nbSevenSeg;
    // Digits are used for the minute part of the display
    for (uint8_t iter = 0; iter < nbSevenSegPerSide; ++iter)
        m_digits.push_back(new SevenSeg(iter * nbPixelPerSeg * nbSegPerSevenSeg));

    // Dots in the center, between minutes and hours
    uint8_t centerOffset = nbSevenSegPerSide * nbPixelPerSeg * nbSegPerSevenSeg;
    for (uint8_t iter = 0; iter < nbCenterDot; ++iter)
        m_dots.push_back(new CenterDot(centerOffset + (iter * nbPixelPerDot)));

    // Digits are used for the hour part of the display
    uint8_t hourPartOffset = centerOffset + (nbCenterDot * nbPixelPerDot);
    for (uint8_t iter = 0; iter < (nbSevenSeg - nbSevenSegPerSide); ++iter)
        m_digits.push_back(new SevenSeg(hourPartOffset + (iter * nbPixelPerSeg * nbSegPerSevenSeg)));

    // Set the default color
    set_color(onColor);
}

void Display7::reset(void)
{
    set_color(offColor);
    strip.Show();
}

// Sets the color on the whole display
void Display7::set_color(RgbColor color)
{
    for (SevenSeg * digit : m_digits)
        digit->set_color(color);
    for (CenterDot * dot : m_dots)
        dot->set_color(color);
}
