#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <SoftwareSerial.h>
#include <Arduino.h>
#include "constants.h"

// Class to track all initialization errors among external devices. Also
// handles lighting up error LEDs on the breadboard
class ErrorHandler {
    // Error flags for each external device
    bool sdCardError;
    bool gpsError;
    bool bmpError;

    SoftwareSerial serial;  // Handles serial output

public:
    ErrorHandler();
    ~ErrorHandler(){}

    void triggerSDCardError() { sdCardError = true; }
    void triggerGPSError() { gpsError = true; }
    void triggerBMPError() { bmpError = true; }

    bool isAnyError() { return sdCardError || gpsError || bmpError; }
    bool isSDCardError() { return sdCardError; }
    bool isGPSError() { return gpsError; }
    bool isBMPError() { return bmpError; }
    void abort();
};

#endif
