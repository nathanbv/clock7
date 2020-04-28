/*
 * Nathan Bleuzen, 2018
 */

#include "Counter.hpp"
#include "config.h"

using namespace std;

const uint16_t Counter::s_updatePeriodInMSec = 1000; // Count up every second

Counter::Counter(uint8_t inc):
        m_inc(inc),
        m_count(0),
        m_prevTime(0),
        m_interTime(s_updatePeriodInMSec)
{ }

Counter::Counter():
        m_inc(1),
        m_count(0),
        m_prevTime(0),
        m_interTime(s_updatePeriodInMSec)
{ }

Counter::~Counter()
{
    m_digits.clear();
    m_dots.clear();
}

void Counter::init(void)
{
    // If there is more than 2 SevenSeg digits, we need to account for the CenterDots
    const uint8_t nbSevenSegPerSide = (nbSevenSeg > 2) ? 2 : nbSevenSeg;

    // Minute part of the clock
    for (uint8_t iter = 0; iter < nbSevenSegPerSide; ++iter)
        m_digits.push_back(SevenSeg(iter * nbPixelPerSeg * nbSegPerSevenSeg));

    // Dots in the center, between minutes and hours
    uint8_t centerOffset = nbSevenSegPerSide * nbPixelPerSeg * nbSegPerSevenSeg;
    for (uint8_t iter = 0; iter < nbCenterDot; ++iter)
        m_dots.push_back(CenterDot(centerOffset + (iter * nbPixelPerDot)));

    // Hour part of the clock
    uint8_t hourPartOffset = centerOffset + (nbCenterDot * nbPixelPerDot);
    for (uint8_t iter = 0; iter < (nbSevenSeg - nbSevenSegPerSide); ++iter)
        m_digits.push_back(SevenSeg(hourPartOffset + (iter * nbPixelPerSeg * nbSegPerSevenSeg)));

    // Set the default color
    set_color(onColor);
}

void Counter::reset(void) {
    m_count = 0;
    m_prevTime = 0;
    set_color(offColor);
    strip.Show();
}

// Sets the color on the whole display
void Counter::set_color(RgbColor color)
{
    for (SevenSeg & digit : m_digits)
        digit.set_color(color);
    for (CenterDot & dot : m_dots)
        dot.set_color(color);
}

void Counter::update(void)
{
    // Print the initial state of the counter i.e. 0
    if (m_prevTime == 0)
    {
        m_prevTime = millis();
        display();
    }
    // Update the display every second
    else if (millis() >= (m_prevTime + m_interTime))
    {
        m_prevTime = millis();
        updateCounter();
        display(); // Print countup on the digits
    }
}

void Counter::updateCounter(void)
{
    m_count += m_inc;
    if (m_count >= pow(10, nbSevenSeg))
        m_count = 0;
}

void Counter::display(void)
{
    uint16_t num = m_count;
    for (SevenSeg & digit : m_digits)
    {
        digit.display(SevenSeg::indexToChar(num % 10));
        num /= 10;
    }
    for (CenterDot & dot : m_dots)
    {
        // Enable center dots on even numbers
        dot.display((m_count % 2) ? false : true);
    }
    strip.Show();
    logger.log(LOG_INFO, "%04d", m_count);
}
