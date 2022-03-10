#include "SDCardManager.h"
#include "GPSManager.h"
#include "ErrorHandler.h"
#include "constants.h"

SDCardManager sdCardManager;
GPSManager gpsManager;
ErrorHandler errorHandler;

void setup() {
    // Initialize error LEDs
    pinMode(constants::SD_ERROR_PIN, OUTPUT);
  
    Serial.begin(constants::BAUD);

    // Initialize all external devices
    if (!sdCardManager.init()) {
        errorHandler.triggerSDCardError();
    }

    // Wait for GPS to initialize
    delay(5000);

    // If GPS hasn't processed enough data after 5 seconds, trigger an error
    if (gpsManager.charsProcessed() < 10) {
        errorHandler.triggerGPSError();
    }

    if (errorHandler.isAnyError()) {
        errorHandler.abort();
    }

}

void loop() {
    gpsManager.readPosTime();
    sdCardManager.write(0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
}
