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
#include "IrRemoteHandler.hpp"
#include "Clock.hpp"
#include "Counter.hpp"

static const uint8_t nbTotalPixel = (nbSevenSeg * nbSegPerSevenSeg * nbPixelPerSeg) + (nbCenterDot * nbPixelPerDot);
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(nbTotalPixel); // Uses ESP8266 GPIO3 (RX on NodeMCU & co)

// Handler to receive infrared commands from a remote
static IrRemoteHandler irRemoteHandler;

// A clock made of NeoPixel seven segments displays
static Clock clock7;

// A display made of NeoPixel seven segments displays and center dots
// When using more than 2 digits, increment minutes and hour parts at the same time
static Counter testCounter = Counter((nbSevenSeg > 2) ? 101 : 1);

void setup()
{
    logger.init(LOG_DEBUG, 115200);

    strip.Begin();
    strip.Show(); // Resets the strip to black

#ifndef TEST_SET_TIME
    setup_wifi();
#endif

    irRemoteHandler.init();
    clock7.init();
    testCounter.init();
}

void loop()
{
    operatingMode previousMode = currentMode;
    irRemoteHandler.update();

    // Wakes up the clock when the sunrise comes
    if (clock7.is_sunrise())
        currentMode = CLOCK;
    // Turn of the clock if it's still displayed after the sunrise animation
    else if (currentMode == CLOCK && clock7.is_sunrise_over())
        currentMode = DISPLAY_OFF;

    if (previousMode != currentMode) {
        clock7.reset();
        testCounter.reset();
    }

    switch (currentMode) {
    case CLOCK:
        clock7.update();
        break;
    case TEST_COUNTER:
        testCounter.update();
        break;
    default:
        break;
    }

    // Delay the next loop by 125ms. Allows easier debugging in case something
    // goes wrong between 2 loops and does not impact much the time tracking.
    delay(125);
}
