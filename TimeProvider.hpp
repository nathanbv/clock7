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
    bool is_ready();
    time_t get_time(void);
    uint16_t get_decimal_time(void);
    const std::string get_date(void);
    const std::string get_date(time_t fromTime);
    bool is_sunrise(void);

private:
    const std::string to_double_digit(const int digits);

    static time_t sync_server_time(void);
    static const size_t s_jsonResponseSize;
};

#endif // TIMEPROVIDER_HPP
