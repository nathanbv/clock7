/*
 * Nathan Bleuzen, 2018
 */

#include "TimeProvider.hpp"

#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <TimeLib.h>

#include "config.h"

using namespace std;

static const size_t jsonBufferSize = JSON_OBJECT_SIZE(3) + 50;

void TimeProvider::init(void)
{
    setSyncProvider(get_local_time); // Set the function used to synchronize the time
    setSyncInterval(300); // Sync time every 5min
}

bool TimeProvider::isReady()
{
    return timeStatus() != timeNotSet;
}

time_t TimeProvider::now(void)
{
    return now();
}

// Returns the current time as a decimal representation with the form HHMM
uint16_t TimeProvider::get_decimal_time(void)
{
    return hour() * 100 + minute();
}

// Returns "HH:MM:SS DD.MM.YYYY"
const string & TimeProvider::get_date(void)
{
    string date;
/*
    date << get_double_digit(hour());
    date << ":";
    date << get_double_digit(minute());
    date << ":";
    date << get_double_digit(second());
    date << " ";
    date << get_double_digit(day());
    date << ".";
    date << get_double_digit(month());
    date << ".";
    date << year();
*/
    return date;
}

const string & TimeProvider::get_double_digit(const int digits)
{

    if (digits > 99 || digits < 0)
        logger.log(LOG_WARN, "Unexpected number (%d)", digits);

    string ret;
/*
    // Add a leading 0
    if (digits < 10)
        ret << '0';
    ret << digits;
*/
    return ret;
}

time_t TimeProvider::get_local_time(void)
{
    HTTPClient http;
    http.begin(getTimeRequest);
    const int err = http.GET();
    if (err < 0)
    {
        logger.log(LOG_ERR, "HTTP PUT error: %s", err);
        http.end();
        return 0UL;
    }
/*
//DynamicJsonBuffer is a class from ArduinoJson 5. Please see arduinojson.org/upgrade to learn how to upgrade your program to ArduinoJson version 6
    DynamicJsonBuffer jsonBuffer(jsonBufferSize);
    const JsonObject & root = jsonBuffer.parseObject(http.getString());
    http.end();

    const char * status = root["status"];
    if (strcmp(status, "OK") == 0)
    {
        uint32_t timestamp = root["timestamp"].as<uint32_t>();
        const int32_t diff = prevTime - timestamp;
        logger.log(LOG_INFO, "Time sync: clock is %d%s",
            (diff < 0) ? -1 * diff : diff,
            (diff < 0) ? "sec late" : "sec ahead");
        return timestamp;
    }
    else
    {
        const char * message = root["message"];
        logger.log(LOG_INFO, "%s API error: %s", status, message);
        return 0UL;
    }
*/
}