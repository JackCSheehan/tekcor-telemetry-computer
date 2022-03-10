#include "ErrorHandler.h"

ErrorHandler::ErrorHandler() : serial(constants::RXD_PIN, constants::TXD_PIN) {
    sdCardError = false;
    gpsError = false;
    bmpError = false;
    serial.begin(constants::BAUD);
}

// Exits program (puts CPU in infinite loop) after setting error lights
// to prevent using an external device which was not initialized correctly
void ErrorHandler::abort() {
    serial.println("ABORTING");

    // Log errors and trigger error lights
    if (sdCardError) {
        serial.println("ERROR: Failed to initialize SD card");
        //digitalWrite(constants::SD_ERROR_PIN, HIGH);
    }

    if (gpsError) {
        serial.println("ERROR: Failed to initialize GPS");
        //digitalWrite(constants::GPS_ERROR_PIN, HIGH);
    }

    if (bmpError) {
        serial.println("ERROR: Failed to initialize BMP");
        //digitalWrite(constants::BMP_ERROR_PIN, HIGH);
    }

    exit(1);
}
