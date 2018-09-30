/*
 * Nathan Bleuzen, 2018
 */

#ifndef LOCALS_H
#define LOCALS_H

const char* wifiSSID = "ssid";
const char* wifiPassword = "password";
const char* getTimeRequest = "http://api.timezonedb.com/v2.1/get-time-zone?key=API_KEY&format=json&by=zone&zone=Europe/Paris&fields=timestamp";

const uint8_t stripDataPin = 12; // D6
const uint8_t nbSevenSegs = 4;
const uint8_t pixelPerSeg = 4;

#endif // LOCALS_H
