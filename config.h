/*
 * Nathan Bleuzen, 2018
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <NeoPixelBus.h>
extern NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip;

#include "Logger.hpp"

// TEST_COUNTER_MODE: Displays a counter counting up on the defined number of digits
//#define TEST_COUNTER_MODE 1
// TEST_SET_TIME: Sets the clock time to a specific time
//#define TEST_SET_TIME 1
//#define SET_TIME_HOUR 7
//#define SET_TIME_MINUTE 59

const uint8_t nbSevenSeg = 4;
const uint8_t nbPixelPerSeg = 4;
const uint8_t nbSegPerSevenSeg = 7;
const uint8_t nbCenterDot = 2;
const uint8_t nbPixelPerDot = 4;

const RgbColor onColor = RgbColor(64, 64, 64);
const RgbColor offColor = RgbColor(0, 0, 0);

constexpr char * wifiSSID = "ssid";
constexpr char * wifiPassword = "password";
constexpr char * getTimeRequest = "http://api.timezonedb.com/v2.1/get-time-zone?key=API_KEY&format=json&by=zone&zone=Europe/Paris&fields=timestamp";

#endif // CONFIG_H
