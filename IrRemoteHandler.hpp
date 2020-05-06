/*
 * Nathan Bleuzen, 2018
 */

#ifndef IRREMOTEHANDLER_HPP
#define IRREMOTEHANDLER_HPP

#include <IRrecv.h>

enum operatingMode {
    OFF = 0,
    CLOCK,
    SETTINGS,
    WEATHER,
    TEST_COUNTER,
};

//const char * operatingModeToString(operatingMode mode) {
//    switch (mode) {
//    case OFF:          return "OFF";
//    case CLOCK:        return "CLOCK";
//    case SETTINGS:     return "SETTINGS";
//    case WEATHER:      return "WEATHER";
//    case TEST_COUNTER: return "TEST_COUNTER";
//    }
//    return "UNKNOWN_OPERATING_MODE";
//}

extern operatingMode currentMode;

class IrRemoteHandler
{
public:
    IrRemoteHandler();
    ~IrRemoteHandler() { }
    void init(void);
    void update(void);

private:
    void printKeycode(uint64_t val);
    void processKeycode(uint32_t val);

    IRrecv m_irRec;
    static const uint64_t s_mask32bits;
    static const uint16_t s_irRecPin;

};

#endif // IRREMOTEHANDLER_HPP
