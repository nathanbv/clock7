/*
 * Nathan Bleuzen, 2018
 *
 * Seven segments digits are defined by 7 bits representing the individual
 * segments in the following order (1 being the MSB in the table):
 * ⌈⎺5⎺⌉
 * 4   6
 * |-7-|
 * 3   1
 * ⌊⎽2⎽⌋
 */

#ifndef SEVENSEG_HPP
#define SEVENSEG_HPP

#include <NeoPixelBus.h>

class SevenSeg
{
public:
    SevenSeg(uint8_t stripOffset);
    ~SevenSeg() { }

    void set_color(RgbColor color);
    void set_color(uint8_t red, uint8_t green, uint8_t blue) { set_color(RgbColor(red, green, blue)); }
    void display(uint8_t segChar);

    static const uint8_t indexToChar(int indexChar) {
        static const uint8_t s_segCharTable[] = {
            0b1111110, // '0'
            0b1000010, // '1'
            0b0110111, // '2'
            0b1100111, // '3'
            0b1001011, // '4'
            0b1101101, // '5'
            0b1111101, // '6'
            0b1000110, // '7'
            0b1111111, // '8'
            0b1101111, // '9'
            0b1011111, // 'A'
            0b1111111, // 'B', same as '8'
            0b0111100, // 'C'
            0b1111110, // 'D', same as '0'
            0b0111101, // 'E'
            0b0011101, // 'F'
            0b0000001, // '-'
            0b0000000, // empty
        };
        if (indexChar >= (sizeof(s_segCharTable) / sizeof(s_segCharTable[0])))
            return 0b0000000; // empty
        return s_segCharTable[indexChar];
    };

private:
    const uint8_t m_stripOffset;
    RgbColor m_color;
};

#endif // SEVENSEG_HPP
