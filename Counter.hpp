/*
 * Nathan Bleuzen, 2018
 */

#ifndef COUNTER_HPP
#define COUNTER_HPP

#include "SevenSeg.hpp"
#include "CenterDot.hpp"
#include <vector>

class Counter
{
public:
    Counter(uint8_t inc);
    Counter();
    ~Counter();
    void init(void);
    void update(void);

private:
    void updateCounter(void);
    void display(uint16_t num);

    // Increment the count, depends on how many SevenSegs are used
    const uint8_t m_inc;
    uint16_t m_count; // Count to display
    time_t m_prevTime; // Last timestamp at which the display was updated
    time_t m_interTime; // Time interval between two updates of the display
    std::vector<SevenSeg> m_digits;
    std::vector<CenterDot> m_dots;

    static const uint16_t s_delayCounterMs;
};

#endif // COUNTER_HPP
