/*
 * Nathan Bleuzen, 2018
 */

#include <Arduino.h>
#include "Logger.hpp"

// Unique intstance of Logger
Logger logger;

void Logger::init(logLevel thresh, uint32_t rate /* = 9600 */)
{
    m_logLevelThresh = thresh;
    if (m_logLevelThresh == LOG_OFF)
    {
        m_initSuccess = false;
        return;
    }

    Serial.begin(rate);

    uint8_t attempt = 0;
    while (!Serial && (++attempt < s_maxConnectionAttempt))
    {
        delay(250);
    }
    if (!Serial)
    {
        m_initSuccess = false;
        return;
    }
    m_initSuccess = true;
    Serial.flush();
    log(LOG_DEBUG, "\n");
    log(LOG_DEBUG, "------------------");
    log(LOG_DEBUG, "Serial initialized");
    log(LOG_DEBUG, "Hello from %s #%d", "logger", 42);
    log(LOG_DEBUG, "------------------");
}

void Logger::log(const logLevel prio, const char * format, ...)
{
    if (!m_initSuccess || (prio > m_logLevelThresh))
        return;

    va_list args;
    va_start(args, format);
    log_write(prio, format, args);
    va_end(args);
}

void Logger::log_write(const logLevel prio, const char * format, va_list args)
{
    const uint8_t bufsize = 127;
    int16_t ret;
    char buf[bufsize];

    ret = vsnprintf(buf, bufsize, format, args);
    if (ret >= bufsize) // Truncated output
        ret = bufsize-1;
    if (Serial && (ret >= 0))
    {
        Serial.println();
        Serial.print(logLevel_to_str(prio));
        Serial.print(buf);
    }
}

const char * Logger::logLevel_to_str(const logLevel type)
{
    switch (type)
    {
        case LOG_CRIT:   return "FATAL:  ";
        case LOG_ERR:    return "ERROR:  ";
        case LOG_WARN:   return "WARNING:";
        case LOG_NOTICE: return "NOTE:   ";
        case LOG_INFO:   return "INFO:   ";
        case LOG_DEBUG:  return "DEBUG:  ";
        case LOG_OFF:    break;
    }
    return "LOG:  ";
}

// Converts an unsigned integer to a string.
// Arguments:
//   input:     The value to print (up to 64 bits)
//   base:      The output base, defaults to HEX (16)
//   digitNb:   Number of preceding 0s to add
//   addPrefix: Add a prefix to represent the base (works for BIN, OCT, DEC, HEX)
// Returns:
//   A string representation of the integer.
String Logger::uint_to_string(uint64_t input,
                              uint8_t base /* = HEX */,
                              uint8_t digitNb /* = 0 */,
                              bool addPrefix /* = true */) {
    String str = "";
    // Prevent issues if called with base <= 1
    if (base < 2) base = DEC;
    // Check we have a base that we can actually print, i.e. [0-9A-Z] == 36
    else if (base > 36) base = DEC;

    do {
        char digit = input % base;
        input /= base;

        if (digit < 10) digit += '0';
        else digit += 'A' - 10;
        str = digit + str;
    } while (input);

    for (uint8_t it = str.length(); it < digitNb; ++it)
        str = '0' + str;

    if (addPrefix) {
        switch (base) {
            case BIN: str = "0b" + str; break;
            case OCT: str = "0o" + str; break;
            case DEC: str = "0d" + str; break;
            case HEX: str = "0x" + str; break;
            default: break;
        }
    }

    return str;
}
