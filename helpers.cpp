/*
 * Nathan Bleuzen, 2018
 */

#include "helpers.h"

#include <ESP8266WiFi.h>

#include "config.h"
#include "Counter.hpp"

void setup_wifi(void)
{
    Counter wifiInitCounter;
    wifiInitCounter.init();
    WiFi.begin(wifiSSID, wifiPassword); // Connect to the WiFi
    logger.log(LOG_DEBUG, "Connecting WiFi on %s", wifiSSID.c_str());
    while (WiFi.status() != WL_CONNECTED)
    {
        wifiInitCounter.update();
        logger.log(LOG_DEBUG, "....");
        delay(250);
    }
    wifiInitCounter.reset();
    logger.log(LOG_INFO, "WiFi connected @%s on %s", WiFi.localIP().toString().c_str(), wifiSSID.c_str());
}

bool is_wifi_connected(void)
{
    return (WiFi.status() == WL_CONNECTED);
}
