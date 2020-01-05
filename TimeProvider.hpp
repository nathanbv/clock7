/*
 * Nathan Bleuzen, 2018
 */

#ifndef TIMEPROVIDER_HPP
#define TIMEPROVIDER_HPP

#include <Arduino.h>

class TimeProvider
{
public:
    TimeProvider() {};
    ~TimeProvider() {};
    void init(void);
    bool isReady();
    time_t now(void);
    uint16_t get_decimal_time(void);
    const std::string & get_date(void);

    static time_t get_local_time(void);
private:
    const std::string & get_double_digit(const int digits);
};

#endif // TIMEPROVIDER_HPP
