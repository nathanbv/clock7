/*
 * Nathan Bleuzen, 2018
 */

#ifndef DISPLAY7_HPP
#define DISPLAY7_HPP

#include <vector>

#include "DisplayElement.hpp"

class CenterDot;
class SevenSeg;

class Display7
{
public:
    Display7();
    ~Display7();
    void init(void);
    void reset(void);
    void set_color(RgbColor color);

private:
    std::vector<SevenSeg *>  m_digits;
    std::vector<CenterDot *> m_dots;
};

extern Display7 display7;

#endif // DISPLAY7_HPP
