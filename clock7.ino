/*
 * Nathan Bleuzen, 2018
 *
 * TODO list:
 * - Add display on 7seg of weather informations (numbers and colors/brightness)
 * - Add REST request on weather station
 * - Build weather station...
 * - Add color/brightness shifting depending on time of the day
 */

#include "config.h"
#include "helpers.h"

static const uint8_t nbTotalPixel = (nbSevenSeg * nbSegPerSevenSeg * nbPixelPerSeg) + (nbCenterDot * nbPixelPerDot);
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(nbTotalPixel); // Uses ESP8266 GPIO3 (RX on NodeMCU & co)


#ifdef TEST_COUNTER_MODE
#include "Counter.hpp"
// A display made of NeoPixel seven segments displays and center dots
// When using more than 2 digits, increment minutes and hour parts at the same time
static Counter testCounter = Counter((nbSevenSeg > 2) ? 101 : 1);
#else
#include "Clock.hpp"
Clock clock7; // A clock made of NeoPixel seven segments displays
#endif

void setup()
{
    logger.init(LOG_DEBUG, 115200);

    strip.Begin();
    strip.Show(); // Resets the strip to black

    setup_wifi();

#ifndef TEST_MODE
    clock7.init();
#elif defined(TEST_COUNTER_MODE)
    logger.log(LOG_WARN, "TEST COUNTER MODE ENABLED");
    testCounter.init();
#endif
}

void loop()
{
#ifndef TEST_MODE
    clock7.update();
#elif defined(TEST_COUNTER_MODE)
    testCounter.update();
#endif
}
