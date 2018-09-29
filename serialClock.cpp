/*
 * Nathan Bleuzen, 2018
 * Serial clock display functions
 */

#include "serialClock.hpp"

void digital_clock_display(void)
{
    if (!Serial)
        return;
    // Digital clock display over Serial connection
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

static void print_double_digit(const int digits)
{
    // Prints leading 0
    if (digits < 10)
        Serial.print('0');
    Serial.print(digits);
}
