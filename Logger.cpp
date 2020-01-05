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
    switch(type)
    {
        case LOG_CRIT:   return "FATAL:  ";
        case LOG_ERR:    return "ERROR:  ";
        case LOG_WARN:   return "WARNING:";
        case LOG_NOTICE: return "NOTE:   ";
        case LOG_INFO:   return "INFO:   ";
        case LOG_DEBUG:  return "DEBUG:  ";
    }
    return "LOG:  ";
}
