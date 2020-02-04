/*
 * Nathan Bleuzen, 2018
 */

#ifndef TESTDISPLAYCOUNTER_HPP
#define TESTDISPLAYCOUNTER_HPP

#include "SevenSeg.hpp"
#include "CenterDot.hpp"
#include <vector>

class TestDisplayCounter
{
public:
    TestDisplayCounter();
    ~TestDisplayCounter();
    void begin(void);
    void update(void);

private:
    void updateCounter(void);
    void display(uint16_t num);

    // Increment the count, depends on ho many SevenSegs are under test
    // When testing more than 2 digits, increment minutes and hour parts at the same time
    const uint8_t m_inc;
    uint16_t m_count; // Count to display
    time_t m_prevTime; // Last timestamp at which the display was updated
    time_t m_interTime; // Time interval between two updates of the display
    std::vector<SevenSeg> m_digits;
    std::vector<CenterDot> m_dots;
};

#endif // TESTDISPLAYCOUNTER_HPP
