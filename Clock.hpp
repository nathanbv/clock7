/*
 * Nathan Bleuzen, 2018
 */

#ifndef CLOCK_HPP
#define CLOCK_HPP

#include "CenterDot.hpp"
#include "SevenSeg.hpp"
#include "ColorProvider.hpp"
#include "TimeProvider.hpp"
#include <vector>

class Clock
{
public:
    Clock();
    ~Clock();
    void init(void);
    void update(void);
    void display(void);

private:
    void set_color(RgbColor color);

    time_t m_prevTime;
    TimeProvider m_timeProvider;
    ColorProvider m_colorProvider;
    std::vector<SevenSeg> m_digits;
    std::vector<CenterDot> m_dots;
};

#endif // CLOCK_HPP
