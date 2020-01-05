/*
 * Nathan Bleuzen, 2018
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <NeoPixelBus.h>
extern NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip;

#include "Logger.hpp"

// Uncomment to use LED strip test mode: Displays a counter sounting up on the defined number of digits and dots
//#define USE_LED_TEST_MODE 1

const uint8_t nbSevenSeg = 4;
const uint8_t nbPixelPerSeg = 4;
const uint8_t nbSegPerSevenSeg = 7;
const uint8_t nbCenterDot = 1;
const uint8_t nbPixelPerDot = 4;

const RgbColor onColor = RgbColor(64, 64, 64);
const RgbColor offColor = RgbColor(0, 0, 0);

constexpr char * wifiSSID = "ssid";
constexpr char * wifiPassword = "password";
constexpr char * getTimeRequest = "http://api.timezonedb.com/v2.1/get-time-zone?key=API_KEY&format=json&by=zone&zone=Europe/Paris&fields=timestamp";

#endif // CONFIG_H
