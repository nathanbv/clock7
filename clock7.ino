/*
 * Nathan Bleuzen, 2018
 *
 * TODO list:
 * - 3D print 7seg display and assemble with LEDs
 * - Add ws2812b 7seg digit implementation
 * - Add display on 7seg of weather informations (numbers and colors/brightness)
 * - Add REST request on weather station
 * - Build weather station...
 * - Add color/brightness shifting depending on time of the day
 */

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <TimeLib.h>
#include <ArduinoJson.h>
#include "Clock.hpp"
#include "serialClock.hpp"

const char* wifiSSID = "ssid";
const char* wifiPassword = "password";
const char* getTimeRequest = "http://api.timezonedb.com/v2.1/get-time-zone?key=API_KEY&format=json&by=zone&zone=Europe/Paris&fields=timestamp";
static const size_t jsonBufferSize = JSON_OBJECT_SIZE(3) + 50;
static time_t prevTime = 0; // when the last digital clock was displayed
static Clock * clock;

static void setup_serial(void);
static void setup_wifi(void);
time_t get_local_time(void);

void setup()
{
    setup_serial();
    setup_wifi();

    setSyncProvider(get_local_time);
    setSyncInterval(300); // Sync time every 5min

    clock = new Clock(6, 4);
}

void loop()
{
    if (timeStatus() != timeNotSet)
    {
        if (now() != prevTime) // Update the display only if time has changed
        {
            prevTime = now();
            digital_clock_display();
        }
    }
}

/********************/
/* HELPER FUNCTIONS */
/********************/
static void setup_serial(void)
{
    Serial.begin(9600);
    while (!Serial)
    {
        delay(250);
    }
    Serial.println();
    Serial.println("Serial initialized");
}

static void setup_wifi(void)
{
    WiFi.begin(wifiSSID, wifiPassword); // Connect to the WiFi
    digitalWrite(LED_BUILTIN, LOW); // Turn error led on
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(250);
    }
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print("WiFi connected @");
    Serial.println(WiFi.localIP());
}

/**************************/
/* TIME PROVIDER FUNCTION */
/**************************/
time_t get_local_time(void)
{
    HTTPClient http;
    http.begin(getTimeRequest);
    const int err = http.GET();
    if (err < 0)
    {
        Serial.print("HTTP GET error: ");
        Serial.println(err);
        http.end();
        return 0UL;
    }

    DynamicJsonBuffer jsonBuffer(jsonBufferSize);
    const JsonObject& root = jsonBuffer.parseObject(http.getString());
    http.end();

    const char* status = root["status"];
    if (strcmp(status, "OK") == 0)
    {
        unsigned long timestamp = root["timestamp"].as<unsigned long>();
        const long diff = prevTime - timestamp;
        Serial.print("Time sync: clock is ");
        Serial.print((diff < 0) ? -1*diff : diff);
        Serial.println((diff < 0) ? "sec late" : "sec ahead");
        return timestamp;
    }
    else
    {
        const char* message = root["message"];
        Serial.print(status);
        Serial.print(" API error: ");
        Serial.println(message);
        return 0UL;
    }
}
