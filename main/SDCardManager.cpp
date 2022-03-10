#include "SDCardManager.h"

SDCardManager::~SDCardManager() {
    telem.close();
}

// Initializes SD card. Returns 0 if there's an error
bool SDCardManager::init() {
    // Initialize SD card
    if (!SD.begin(constants::SD_PIN)) {
        return false;
    }

    // Open telemtry file
    telem = SD.open("tele.csv", FILE_WRITE);

    // Return error if file has error
    if (telem) {
        // Write header of CSV
        telem.println("time,temp,alt,pres,vel,lat,lon");
        return true;
    } else {
        return false;
    }
}

// Writes a record to the file
void SDCardManager::write(GPSData gpsData, BMPData bmpData) {
    telem.print("0,");

    telem.print(bmpData.temp); telem.print(",");
    telem.print(gpsData.alt); telem.print(",");
    telem.print(bmpData.pres); telem.print(",");
    telem.print(gpsData.vel); telem.print(",");
    telem.print(gpsData.lat); telem.print(",");
    telem.print(gpsData.lat); telem.print(",");
}
