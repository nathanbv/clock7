/*
 * Nathan Bleuzen, 2018
 *
 * Seven segments digits are defined by 7 bits representing the individual
 * segments in the following order (0 being the MSB in the table):
 * ⌈⎺4⎺⌉
 * 3   5
 * |-6-|
 * 2   0
 * ⌊⎽1⎽⌋
 */

#ifndef SEVENSEG_HPP
#define SEVENSEG_HPP

#include "DisplayElement.hpp"

class SevenSeg: public DisplayElement
{
public:
    SevenSeg(uint8_t stripOffset);

    void set_color(RgbColor color);
    void set_color(uint8_t red, uint8_t green, uint8_t blue) { set_color(RgbColor(red, green, blue)); }
    void display(uint8_t segChar);

    static uint8_t indexToChar(int indexChar) {
        static const uint8_t badCharac = 0b0000100; // '‾', value used for not supported characters
        static const uint8_t segCharTable[] = {
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
            0b1111001, // 'B'
            0b0111100, // 'C'
            0b1110011, // 'D'
            0b0111101, // 'E'
            0b0011101, // 'F'
            0b1111100, // 'G'
            0b1011011, // 'H'
            0b0011000, // 'I'
            0b1110010, // 'J'
            badCharac, // 'K', not supported
            0b0111000, // 'L'
            badCharac, // 'M', not supported
            0b1010001, // 'N'
            0b1110001, // 'O'
            0b0011111, // 'P'
            0b1001111, // 'Q'
            0b0010001, // 'R'
            0b1101101, // 'S', same as '5'
            0b0111001, // 'T'
            0b1111010, // 'U'
            badCharac, // 'V', not supported
            badCharac, // 'W', not supported
            badCharac, // 'X', not supported
            0b1101011, // 'Y'
            badCharac, // 'Z', not supported
            0b0000000, // ' ', empty
            0b0001111, // '*' also used for '°'
            0b0000001, // '-'
            0b0100000, // '_'
            badCharac, // '‾', value use for not supported characters
        };
        static const uint8_t tableSize = sizeof(segCharTable) / sizeof(segCharTable[0]);
        static const uint8_t numericOffset = '9' - '0' + 1;
        static const uint8_t alphanumOffset = numericOffset + 'Z' - 'A' + 1;

        // If it does not correspond to an index of the table,
        // try to parse it from supported characters.
        if (indexChar >= tableSize) {
            if (('0' <= indexChar) && (indexChar <= '9'))
                indexChar = indexChar - '0';
            else if (('A' <= indexChar) && (indexChar <= 'Z'))
                indexChar = numericOffset + indexChar - 'A';
            else if (('a' <= indexChar) && (indexChar <= 'z'))
                indexChar = numericOffset + indexChar - 'a' ;
            else if (indexChar == ' ')
                indexChar = alphanumOffset;
            else if (indexChar == '*')
                indexChar = alphanumOffset + 1;
            else if (indexChar == '-')
                indexChar = alphanumOffset + 2;
            else if (indexChar == '_')
                indexChar = alphanumOffset + 3;
            else
                indexChar = tableSize - 1; // badCharac
        }
        return segCharTable[indexChar];
    };
};

#endif // SEVENSEG_HPP
