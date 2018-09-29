#include <Adafruit_NeoPixel.h>

class SevenSeg
{
public:
    SevenSeg(uint8_t stripOffset, uint8_t pixelPerSeg, Adafruit_NeoPixel & strip);
    ~SevenSeg();
    void set_color(uint8_t red, uint8_t green, uint8_t blue);
    void display(uint8_t value);

private:
    const uint8_t m_stripOffset;
    const uint8_t m_pixelPerSeg;
    Adafruit_NeoPixel & m_strip;
    uint32_t m_color;

    static const uint8_t m_segCharSize = 16;
    static const uint8_t m_segChar[m_segCharSize];
};