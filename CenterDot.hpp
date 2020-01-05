/*
 * Nathan Bleuzen, 2018
 */

#ifndef CENTERDOT_HPP
#define CENTERDOT_HPP

#include <NeoPixelBus.h>

class CenterDot
{
public:
    CenterDot(uint8_t stripOffset);
    ~CenterDot() { }

    void set_color(RgbColor color);
    void set_color(uint8_t red, uint8_t green, uint8_t blue) { set_color(RgbColor(red, green, blue)); }
    void display(bool state);

private:
    const uint8_t m_stripOffset;
    RgbColor m_color;
};

#endif // CENTERDOT_HPP
