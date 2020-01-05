/*
 * Nathan Bleuzen, 2018
 */

#ifndef LOGGER_HPP
#define LOGGER_HPP

// Log priority levels
typedef enum
{
    LOG_CRIT   = 2, // Critical conditions
    LOG_ERR    = 3, // Error conditions
    LOG_WARN   = 4, // Warning conditions
    LOG_NOTICE = 5, // Normal but significant condition
    LOG_INFO   = 6, // Informational message
    LOG_DEBUG  = 7, // Debug-level message
    LOG_OFF    = 8, // Deactivate logging
} logLevel;

class Logger
{
public:
    void init(logLevel thresh, uint32_t rate = 9600);
    void log(const logLevel prio, const char * format, ...);

private:
    void log_write(const logLevel prio, const char * format, va_list args);
    const char * logLevel_to_str(const logLevel type);

private:
    logLevel m_logLevelThresh;
    bool m_initSuccess;
    static const uint8_t s_maxConnectionAttempt = 10;
};

extern Logger logger;

#endif // LOGGER_HPP
