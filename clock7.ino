/*
 * Nathan Bleuzen, 2018
 *
 * TODO list:
 * - 3D print 7seg display and assemble with LEDs
 * - Add display on 7seg of weather informations (numbers and colors/brightness)
 * - Add REST request on weather station
 * - Build weather station...
 * - Add color/brightness shifting depending on time of the day
 */

#include <ESP8266WiFi.h>

#include "Clock.hpp"
#include "config.h"
static const uint8_t nbTotalPixel = (nbSevenSeg * nbSegPerSevenSeg * nbPixelPerSeg) + (nbCenterDot * nbPixelPerDot);
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(nbTotalPixel); // Uses ESP8266 GPIO3 (RX on NodeMCU & co)
Clock clock7; // A clock made of NeoPixel seven segments displays

static void setup_wifi(void);

void setup()
{
    strip.Begin();
    strip.Show(); // Resets the strip to black

    logger.init(LOG_DEBUG);
    setup_wifi();

    clock7.init();
}

void loop()
{
    clock7.update();
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
