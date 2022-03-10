#ifndef GPS_MANAGER_H
#define GPS_MANAGER_H

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "constants.h"

// Struct to contain position data received from GPS at a particular time
struct PosTime {
    // Position
    double lat;
    double lon;
    double alt;

    // Time
    int hour;
    int min;
    int sec;
    int cent;
};

// Class to manage reading of GPS data
class GPSManager {
    TinyGPSPlus gps;        // GPS object to read data from GT-tU
    SoftwareSerial serial;  // Handles serial input

public:
    GPSManager() : serial(constants::RXD_PIN, constants::TXD_PIN) { serial.begin(constants::BAUD); }
    ~GPSManager(){}

    void init();
    PosTime readPosTime();
    uint32_t charsProcessed() { return gps.charsProcessed(); }
    
};


#endif
