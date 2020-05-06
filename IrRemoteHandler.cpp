/*
 * Nathan Bleuzen, 2018
 */

#include "IrRemoteHandler.hpp"
#include "config.h"

operatingMode currentMode = CLOCK;

const uint64_t IrRemoteHandler::s_mask32bits = 0xFFFF;
const uint16_t IrRemoteHandler::s_irRecPin = 14; // D5

IrRemoteHandler::IrRemoteHandler():
        m_irRec(s_irRecPin)
{ }

void IrRemoteHandler::init(void) {
    m_irRec.enableIRIn(); // Start the receiver
}

void IrRemoteHandler::update(void) {
    decode_results results;
    if (m_irRec.decode(&results)) {
        printKeycode(results.value);
        uint32_t keycode = results.value & s_mask32bits; // From 64 bits, keep only 32 LSB
        processKeycode(keycode);

        m_irRec.resume(); // Receive the next value
    }
}

void IrRemoteHandler::printKeycode(uint64_t val) {
    logger.log(LOG_DEBUG, "keycode=%s", logger.uint_to_string(val).c_str());
}

void IrRemoteHandler::processKeycode(uint32_t val) {
    int8_t keyVal = -1;
    operatingMode newMode;
    switch (val) {
    case 0xFC03:
        keyVal = 1;
        newMode = CLOCK;
        break;
    case 0xC43B:
        keyVal = 3;
        newMode = SETTINGS;
        break;
    case 0xC23D:
        keyVal = 4;
        newMode = TEST_COUNTER;
        break;
    default: break;
    }
    if (keyVal != -1) {
        logger.log(LOG_DEBUG, "You pressed %d!", keyVal);
        currentMode = newMode;
    }
    else {
        logger.log(LOG_DEBUG, "You pressed an unrecognized key...");
    }
}
