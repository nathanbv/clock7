/*
 * Nathan Bleuzen, 2018
 * Serial clock display functions
 */

#include <Arduino.h>
#include <TimeLib.h>

void digital_clock_display(void);
static void print_double_digit(const int digits);
