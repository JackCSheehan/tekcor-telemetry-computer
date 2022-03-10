#include "GPSManager.h"

// Reads position from GPS and returns as a GPSData struct
GPSData GPSManager::readData() {
    // Initialize to error values initially
    GPSData pos = {361, 361, -1, -1, -1, -1, -1};

    // Read if available
    if (serial.available() > 0) {
        if (gps.encode(serial.read())) {
            // Read location
            if (gps.location.isValid()) {
                pos.lat = gps.location.lat();
                pos.lon = gps.location.lng();
            }

            // Read altitude
            if (gps.altitude.isValid()) {
                pos.alt = gps.altitude.meters();
            }

            // Read velocity
            if (gps.speed.isValid()) {
                pos.vel = gps.speed.mps();
            }

            // Read time
            if (gps.time.isValid()) {
                pos.hour = gps.time.hour();
                pos.min = gps.time.minute();
                pos.sec = gps.time.second();
                pos.cent = gps.time.centisecond();
            }
        }
    }

    return pos;
}
