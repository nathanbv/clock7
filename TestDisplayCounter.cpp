/*
 * Nathan Bleuzen, 2018
 */

#include "TestDisplayCounter.hpp"
#include "config.h"

using namespace std;

#define DELAY_COUNTER_MS 2000

TestDisplayCounter::TestDisplayCounter():
        m_inc((nbSevenSeg > 2) ? 101 : 1),
        m_count(0),
        m_prevTime(0),
        m_interTime(DELAY_COUNTER_MS)
{ }

TestDisplayCounter::~TestDisplayCounter()
{
    m_digits.clear();
    m_dots.clear();
}

void TestDisplayCounter::begin(void)
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

    // Set the default color to a low bright white-ish
    for (SevenSeg & digit : m_digits)
        digit.set_color(onColor);
    for (CenterDot & dot : m_dots)
        dot.set_color(onColor);
}

void TestDisplayCounter::update(void)
{
    if (millis() >= (m_prevTime + m_interTime)) // Update the display every second
    {
        m_prevTime = millis();
        updateCounter();
        logger.log(LOG_INFO, "%04d", m_count);
        display(m_count); // Print countup on the digits
    }
}

void TestDisplayCounter::updateCounter(void)
{
    m_count += m_inc;
    if (m_count >= pow(10, nbSevenSeg))
        m_count = 0;
}

void TestDisplayCounter::display(uint16_t num)
{
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
}
