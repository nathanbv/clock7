/*
 * Nathan Bleuzen, 2018
 */

#include "TimeProvider.hpp"

#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <sstream>
#include <TimeLib.h>

#include "config.h"

using namespace std;

const size_t TimeProvider::m_jsonResponseSize = JSON_OBJECT_SIZE(3) + 40;

void TimeProvider::init(void)
{
    setSyncProvider(sync_server_time); // Set the function used to synchronize the time
    setSyncInterval(300); // Sync time every 5min
}

bool TimeProvider::isReady()
{
    return timeStatus() != timeNotSet;
}

time_t TimeProvider::get_time(void)
{
    return now();
}

// Returns the current time as a decimal representation with the form HHMM
uint16_t TimeProvider::get_decimal_time(void)
{
    return hour() * 100 + minute();
}

// Returns "HH:MM:SS DD.MM.YYYY"
const string TimeProvider::get_date(void)
{
    ostringstream date;
    date << to_double_digit(hour()) << ":";
    date << to_double_digit(minute()) << ":";
    date << to_double_digit(second()) << " ";
    date << to_double_digit(day()) << ".";
    date << to_double_digit(month()) << ".";
    date << year();
    return date.str();
}

const string TimeProvider::to_double_digit(const int digits)
{
    if (digits > 99 || digits < 0)
        logger.log(LOG_WARN, "Unexpected number (%d)", digits);

    ostringstream ret;
    // Add a leading 0
    if (digits < 10)
        ret << "0";
    ret << digits;
    return ret.str();
}

time_t TimeProvider::sync_server_time(void)
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

    // JSON string from the request should look like that:
    // { "status": "OK", "message": "", "timestamp": 1234567890 }
    DynamicJsonDocument doc(m_jsonResponseSize);
    deserializeJson(doc, http.getString());
    http.end();
    const char * status = doc["status"];
    if (strcmp(status, "OK") == 0)
    {
        logger.log(LOG_DEBUG, "Time synchronized from distant server");
        return doc["timestamp"];
    }
    else
    {
        const char * message = doc["message"];
        logger.log(LOG_INFO, "%s API error: %s", status, message);
        return 0UL;
    }
}