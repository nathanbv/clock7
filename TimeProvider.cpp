/*
 * Nathan Bleuzen, 2018
 */

#include "TimeProvider.hpp"

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <sstream>
#include <TimeLib.h>

#include "helpers.h"

// Fix errors in macros from TimeLib.h v1.6
#undef  minutesToTime_t
#define minutesToTime_t(M) ((M) * SECS_PER_MIN)
#undef  hoursToTime_t
#define hoursToTime_t(H)   ((H) * SECS_PER_HOUR)
#undef  daysToTime_t
#define daysToTime_t(D)    ((D) * SECS_PER_DAY)
#undef  weeksToTime_t
#define weeksToTime_t(W)   ((W) * SECS_PER_WEEK)

#include "config.h"

using namespace std;

const size_t TimeProvider::s_jsonResponseSize = JSON_OBJECT_SIZE(3) + 40;
const time_t TimeProvider::s_timeSyncInterval = 5 * 60; // Sync time every 5 minutes

// Sunrise starts at 7:50 every morning and ends 10 minutes later
static const time_t sunriseBeginning = hoursToTime_t(7) + minutesToTime_t(50);
static const time_t sunriseEnd       = sunriseBeginning + minutesToTime_t(10);

void TimeProvider::init(void)
{
    logger.log(LOG_DEBUG, "TimeProvider::%s sunrise is from %s to %s", __func__,
            get_time_str(sunriseBeginning).c_str(), get_time_str(sunriseEnd).c_str());
#ifdef TEST_SET_TIME
    setTime(SET_TIME_HOUR, SET_TIME_MINUTE, 0 /* sec */, 1 /* day */, 1 /* mnth */, 2000 /* yr */);
    return;
#endif

    setSyncProvider(sync_server_time); // Set the function used to synchronize the time
    setSyncInterval(s_timeSyncInterval); // Must be done after setting the provider function
}

bool TimeProvider::is_ready()
{
    // Allow the time to be used even when not properly synced when:
    // timeStatus() == timeNeedsSync
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

// Returns "HH:MM:SS"
string TimeProvider::get_time_str(time_t fromTime)
{
    ostringstream time;
    time << to_double_digit(hour(fromTime)) << ":";
    time << to_double_digit(minute(fromTime)) << ":";
    time << to_double_digit(second(fromTime));
    return time.str();
}

const string TimeProvider::get_date_str(void)
{
    return get_date_str(now());
}

// Returns "HH:MM:SS DD.MM.YYYY"
string TimeProvider::get_date_str(time_t fromTime)
{
    ostringstream date;
    date << get_time_str(fromTime) << " ";
    date << to_double_digit(day(fromTime)) << ".";
    date << to_double_digit(month(fromTime)) << ".";
    date << year(fromTime);
    return date.str();
}

string TimeProvider::to_double_digit(const int digits)
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

bool TimeProvider::is_sunrise(void)
{
    time_t timeNow = now();
    time_t todaysSunriseBeginning = previousMidnight(timeNow) + sunriseBeginning;
    time_t todaysSunriseEnd =       previousMidnight(timeNow) + sunriseEnd;
    bool isWeekEnd = (dayOfWeek(timeNow) == 1 /* Sunday */) || (dayOfWeek(timeNow) == 7 /* Saturday */);
    return (!isWeekEnd && (todaysSunriseBeginning < timeNow) && (timeNow < todaysSunriseEnd));
}

time_t TimeProvider::sync_server_time(void)
{
    // Hack to be able to call now() while syncing the time
    setSyncInterval(s_timeSyncInterval);
    logger.log(LOG_DEBUG, "%s @%s", __func__, TimeProvider::get_date_str(now()).c_str());

    if (!is_wifi_connected())
    {
        logger.log(LOG_ERR, "%s: WiFi is not connected!", __func__);
        return 0;
    }

    WiFiClient wifiClient;
    HTTPClient httpClientRequest;
    if (!httpClientRequest.begin(wifiClient, getTimeRequest))
    {
        logger.log(LOG_ERR, "%s: Unable to connect using HTTP!", __func__);
        return 0;
    }

    const int httpRetCode = httpClientRequest.GET();
    if (httpRetCode < 0)
    {
        logger.log(LOG_ERR, "%s: HTTP GET error: [%d] %s", __func__, httpRetCode, httpClientRequest.errorToString(httpRetCode).c_str());
        httpClientRequest.end();
        return 0;
    }

    // JSON string from the request should look like that:
    // { "status": "OK", "message": "", "timestamp": 1234567890 }
    DynamicJsonDocument doc(s_jsonResponseSize);
    deserializeJson(doc, httpClientRequest.getString());
    httpClientRequest.end();
    const char * status = doc["status"];
    if (strcmp(status, "OK") == 0)
    {
        const time_t syncTime = doc["timestamp"];
        const time_t currentTime = now();
        const time_t timeDrift = currentTime - syncTime;
        logger.log(LOG_DEBUG, "Time synchronized from distant server with %ld sec drift (internal clock is %s)",
                timeDrift,
                (timeDrift == 0) ? "ok" : ((timeDrift < 0) ? "too slow" : "too fast"));
        return syncTime;
    }
    else
    {
        const char * message = doc["message"];
        logger.log(LOG_ERR, "%s: %s API error: %s", __func__, status, message);
        return 0;
    }
}
