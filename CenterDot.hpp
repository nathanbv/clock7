/*
 * Nathan Bleuzen, 2018
 */

#ifndef CENTERDOT_HPP
#define CENTERDOT_HPP

#include "DisplayElement.hpp"

class CenterDot: public DisplayElement
{
public:
    CenterDot(uint8_t stripOffset);
    ~CenterDot() { }

    void set_color(RgbColor color);
    void set_color(uint8_t red, uint8_t green, uint8_t blue);
    void display(uint8_t segchar);
};

#endif // CENTERDOT_HPP
