/*
 * Nathan Bleuzen, 2018
 * Serial clock display functions
 */

#ifndef SERIALCLOCK_HPP
#define SERIALCLOCK_HPP

#include <Arduino.h>
#include <TimeLib.h>

void digital_clock_display(void);
static void print_double_digit(const int digits);

#endif // SERIALCLOCK_HPP
