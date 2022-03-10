#include "SDCardManager.h"

SDCardManager::~SDCardManager() {
    telem.close();
}

// Initializes SD card. Returns 0 if there's an error
bool SDCardManager::init() {
    // Initialize SD card
    if (!SD.begin(SD_PIN)) {
        return false;
    }

    // Open telemtry file
    telem = SD.open("tele.csv", FILE_WRITE);

    // Return error if file has error
    if (telem) {
        // Write header of CSV
        telem.println("time,temp,alt,pres,vel,accel,lat,lon");
        return true;
    } else {
        return false;
    }
}

// Writes a record to the file
void SDCardManager::write(int time, double temp, double alt, double pres, double vel, double accel, double lat, double lon) {
    telem.println("");
}
