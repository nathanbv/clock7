/*
 * Nathan Bleuzen, 2018
 */

#include <ESP8266WiFi.h>
#include "helpers.h"
#include "config.h"
#include "Counter.hpp"

void setup_wifi(void)
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
