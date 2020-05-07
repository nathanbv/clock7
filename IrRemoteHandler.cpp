/*
 * Nathan Bleuzen, 2018
 */

#include "IrRemoteHandler.hpp"
#include "config.h"

operatingMode currentMode = CLOCK;

static const char * operatingModeToString(operatingMode mode) {
    switch (mode) {
    case DISPLAY_OFF:  return "DISPLAY_OFF";
    case CLOCK:        return "CLOCK";
    case SETTINGS:     return "SETTINGS";
    case WEATHER:      return "WEATHER";
    case TEST_COUNTER: return "TEST_COUNTER";
    case INVALID_OPERATING_MODE: return "INVALID_OPERATING_MODE";
    }
    return "Unknown operatingMode!";
}

const uint64_t IrRemoteHandler::s_mask32bits = 0xFFFF;
const uint16_t IrRemoteHandler::s_irRecPin = 14; // D5

IrRemoteHandler::IrRemoteHandler():
        m_irRec(s_irRecPin)
{ }

void IrRemoteHandler::init(void) {
    logger.log(LOG_DEBUG, "IrRemoteHandler::%s", __func__);
    m_irRec.enableIRIn(); // Start the receiver
}

void IrRemoteHandler::update(void) {
    decode_results results;
    if (m_irRec.decode(&results)) {
        //printKeycode(results.value); // Print key code received, useful to create a map of the remote
        uint32_t keycode = results.value & s_mask32bits; // From 64 bits, keep only 32 LSB
        processKeycode(keycode);

        m_irRec.resume(); // Receive the next value
    }
}

void IrRemoteHandler::printKeycode(uint64_t val) {
    logger.log(LOG_DEBUG, "keycode=%s", logger.uint_to_string(val).c_str());
}

void IrRemoteHandler::processKeycode(uint32_t val) {
    operatingMode newMode = INVALID_OPERATING_MODE;
    switch (val) {
    /* Temporary key values, from the only remote at arms reach */
    case 0xFC03: newMode = CLOCK; break;
    case 0xC43B: newMode = DISPLAY_OFF; break;
    case 0xC23D: newMode = TEST_COUNTER; break;
    }
    if (newMode != INVALID_OPERATING_MODE && newMode != currentMode) {
        currentMode = newMode;
        logger.log(LOG_DEBUG, "Entering %s mode", operatingModeToString(currentMode));
    }
}
