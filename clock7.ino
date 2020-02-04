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

static void setup_wifi(void);

static const uint8_t nbTotalPixel = (nbSevenSeg * nbSegPerSevenSeg * nbPixelPerSeg) + (nbCenterDot * nbPixelPerDot);
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(nbTotalPixel); // Uses ESP8266 GPIO3 (RX on NodeMCU & co)

#ifndef TEST_MODE
#include "Clock.hpp"
Clock clock7; // A clock made of NeoPixel seven segments displays
#elif defined(TEST_COUNTER_MODE)
#include "TestDisplayCounter.hpp"
static TestDisplayCounter testCounter = TestDisplayCounter(); // A display made of NeoPixel seven segments displays and center dots
#endif

void setup()
{
    strip.Begin();
    strip.Show(); // Resets the strip to black

    logger.init(LOG_DEBUG);
    setup_wifi();

#ifndef TEST_MODE
    clock7.init();
    clock7.display();
#elif defined(TEST_COUNTER_MODE)
    logger.log(LOG_WARN, "TEST COUNTER MODE ENABLED");
    testCounter.begin();
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
    WiFi.begin(wifiSSID, wifiPassword); // Connect to the WiFi
    digitalWrite(LED_BUILTIN, LOW); // Turn error led on
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(250);
    }
    digitalWrite(LED_BUILTIN, HIGH);
    logger.log(LOG_INFO, "WiFi connected @%s", WiFi.localIP().toString().c_str());
}
