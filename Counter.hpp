/*
 * Nathan Bleuzen, 2018
 */

#ifndef COUNTER_HPP
#define COUNTER_HPP

#include <vector>

#include "DisplayElement.hpp"

class CenterDot;
class SevenSeg;

class Counter
{
public:
    Counter(uint8_t inc);
    Counter();
    ~Counter();
    void init(void);
    void reset(void);
    void update(void);

private:
    void set_color(RgbColor color);
    void updateCounter(void);
    void display(void);

    // Increment the count, depends on how many SevenSegs are used
    const uint8_t m_inc;
    uint16_t m_count; // Count to display
    unsigned long m_prevTime; // Last timestamp at which the display was updated
    unsigned long m_interTime; // Time interval between two updates of the display
    std::vector<SevenSeg *>  m_digits;
    std::vector<CenterDot *> m_dots;

    static const uint16_t s_updatePeriodInMSec;
};

#endif // COUNTER_HPP
