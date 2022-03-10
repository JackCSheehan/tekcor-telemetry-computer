#include "SDCardManager.h"
#include "GPSManager.h"
#include "BMPManager.h"
#include "ErrorHandler.h"
#include "constants.h"

SDCardManager sdCardManager;
GPSManager gpsManager;
BMPManager bmpManager;
ErrorHandler errorHandler;

// Prints values in given BMPData and GPSData structs
void debug(GPSData gpsData, BMPData bmpData) {
    Serial.print("LAT : ");
    Serial.println(gpsData.lat);

    Serial.print("LON : ");
    Serial.println(gpsData.lon);

    Serial.print("ALT : ");
    Serial.println(gpsData.alt);

    Serial.print("PRES : ");
    Serial.println(bmpData.pres);

    Serial.print("TEMP : ");
    Serial.println(bmpData.temp);
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
    GPSData gpsData = gpsManager.readData();
    BMPData bmpData = bmpManager.readData();
    debug(gpsData, bmpData);
    sdCardManager.write(gpsData, bmpData);
}
