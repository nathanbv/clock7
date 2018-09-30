/*
 * Nathan Bleuzen, 2018
 *
 * Seven segments digits are defined by 7 bits representing the individual
 * segments in the following order (1 being the MSB in the table):
 * ⌈⎺2⎺⌉
 * 1   3
 * |-7-|
 * 6   4
 * ⌊⎽5⎽⌋
 */

#ifndef SEVENSEG_HPP
#define SEVENSEG_HPP

#include <Adafruit_NeoPixel.h>

extern Adafruit_NeoPixel strip;

class SevenSeg
{
public:
    SevenSeg(uint8_t stripOffset, uint8_t pixelPerSeg);
    ~SevenSeg();
    void set_color(uint8_t red, uint8_t green, uint8_t blue);
    void display(uint8_t segChar);

    static const uint8_t indexToChar(int indexChar) {
        static const uint8_t s_segCharTable[] = {
            0b1111110, // 0
            0b0011000, // 1
            0b0110111, // 2
            0b0111101, // 3
            0b1011001, // 4
            0b1101101, // 5
            0b1101111, // 6
            0b0111000, // 7
            0b1111111, // 8
            0b1111001, // 9
            0b1111011, // A
            0b1111111, // B, same as 8
            0b1100110, // C
            0b1111110, // D, same as 0
            0b1100111, // E
            0b1100011, // F
            0b0000001, // -
            0b0000000, // empty
        };
        if (indexChar >= (sizeof(s_segCharTable) / sizeof(s_segCharTable[0])))
            return 0b0000000; // empty
        return s_segCharTable[indexChar];
    };

private:
    const uint8_t m_stripOffset;
    const uint8_t m_pixelPerSeg;
    uint32_t m_color;
};

#endif // SEVENSEG_HPP
