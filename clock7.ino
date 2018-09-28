#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <TimeLib.h>
#include <ArduinoJson.h>

const char* wifiSSID = "ssid";
const char* wifiPassword = "password";
const char* restRequest = "http://api.timezonedb.com/v2.1/get-time-zone?key=API_KEY&format=json&by=zone&zone=Europe/Paris&fields=timestamp";
const size_t jsonBufferSize = JSON_OBJECT_SIZE(3) + 50;
time_t prevTime = 0; // when the last digital clock was displayed

void setup_serial(void);
void setup_wifi(void);
time_t get_local_time(void);
void digital_clock_display(void);
void print_double_digit(const int digits);

void setup()
{
    setup_serial();
    setup_wifi();

    setSyncProvider(get_local_time);
    setSyncInterval(900); // TODO: change to larger value
}

void loop()
{
    if (timeStatus() != timeNotSet)
    {
        if (now() != prevTime) //update the display only if time has changed
        {
            prevTime = now();
            digital_clock_display();
        }
    }
}

/********************/
/* HELPER FUNCTIONS */
/********************/
void setup_serial(void)
{
    Serial.begin(9600);
    while (!Serial)
    {
        delay(250);
    }
    Serial.println();
    Serial.println("Serial initialized");
}

void setup_wifi(void)
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
    http.begin(restRequest);
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
        long diff = prevTime - timestamp;
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

/*********************/
/* DISPLAY FUNCTIONS */
/*********************/
void digital_clock_display(void)
{
    // digital clock display of the time
    print_double_digit(hour());
    Serial.print(":");
    print_double_digit(minute());
    Serial.print(":");
    print_double_digit(second());
    Serial.print(" ");
    print_double_digit(day());
    Serial.print(".");
    print_double_digit(month());
    Serial.print(".");
    Serial.print(year());
    Serial.println();
}

void print_double_digit(const int digits)
{
    // prints leading 0
    if (digits < 10)
        Serial.print('0');
    Serial.print(digits);
}
