/*
 * Nathan Bleuzen, 2018
 *
 * TODO list:
 * - Add display on 7seg of weather informations (numbers and colors/brightness)
 * - Add REST request on weather station
 * - Build weather station...
 * - Add color/brightness shifting depending on time of the day
 */

#include <ESP8266WiFi.h>
#include "config.h"
#include "Counter.hpp"

static void setup_wifi(void);

static const uint8_t nbTotalPixel = (nbSevenSeg * nbSegPerSevenSeg * nbPixelPerSeg) + (nbCenterDot * nbPixelPerDot);
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(nbTotalPixel); // Uses ESP8266 GPIO3 (RX on NodeMCU & co)

#ifndef TEST_MODE
#include "Clock.hpp"
Clock clock7; // A clock made of NeoPixel seven segments displays
#elif defined(TEST_COUNTER_MODE)
// A display made of NeoPixel seven segments displays and center dots
// When using more than 2 digits, increment minutes and hour parts at the same time
static Counter testCounter = Counter((nbSevenSeg > 2) ? 101 : 1);
#endif

void setup()
{
    logger.init(LOG_DEBUG);

    strip.Begin();
    strip.Show(); // Resets the strip to black

    setup_wifi();

#ifndef TEST_MODE
    clock7.init();
    clock7.display();
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

/********************/
/* HELPER FUNCTION */
/********************/
static void setup_wifi(void)
{
    Counter wifiInitCounter;
    wifiInitCounter.init();
    WiFi.begin(wifiSSID, wifiPassword); // Connect to the WiFi
    logger.log(LOG_DEBUG, "Connecting WiFi on %s", wifiSSID);
    while (WiFi.status() != WL_CONNECTED)
    {
        logger.log(LOG_DEBUG, "...");
        wifiInitCounter.update();
        delay(250);
    }
    logger.log(LOG_INFO, "WiFi connected @%s on %s", WiFi.localIP().toString().c_str(), wifiSSID);
}
