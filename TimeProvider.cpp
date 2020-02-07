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

const size_t TimeProvider::s_jsonResponseSize = JSON_OBJECT_SIZE(3) + 40;

// Sunrise starts at 8:01 every morning and ends at 9:00
static const time_t sunriseBeginning = hoursToTime_t(8) + minutesToTime_t(1);
static const time_t sunriseEnd       = hoursToTime_t(9) + minutesToTime_t(0);

void TimeProvider::init(void)
{
#ifdef TEST_SET_TIME
    setTime(SET_TIME_HOUR, SET_TIME_MINUTE, 0 /* sec */, 1 /* day */, 1 /* mnth */, 2000 /* yr */);
    return;
#endif

    setSyncProvider(sync_server_time); // Set the function used to synchronize the time
    setSyncInterval(300);              // Sync time every 5 minutes
}

bool TimeProvider::is_ready()
{
    return timeStatus() != timeNotSet;
}

// Returns the Epoch time, elapsed time since Jan 1 1970 in second
time_t TimeProvider::get_time(void)
{
    return now();
}

// Returns the current time as a decimal representation with the form HHMM
uint16_t TimeProvider::get_decimal_time(void)
{
    return hour() * 100 + minute();
}

const string TimeProvider::get_date(void)
{
    return get_date(now());
}

// Returns "HH:MM:SS DD.MM.YYYY"
const string TimeProvider::get_date(time_t fromTime)
{
    ostringstream date;
    date << to_double_digit(hour(fromTime)) << ":";
    date << to_double_digit(minute(fromTime)) << ":";
    date << to_double_digit(second(fromTime)) << " ";
    date << to_double_digit(day(fromTime)) << ".";
    date << to_double_digit(month(fromTime)) << ".";
    date << year(fromTime);
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

const bool TimeProvider::is_sunrise(void)
{
    time_t timeNow = now();
    time_t todaysSunriseBeginning = previousMidnight(timeNow) + sunriseBeginning;
    time_t todaysSunriseEnd =       previousMidnight(timeNow) + sunriseEnd;
    logger.log(LOG_DEBUG, "Today's sunrise starts at %s and ends at %s", get_date(todaysSunriseBeginning).c_str(), get_date(todaysSunriseEnd).c_str());
    return ((todaysSunriseBeginning < timeNow) && (timeNow < todaysSunriseEnd));
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
    DynamicJsonDocument doc(s_jsonResponseSize);
    deserializeJson(doc, http.getString());
    http.end();
    const char *status = doc["status"];
    if (strcmp(status, "OK") == 0)
    {
        logger.log(LOG_DEBUG, "Time synchronized from distant server");
        return doc["timestamp"];
    }
    else
    {
        const char *message = doc["message"];
        logger.log(LOG_INFO, "%s API error: %s", status, message);
        return 0UL;
    }
}
