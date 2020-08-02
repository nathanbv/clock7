/*
 * Nathan Bleuzen, 2018
 */

#include "Clock.hpp"
#include "config.h"

Clock::Clock():
        m_prevTime(0),
        m_timeProvider(),
        m_colorProvider()
{ }

Clock::~Clock()
{
    m_digits.clear();
    m_dots.clear();
}

void Clock::init()
{
    logger.log(LOG_DEBUG, "Clock::%s", __func__);
    // Initialize the most crucial part of a clock...
    m_timeProvider.init();

    // The Clock7 requires 4 SevenSegment digits with 2 CenterDots in the middle
    if ((nbSevenSeg != 4) || (nbCenterDot != 2)) {
        logger.log(LOG_ERR, "Incorrect number of displays ! The full Clock7 requires 4 digits (%d) and 2 dots (%d)", nbSevenSeg, nbCenterDot);
        m_digits.clear();
        m_dots.clear();
        return;
    }

    const uint8_t nbSevenSegPerSide = 2;
    // 2 digits are used for the minute part of the clock
    for (uint8_t iter = 0; iter < nbSevenSegPerSide; ++iter)
        m_digits.push_back(SevenSeg(iter * nbPixelPerSeg * nbSegPerSevenSeg));

    // 2 dots in the center, between minutes and hours
    uint8_t centerOffset = nbSevenSegPerSide * nbPixelPerSeg * nbSegPerSevenSeg;
    for (uint8_t iter = 0; iter < nbCenterDot; ++iter)
        m_dots.push_back(CenterDot(centerOffset + (iter * nbPixelPerDot)));

    // 2 digits are used for the hour part of the clock
    uint8_t hourPartOffset = centerOffset + (nbCenterDot * nbPixelPerDot);
    for (uint8_t iter = 0; iter < nbSevenSegPerSide; ++iter)
        m_digits.push_back(SevenSeg(hourPartOffset + (iter * nbPixelPerSeg * nbSegPerSevenSeg)));
}

void Clock::reset(void) {
    m_prevTime = 0;
    set_color(offColor);
    for (SevenSeg & digit : m_digits)
        digit.display();
    for (CenterDot & dot : m_dots)
        dot.display(false);
    strip.Show();
}

// Sets the color on the whole clock
void Clock::set_color(RgbColor color)
{
    for (SevenSeg & digit : m_digits)
        digit.set_color(color);
    for (CenterDot & dot : m_dots)
        dot.set_color(color);
}

bool Clock::is_sunrise(void)
{
    return m_timeProvider.is_sunrise();
}

void Clock::update(void)
{
    if (!m_timeProvider.is_ready())
        return;

    // When the clock is not yet displayed, force the initialization of the display
    bool forceDisplay = false;
    if (m_prevTime == 0) {
        forceDisplay = true;
        set_color(onColor); // Set the default color
    }
    // Update the display only if time has changed
    else if (m_timeProvider.get_time() == m_prevTime)
        return;

    m_prevTime = m_timeProvider.get_time(); // Get the current time accurate to the second
    // If the sun is raising get the appropriate color
    if (is_sunrise()) {
        RgbColor colorTmp = m_colorProvider.getSunriseColor(m_timeProvider.get_time());
        set_color(colorTmp);
        //logger.log(LOG_DEBUG, "Sunrise color: R%3d G%3d B%3d", colorTmp.R, colorTmp.G, colorTmp.B);
    }
    // Otherwise use default one
    else {
        m_colorProvider.resetSunriseColor();
        set_color(onColor);
    }

    display(forceDisplay); // Print the current time on the LED seven segments
}

void Clock::display(bool forceDisplay)
{
    // Get the time as a decimal number with the form HHMM
    uint16_t timeDesc = m_timeProvider.get_decimal_time();
    for (SevenSeg & digit : m_digits)
    {
        digit.display(SevenSeg::indexToChar(timeDesc % 10));
        timeDesc /= 10;
    }
    // Light-up center dots
    for (CenterDot & dot : m_dots)
        dot.display(true);

    strip.Show();

    // Log time to serial every minute
    if ((m_prevTime % 60) == 0 || forceDisplay)
        logger.log(LOG_INFO, "%s", m_timeProvider.get_date_str().c_str());
}
