/*
 * Nathan Bleuzen, 2018
 */

#ifndef DISPLAYELEMENT_HPP
#define DISPLAYELEMENT_HPP

#include <NeoPixelBus.h>

class DisplayElement
{
public:
    DisplayElement(uint8_t stripOffset): m_stripOffset(stripOffset) { }
    virtual ~DisplayElement() { };

    virtual void set_color(RgbColor color) = 0;
    virtual void set_color(uint8_t red, uint8_t green, uint8_t blue) = 0;
    virtual void display(uint8_t segChar) = 0;

protected:
    const uint8_t m_stripOffset;
    RgbColor m_color;
};

#endif // DISPLAYELEMENT_HPP
