#include "SDCardManager.h"
#include "GPSManager.h"
#include "BMPManager.h"
#include "ErrorHandler.h"
#include "constants.h"

SDCardManager sdCardManager;
GPSManager gpsManager;
BMPManager bmpManager;
ErrorHandler errorHandler;

// Prints values in given PresTemp and PosTime structs
void debug(PosTime posTime, PresTemp presTemp) {
    Serial.print("LAT : ");
    Serial.println(posTime.lat);

    Serial.print("LON : ");
    Serial.println(posTime.lon);

    Serial.print("ALT : ");
    Serial.println(posTime.alt);

    Serial.print("PRES : ");
    Serial.println(presTemp.pres);

    Serial.print("TEMP : ");
    Serial.println(presTemp.temp);
}

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

    if (!bmpManager.init()) {
        errorHandler.triggerBMPError();
    }

    if (errorHandler.isAnyError()) {
        errorHandler.abort();
    }

}

void loop() {
    PosTime posTime = gpsManager.readPosTime();
    PresTemp presTemp = bmpManager.readPresTemp();
    debug(posTime, presTemp);
    sdCardManager.write(0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
}
